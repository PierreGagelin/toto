
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ulfius.h>
#include <jansson.h>

#define PORT 1664

static void print_map(const struct _u_map *map, const char *name)
{
    printf("Printing map name=%s\n", name);

    if (map != NULL)
    {
        const char **keys;
        int i;

        keys = u_map_enum_keys(map);
        for (i = 0; keys[i] != NULL; i++)
        {
            const char *value;

            value = u_map_get(map, keys[i]);

            printf("- item: key=%s value=%s\n", keys[i], value);
        }
    }
}

static void print_json(json_t *json_obj, const char *name)
{
    const char *key;
    json_t *value;

    printf("Printing JSON object name=%s\n", name);

    json_object_foreach(json_obj, key, value)
    {
        printf("- item: json_key=%s", key);
        if (json_typeof(value) == JSON_STRING)
        {
            printf(" json_string=%s", json_string_value(value));
        }
        printf("\n");
    }
}

static void print_request(const struct _u_request *request)
{
    if (request != NULL)
    {
        printf("http_protocol=%s\n", request->http_protocol);
        printf("http_verb=%s\n", request->http_verb);
        printf("http_url=%s\n", request->http_url);
        print_map(request->map_url, "URL");
        print_map(request->map_header, "headers");

        json_t *json_obj = ulfius_get_json_body_request(request, NULL);
        if (json_obj != NULL)
        {
            print_json(json_obj, "body");
        }
        else
        {
            print_map(request->map_post_body, "body");
        }
    }
}

static void print_response(const struct _u_response *response)
{
    if (response != NULL)
    {
        char *response_body;

        response_body = malloc(response->binary_body_length + 1);
        strncpy(response_body, response->binary_body, response->binary_body_length);
        response_body[response->binary_body_length] = '\0';

        printf("status=%ld\n", response->status);
        printf("protocol=%s\n", response->protocol);
        printf("body=%s\n", response_body);
        print_map(response->map_header, "headers");

        free(response_body);
    }
}

static int callback_test(const struct _u_request *request, struct _u_response *response, void *user_data)
{
    print_request(request);

    ulfius_set_string_body_response(response, 200, "test answer");

    return U_CALLBACK_CONTINUE;
}

static int callback_default(const struct _u_request *request, struct _u_response *response, void *user_data)
{
    print_request(request);

    ulfius_set_string_body_response(response, 200, "default answer");

    return U_CALLBACK_CONTINUE;
}

static int rest_server()
{
    struct _u_instance instance;
    int ret;

    if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK)
    {
        return 1;
    }

    ulfius_add_endpoint_by_val(&instance, "PUT", NULL, "/test", 0, &callback_test, NULL);
    ulfius_add_endpoint_by_val(&instance, "DELETE", NULL, "/test", 0, &callback_test, NULL);

    ulfius_set_default_endpoint(&instance, &callback_default, NULL);

    ret = ulfius_start_framework(&instance);
    if (ret == U_OK)
    {
        printf("Waiting to be killed\n");
        while (0 == 0)
        {
            sleep(10);
        }
    }
    else
    {
        ret = 1;
    }

    ulfius_stop_framework(&instance);
    ulfius_clean_instance(&instance);

    return ret;
}

static int rest_client()
{
    struct _u_request request;
    struct _u_response response;
    struct _u_map url_params;
    struct _u_map req_headers;
    json_t *json_body;
    int ret;

    ulfius_init_request(&request);
    ulfius_init_response(&response);

    u_map_init(&url_params);
    u_map_put(&url_params, "url-param1", "url-value1");
    u_map_put(&url_params, "url-param2", "url-value2");

    u_map_init(&req_headers);
    u_map_put(&req_headers, "Content-Type", "application/json");

    json_body = json_object();
    json_object_set_new(json_body, "json-key1", json_string("json-string1"));
    json_object_set_new(json_body, "json-key2", json_string("json-string2"));

    request.http_verb = strdup("PUT");
    request.http_url = strdup("http://localhost:1664/test");
    request.timeout = 20;
    u_map_copy_into(request.map_url, &url_params);
    u_map_copy_into(request.map_header, &req_headers);
    ulfius_set_json_body_request(&request, json_body);

    ret = ulfius_send_http_request(&request, &response);
    if (ret == U_OK)
    {
        print_response(&response);
    }
    else
    {
        printf("Error: failed HTTP request status=%d\n", ret);
    }

    u_map_clean(&url_params);
    u_map_clean(&req_headers);
    json_decref(json_body);

    ulfius_clean_request(&request);
    ulfius_clean_response(&response);

    return ret;
}

int main(int argc, char **argv)
{
    int ret;

    if (argc == 1)
    {
        ret = rest_server();
    }
    else
    {
        ret = rest_client();
    }

    return ret;
}
