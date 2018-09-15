
#include "toto.hpp"

struct base
{
    virtual ~base() {}
    virtual void method() = 0;
};

struct base_factory
{
    virtual struct base *create() = 0;
    virtual void destroy(struct base *entry) = 0;
};

std::unordered_map<std::string, struct base_factory *> *factory_get();
