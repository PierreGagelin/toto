
#include "factory.hpp"

struct derived_lib : base
{
    derived_lib() : base() { DEBUG("Create derived_lib struct instance"); }
    virtual ~derived_lib() override { DEBUG("Destroy derived_lib struct instance"); }

    virtual void method() override {}
};

// Implement a factory for this derived class
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

extern "C"
{
    struct base *derived_lib_create()
    {
        return new derived_lib;
    }
    void derived_lib_destroy(struct base *entry)
    {
        delete static_cast<struct derived_lib *>(entry);
    }
}
