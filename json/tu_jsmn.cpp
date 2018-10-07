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

//
// Compare a JSON token against a string
//
static int json_cmp(const char *json, jsmntok_t *tok, const char *str)
{
    if (strncmp(json + tok->start, str, tok->end - tok->start) == 0)
    {
        return 0;
    }
    return -1;
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

#if 0
        if (jsoneq(json, &t[i], "user") == 0) {
			/* We may use strndup() to fetch string value */
			printf("- User: %.*s\n", t[i+1].end-t[i+1].start,
					json + t[i+1].start);
			i++;
		} else if (jsoneq(json, &t[i], "admin") == 0) {
			/* We may additionally check if the value is either "true" or "false" */
			printf("- Admin: %.*s\n", t[i+1].end-t[i+1].start,
					json + t[i+1].start);
			i++;
		} else if (jsoneq(json, &t[i], "uid") == 0) {
			/* We may want to do strtol() here to get numeric value */
			printf("- UID: %.*s\n", t[i+1].end-t[i+1].start,
					json + t[i+1].start);
			i++;
		} else if (jsoneq(json, &t[i], "groups") == 0) {
			int j;
			printf("- Groups:\n");
			if (t[i+1].type != JSMN_ARRAY) {
				continue; /* We expect groups to be an array of strings */
			}
			for (j = 0; j < t[i+1].size; j++) {
				jsmntok_t *g = &t[i+j+2];
				printf("  * %.*s\n", g->end - g->start, json + g->start);
			}
			i += t[i+1].size + 1;
		} else {
			printf("Unexpected key: %.*s\n", t[i].end-t[i].start,
					json + t[i].start);
		}
#endif

    delete[] token;

    return 0;
}
