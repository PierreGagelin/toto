

#ifndef TOTO_HPP
#define TOTO_HPP

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>

#include <string>
#include <unordered_map>
#include <vector>

#define DEBUG(msg, ...)                             \
    do                                              \
    {                                               \
        printf("[DEBUG] " msg "\n", ##__VA_ARGS__); \
    } while (false)
#define ERROR(msg, ...)                             \
    do                                              \
    {                                               \
        printf("[ERROR] " msg "\n", ##__VA_ARGS__); \
    } while (false)

#define ASSERT(condition)                           \
    do                                              \
    {                                               \
        if (!(condition))                           \
        {                                           \
            ERROR("Assertion failed: " #condition); \
            exit(1);                                \
        }                                           \
    } while (false)

#endif // TOTO_HPP
