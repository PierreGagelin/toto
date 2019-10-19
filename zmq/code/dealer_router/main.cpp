
#include <cassert>
#include <cstring>
#include <set>
#include <string>
#include <vector>

extern "C"
{
#include <getopt.h>
#include <zmq.h>
}

const char *TCP_ADDRESS = "tcp://127.0.0.1:1664";

std::set<std::string> clients;

static void message_clear(std::vector<zmq_msg_t> &msg)
{
    for (auto &part : msg)
    {
        int rc;

        rc = zmq_msg_close(&part);
        assert(rc == 0);
    }

    msg.clear();
}

static void message_recv(void *socket, std::vector<zmq_msg_t> &msg)
{
    zmq_msg_t part;

    message_clear(msg);

    do
    {
        int rc;

        zmq_msg_init(&part);
        rc = zmq_msg_recv(&part, socket, 0);
        assert(rc != -1);

        msg.push_back(part);

    } while (zmq_msg_more(&part) == 1);

    if (msg.size() == 1u)
    {
        const char *message;

        message = static_cast<char *>(zmq_msg_data(&msg[0]));

        printf("Received message [message=%s]\n", message);
    }
    else if (msg.size() == 2u)
    {
        std::string client;
        const char *name;
        const char *message;

        // First message part is client identity
        name = static_cast<char *>(zmq_msg_data(&msg[0]));
        client = std::string(name);

        clients.insert(client);

        message = static_cast<char *>(zmq_msg_data(&msg[1]));

        printf("Received message [client=%s ; message=%s]\n", name, message);
    }
    else
    {
        assert("unexpected part counts" == nullptr);
    }

    message_clear(msg);
}

static void message_send(void *socket, std::vector<zmq_msg_t> &msg)
{
    int rc;
    size_t size;
    auto end = msg.end();

    end--;
    for (auto it = msg.begin(); it != end; ++it)
    {
        size = zmq_msg_size(&(*it));
        rc = zmq_msg_send(&(*it), socket, ZMQ_SNDMORE);
        assert(rc != -1);
        assert(static_cast<size_t>(rc) == size);
    }

    size = zmq_msg_size(&(*end));
    rc = zmq_msg_send(&(*end), socket, 0);
    assert(rc != -1);
    assert(static_cast<size_t>(rc) == size);

    printf("Sent multi-part message [part_count=%zu]\n", msg.size());

    msg.clear();
}

static void *server_start(void *ctx)
{
    void *server;
    int rc;

    server = zmq_socket(ctx, ZMQ_ROUTER);
    assert(server != nullptr);

    rc = zmq_bind(server, TCP_ADDRESS);
    assert(rc == 0);

    return server;
}

static void *client_start(void *ctx, const char *client_id)
{
    void *client;
    int rc;

    client = zmq_socket(ctx, ZMQ_DEALER);
    assert(client != nullptr);

    rc = zmq_setsockopt(client, ZMQ_IDENTITY, client_id, strlen(client_id) + 1);
    assert(rc == 0);

    rc = zmq_connect(client, TCP_ADDRESS);
    assert(rc == 0);

    return client;
}

static void server_data(void *socket)
{
    std::vector<zmq_msg_t> msg;

    message_recv(socket, msg);

    for (const auto &client : clients)
    {
        zmq_msg_t part;
        std::string message;
        int rc;

        message = "hello " + client;

        rc = zmq_msg_init_size(&part, client.size() + 1);
        assert(rc == 0);

        memcpy(zmq_msg_data(&part), client.c_str(), client.size() + 1);
        msg.push_back(part);

        rc = zmq_msg_init_size(&part, message.size() + 1);
        assert(rc == 0);

        memcpy(zmq_msg_data(&part), message.c_str(), message.size() + 1);
        msg.push_back(part);

        message_send(socket, msg);
    }
}

static void client_data(void *socket)
{
    std::vector<zmq_msg_t> msg;
    zmq_msg_t part;
    int rc;

    rc = zmq_msg_init_size(&part, 6);
    assert(rc == 0);

    memset(zmq_msg_data(&part), 'A', 6);

    msg.push_back(part);
    message_send(socket, msg);

    message_recv(socket, msg);
}

int main(int argc, char **argv)
{
    int opt;
    const char *options = "i:";
    const char *client_id;

    // Retrieve options
    client_id = nullptr;
    for (opt = getopt(argc, argv, options); opt != -1; opt = getopt(argc, argv, options))
    {
        switch (opt)
        {
        case 'i':
            client_id = optarg;
            printf("Configured client identifier [client_id=%s]\n", client_id);
            break;
        default:
            assert("Failed to parse option" == nullptr);
            break;
        }
    }

    int major;
    int minor;
    int patch;
    zmq_version(&major, &minor, &patch);
    printf("ZMQ version: %d.%d.%d\n", major, minor, patch);

    // Setup ZMQ
    void *zmq_ctx = zmq_ctx_new();
    assert(zmq_ctx != nullptr);

    void *zmq_sock;
    if (client_id == nullptr)
    {
        zmq_sock = server_start(zmq_ctx);
    }
    else
    {
        zmq_sock = client_start(zmq_ctx, client_id);

        // Initiate communication with router
        client_data(zmq_sock);
    }

    while (true)
    {
        zmq_pollitem_t poll_entry;
        int ready_count;

        poll_entry.events = ZMQ_POLLIN;
        poll_entry.fd = -1;
        poll_entry.socket = zmq_sock;
        ready_count = zmq_poll(&poll_entry, 1, 100);
        if (ready_count == -1)
        {
            printf("Failed to call zmq_poll: %s [errno=%d]\n", strerror(errno), errno);
            continue;
        }
        else if (ready_count == 0)
        {
            // Nothing ready at the moment
            continue;
        }
        assert(ready_count == 1);
        assert(poll_entry.revents == ZMQ_POLLIN);

        if (client_id == nullptr)
        {
            server_data(zmq_sock);
        }
        else
        {
            client_data(zmq_sock);
        }
    }
}
