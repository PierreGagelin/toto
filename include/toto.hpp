

#ifndef TOTO_HPP
#define TOTO_HPP

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <memory>

#include <string>
#include <unordered_map>
#include <vector>

#include <boost/intrusive_ptr.hpp>

#define STR(token) #token

#define DEBUG(msg, ...)                             \
    do                                              \
    {                                               \
        printf("[DEBUG] " msg "\n", ##__VA_ARGS__); \
    } while (false);
#define ERR(msg, ...)                             \
    do                                            \
    {                                             \
        printf("[ERR] " msg "\n", ##__VA_ARGS__); \
    } while (false);

#define ASSERT(condition)                             \
    do                                                \
    {                                                 \
        if (!(condition))                             \
        {                                             \
            ERR("Assertion failed: " STR(condition)); \
            exit(1);                                  \
        }                                             \
    } while (false);

#endif // TOTO_HPP
