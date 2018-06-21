//
// @brief Test unit on smart pointers
//

#include <chrono>  // now
#include <cstdlib> // seed
#include <memory>  // shared_ptr

#include <boost/intrusive_ptr.hpp> // intrusive_ptr

#include "toto.hpp"

int seed;

class shared_int
{
  public:
    int value;
    int ref;

    shared_int() : value(0), ref(0){};
};

inline void
intrusive_ptr_add_ref(class shared_int *p)
{
    ++p->ref;
}

inline void
intrusive_ptr_release(class shared_int *p)
{
    --p->ref;
    if (p->ref == 0)
    {
        delete p;
    }
}

template <typename T>
void use_ptr_val(T ptr) __attribute__((noinline));
template <typename T>
void use_ptr_val(T ptr)
{
    if (seed > -1)
    {
        ++ptr->value;
    }
}

template <typename T>
void use_ptr_ref(T &ptr) __attribute__((noinline));
template <typename T>
void use_ptr_ref(T &ptr)
{
    if (seed > -1)
    {
        ++ptr->value;
    }
}

template <typename T>
T &&use_ptr_fwd(T &&ptr) __attribute__((noinline));
template <typename T>
T &&use_ptr_fwd(T &&ptr)
{
    if (seed > -1)
    {
        ++ptr->value;
    }
    return std::forward<T>(ptr);
}

class shared_int *&&use_raw_fwd(class shared_int *&&ptr) __attribute__((noinline));
class shared_int *&&use_raw_fwd(class shared_int *&&ptr)
{
    if (seed > -1)
    {
        ++ptr->value;
    }
    return std::forward<class shared_int *>(ptr);
}

boost::intrusive_ptr<class shared_int> &&use_itr_fwd(boost::intrusive_ptr<class shared_int> &&ptr) __attribute__((noinline));
boost::intrusive_ptr<class shared_int> &&use_itr_fwd(boost::intrusive_ptr<class shared_int> &&ptr)
{
    if (seed > -1)
    {
        ++ptr->value;
    }
    return std::forward<boost::intrusive_ptr<shared_int>>(ptr);
}

std::shared_ptr<class shared_int> &&use_shd_fwd(std::shared_ptr<class shared_int> &&ptr) __attribute__((noinline));
std::shared_ptr<class shared_int> &&use_shd_fwd(std::shared_ptr<class shared_int> &&ptr)
{
    if (seed > -1)
    {
        ++ptr->value;
    }
    return std::forward<std::shared_ptr<shared_int>>(ptr);
}

std::unique_ptr<class shared_int> &&use_uni_fwd(std::unique_ptr<class shared_int> &&ptr) __attribute__((noinline));
std::unique_ptr<class shared_int> &&use_uni_fwd(std::unique_ptr<class shared_int> &&ptr)
{
    if (seed > -1)
    {
        ++ptr->value;
    }
    return std::forward<std::unique_ptr<shared_int>>(ptr);
}

//
// @brief Basic usage smart_ptr
//
int main(int argc, char **argv)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> beg;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;

    std::chrono::duration<double> diff_raw_val;
    std::chrono::duration<double> diff_itr_val;
    std::chrono::duration<double> diff_shd_val;
    std::chrono::duration<double> diff_raw_ref;
    std::chrono::duration<double> diff_itr_ref;
    std::chrono::duration<double> diff_shd_ref;
    std::chrono::duration<double> diff_raw_fwd;
    std::chrono::duration<double> diff_itr_fwd;
    std::chrono::duration<double> diff_shd_fwd;
    std::chrono::duration<double> diff_uni_fwd;

    class shared_int *raw;
    boost::intrusive_ptr<class shared_int> intrusive;
    std::shared_ptr<class shared_int> shared;
    std::unique_ptr<class shared_int> unique;
    class shared_int *ptr;
    size_t iteration_count;

    (void) argc;
    (void) argv;

    iteration_count = 1 * 1000 * 1000;
    seed = std::rand();

    // Allocate different types of pointers
    raw = new class shared_int;
    ptr = new class shared_int;
    intrusive = boost::intrusive_ptr<class shared_int>(ptr);
    ptr = new class shared_int;
    shared = std::shared_ptr<class shared_int>(ptr);
    ptr = new class shared_int;
    unique = std::unique_ptr<class shared_int>(ptr);

    raw->value = seed;
    intrusive->value = seed;
    shared->value = seed;
    unique->value = seed;

    // Passing argument by value
    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            use_ptr_val(raw);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_raw_val = end - beg;

    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            use_ptr_val(intrusive);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_itr_val = end - beg;

    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            use_ptr_val(shared);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_shd_val = end - beg;

    // Passing argument by reference
    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            use_ptr_ref(raw);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_raw_ref = end - beg;

    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            use_ptr_ref(intrusive);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_itr_ref = end - beg;

    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            use_ptr_ref(shared);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_shd_ref = end - beg;

    // Perfect forwarding
    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            raw = use_raw_fwd(std::move(raw));
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_raw_fwd = end - beg;

    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            intrusive = use_itr_fwd(std::move(intrusive));
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_itr_fwd = end - beg;

    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            shared = use_shd_fwd(std::move(shared));
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_shd_fwd = end - beg;

    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            unique = use_uni_fwd(std::move(unique));
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_uni_fwd = end - beg;

    DEBUG("VALUE RAW       [iteration=%zu ; time=%es]", iteration_count, diff_raw_val.count());
    DEBUG("VALUE INTRUSIVE [iteration=%zu ; time=%es]", iteration_count, diff_itr_val.count());
    DEBUG("VALUE SHARED    [iteration=%zu ; time=%es]", iteration_count, diff_shd_val.count());
    DEBUG("REFERENCE RAW       [iteration=%zu ; time=%es]", iteration_count, diff_raw_ref.count());
    DEBUG("REFERENCE INTRUSIVE [iteration=%zu ; time=%es]", iteration_count, diff_itr_ref.count());
    DEBUG("REFERENCE SHARED    [iteration=%zu ; time=%es]", iteration_count, diff_shd_ref.count());
    DEBUG("FORWARD RAW       [iteration=%zu ; time=%es]", iteration_count, diff_raw_fwd.count());
    DEBUG("FORWARD INTRUSIVE [iteration=%zu ; time=%es]", iteration_count, diff_itr_fwd.count());
    DEBUG("FORWARD SHARED    [iteration=%zu ; time=%es]", iteration_count, diff_shd_fwd.count());
    DEBUG("FORWARD UNIQUE    [iteration=%zu ; time=%es]", iteration_count, diff_uni_fwd.count());

    delete raw;

    return 0;
}
