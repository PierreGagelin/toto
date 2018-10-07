
#include "factory.hpp"

// Factory of base class pointers: is filled with derived class constructor and destructors
std::unordered_map<std::string, struct base_factory *> *factory;
std::unordered_map<std::string, struct base_factory *> *factory_get()
{
    if (factory == nullptr)
    {
        factory = new std::unordered_map<std::string, struct base_factory *>;
    }
    return factory;
}

struct derived : base
{
    derived() : base() { DEBUG("Create derived struct instance"); }
    virtual ~derived() override { DEBUG("Destroy derived struct instance"); }

    virtual void method() override {}
};

// Interface to create and destroy derived class via factory approach
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

// Interface to create and destroy derived class via dlopen / dlsym approach
extern "C"
{
    struct base *derived_create()
    {
        return new derived;
    }
    void derived_destroy(struct base *entry)
    {
        delete static_cast<struct derived *>(entry);
    }
}

int main(int, char **)
{
    struct base *entry;
    void *handle;
    struct base *(*create)();
    void (*destroy)(struct base *);

    // dlopen method
    handle = dlopen(nullptr, RTLD_LAZY);
    if (handle == nullptr)
    {
        ERROR("Failed to open library");
    }

    create = reinterpret_cast<struct base *(*)()>(dlsym(handle, "derived_create"));
    destroy = reinterpret_cast<void (*)(struct base *)>(dlsym(handle, "derived_destroy"));
    if ((create == nullptr) || (destroy == nullptr))
    {
        ERROR("Failed to load function_main symbols");
    }
    entry = create();
    destroy(entry);

    create = reinterpret_cast<struct base *(*)()>(dlsym(handle, "derived_lib_create"));
    destroy = reinterpret_cast<void (*)(struct base *)>(dlsym(handle, "derived_lib_destroy"));
    if ((create == nullptr) || (destroy == nullptr))
    {
        ERROR("Failed to load function_lib symbols");
    }
    entry = create();
    destroy(entry);

    // factory method
    entry = (*factory_get())["derived"]->create();
    (*factory_get())["derived"]->destroy(entry);

    entry = (*factory_get())["derived_lib"]->create();
    (*factory_get())["derived"]->destroy(entry);
}
