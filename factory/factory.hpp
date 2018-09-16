

#ifndef FACTORY_HPP
#define FACTORY_HPP

extern "C"
{
#include "dlfcn.h"
}

#include "toto.hpp"

// Abstract base class
struct base
{
    base() {}
    virtual ~base() {}

    virtual void method() = 0;
};

// Abstract base class factory
struct base_factory
{
    virtual struct base *create() = 0;
    virtual void destroy(struct base *entry) = 0;
};
std::unordered_map<std::string, struct base_factory *> *factory_get();

#endif // FACTORY_HPP
