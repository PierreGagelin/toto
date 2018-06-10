
#include <cstdio>

#define DEBUG(msg, ...)                            \
    do                                             \
    {                                              \
        printf("[DEBUG] " msg "\n", ##__VA_ARGS__); \
    } while (false);
#define ERR(msg, ...)                            \
    do                                           \
    {                                            \
        printf("[ERR] " msg "\n", ##__VA_ARGS__); \
    } while (false);
