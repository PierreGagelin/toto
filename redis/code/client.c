#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis/hiredis.h>

int main(int argc, char **argv)
{
    redisContext *c;
    redisReply *reply;
    const char *hostname;
    int port;
    struct timeval timeout;
    unsigned int j;

    hostname = "127.0.0.1";
    port = 6379;
    timeout.tv_sec = 1;
    timeout.tv_usec = 500000;

    c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL)
    {
        printf("Failed to connect to redis server: context allocation failed\n");
        exit(1);
    }
    else if (c->err != 0)
    {
        printf("Failed to connect to redis server err=%d errstr=%s\n", c->err, c->errstr);
        redisFree(c);
        exit(1);
    }
    else
    {
        printf("Connected to redis server\n");
    }

    // Send a ping
    reply = redisCommand(c, "PING");
    printf("PING reply=%s\n", reply->str);
    freeReplyObject(reply);

    // Set a key
    reply = redisCommand(c, "SET %s %s", "foo", "hello world");
    printf("SET foo reply=%s\n", reply->str);
    freeReplyObject(reply);

    // Get a key
    reply = redisCommand(c, "GET foo");
    printf("GET foo reply=%s\n", reply->str);
    freeReplyObject(reply);

    // Increment a counter twice
    reply = redisCommand(c, "INCR counter");
    printf("INCR counter: %lld\n", reply->integer);
    freeReplyObject(reply);
    reply = redisCommand(c, "INCR counter");
    printf("INCR counter: %lld\n", reply->integer);
    freeReplyObject(reply);

    // Create a list
    reply = redisCommand(c, "DEL mylist");
    freeReplyObject(reply);
    for (j = 0; j < 10; j++)
    {
        char buf[64];

        snprintf(buf, 64, "%u", j);
        reply = redisCommand(c, "LPUSH mylist value-%s", buf);
        freeReplyObject(reply);
    }

    // Print the list
    reply = redisCommand(c, "LRANGE mylist 0 -1");
    if (reply->type == REDIS_REPLY_ARRAY)
    {
        for (j = 0; j < reply->elements; j++)
        {
            printf("LRANGE mylist index=%u str=%s\n", j, reply->element[j]->str);
        }
    }
    freeReplyObject(reply);

    // Disconnect and free the context
    redisFree(c);

    return 0;
}
