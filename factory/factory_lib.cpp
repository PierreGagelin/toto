
#include "factory.hpp"

struct derived_lib : base
{
    virtual ~derived_lib() override {}
    virtual void method() override { DEBUG("Construct derived_lib struct instance"); }
};

struct derived_lib_factory : base_factory
{
    virtual struct base *create() override
    {
        return new derived_lib;
    }
    virtual void destroy(struct base *entry) override
    {
        delete static_cast<struct derived_lib *>(entry);
    }
};

struct derived_lib_register
{
    derived_lib_register()
    {
        (*factory_get())["derived_lib"] = new struct derived_lib_factory;
    }
};
struct derived_lib_register derived_lib_entry;