//
// Test unit using jsmn JSON parser
//

#include "toto.hpp"
#include "jsmn.h"

static const char *json_type_to_string(jsmntype_t type)
{
    switch (type)
    {
    case JSMN_UNDEFINED:
        return "JSMN_UNDEFINED";
    case JSMN_OBJECT:
        return "JSMN_OBJECT";
    case JSMN_ARRAY:
        return "JSMN_ARRAY";
    case JSMN_STRING:
        return "JSMN_STRING";
    case JSMN_PRIMITIVE:
        return "JSMN_PRIMITIVE";
    default:
        ERROR("Unknown token type [type=%d]", type);
        return "UNKNOWN";
    }
}

static void json_print(const char *json, jsmntok_t *tok, int idx)
{
    DEBUG("Token [index=%d ; type=%s ; value=%.*s]",
          idx,
          json_type_to_string(tok[idx].type),
          tok[idx].end - tok[idx].start,
          json + tok[idx].start);
}

int main(int, char **)
{
    jsmn_parser parser;
    jsmntok_t *token;
    char json[1024];
    int token_count;
    int ret;

    // Create a JSON string
    ret = snprintf(json, sizeof(json), "{ \"begin\": \"hello world\", \"list\": [1, null, true], \"end\": \"goodbye world\" }");
    ASSERT(ret > 0);
    ASSERT(static_cast<size_t>(ret) < sizeof(json));

    jsmn_init(&parser);
    token_count = jsmn_parse(&parser, json, strlen(json), NULL, 0);
    DEBUG("JSON string inspected [token_count=%d]", token_count);
    ASSERT(token_count > 0);

    token = new jsmntok_t[token_count];
    jsmn_init(&parser);
    ret = jsmn_parse(&parser, json, strlen(json), token, token_count);
    DEBUG("JSON string parsed [token_count=%d]", ret);
    ASSERT(ret == token_count);

    for (int i = 0; i < token_count; ++i)
    {
        json_print(json, token, i);
    }

    delete[] token;

    return 0;
}
