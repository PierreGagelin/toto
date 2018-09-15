
#include "factory.hpp"

std::unordered_map<std::string, struct base_factory *> *factory;

std::unordered_map<std::string, struct base_factory *> *factory_get()
{
    if (factory == nullptr)
    {
        factory =  new std::unordered_map<std::string, struct base_factory *>;
    }
    return factory;
}

struct derived : base
{
    virtual ~derived() override {}
    virtual void method() override { DEBUG("Construct derived struct instance"); }
};

struct derived_factory : base_factory
{
    virtual struct base *create() override
    {
        return new derived;
    }
    virtual void destroy(struct base *entry) override
    {
        delete static_cast<struct derived *>(entry);
    }
};

struct derived_register
{
    derived_register()
    {
        (*factory_get())["derived"] = new struct derived_factory;
    }
};
struct derived_register derived_entry;

int main(int, char **)
{
    struct base *entry;

    entry = (*factory_get())["derived"]->create();

    entry->method();

    (*factory_get())["derived"]->destroy(entry);

    entry = (*factory_get())["derived_lib"]->create();

    entry->method();

    (*factory_get())["derived"]->destroy(entry);
}
