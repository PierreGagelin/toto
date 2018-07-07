//
// @brief Test unit on smart pointers
//

#include <chrono>  // now
#include <cstdlib> // seed
#include <memory>  // shared_ptr

#include <boost/intrusive_ptr.hpp> // intrusive_ptr

#include "toto.hpp"

struct shared_int
{
  public:
    int value;
    int ref;

    shared_int() : value(0), ref(0){};
};

inline void
intrusive_ptr_add_ref(struct shared_int *p) noexcept
{
    ++p->ref;
}

inline void
intrusive_ptr_release(struct shared_int *p) noexcept
{
    --p->ref;
    if (p->ref == 0)
    {
        delete p;
    }
}

template <typename T>
__attribute__((noinline)) void
use_ptr_val(T ptr) noexcept
{
    if (ptr->value > RAND_MAX)
    {
        ++ptr->value;
    }
}

template <typename T>
__attribute__((noinline)) void
use_ptr_ref(T &ptr) noexcept
{
    if (ptr->value > RAND_MAX)
    {
        ++ptr->value;
    }
}

template <typename T>
__attribute__((noinline)) void
use_ptr_fwd(T &&ptr) noexcept
{
    if (ptr->value > RAND_MAX)
    {
        ++ptr->value;
    }
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

    struct shared_int *raw;
    boost::intrusive_ptr<struct shared_int> intrusive;
    std::shared_ptr<struct shared_int> shared;
    struct shared_int *ptr;

    size_t iteration_count;
    int seed;

    (void)argc;
    (void)argv;

    iteration_count = 1 * 1000 * 1000;
    seed = std::rand();

    // Allocate different types of pointers
    raw = new struct shared_int;
    ptr = new struct shared_int;
    intrusive = boost::intrusive_ptr<struct shared_int>(ptr);
    ptr = new struct shared_int;
    shared = std::shared_ptr<struct shared_int>(ptr);

    raw->value = seed;
    intrusive->value = seed;
    shared->value = seed;

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
            use_ptr_fwd(std::move(raw));
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_raw_fwd = end - beg;

    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            use_ptr_fwd(std::move(intrusive));
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_itr_fwd = end - beg;

    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            use_ptr_fwd(std::move(shared));
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_shd_fwd = end - beg;

    DEBUG("VALUE RAW       [iteration=%zu ; time=%es]", iteration_count, diff_raw_val.count());
    DEBUG("VALUE INTRUSIVE [iteration=%zu ; time=%es]", iteration_count, diff_itr_val.count());
    DEBUG("VALUE SHARED    [iteration=%zu ; time=%es]", iteration_count, diff_shd_val.count());
    DEBUG("REFERENCE RAW       [iteration=%zu ; time=%es]", iteration_count, diff_raw_ref.count());
    DEBUG("REFERENCE INTRUSIVE [iteration=%zu ; time=%es]", iteration_count, diff_itr_ref.count());
    DEBUG("REFERENCE SHARED    [iteration=%zu ; time=%es]", iteration_count, diff_shd_ref.count());
    DEBUG("FORWARD RAW       [iteration=%zu ; time=%es]", iteration_count, diff_raw_fwd.count());
    DEBUG("FORWARD INTRUSIVE [iteration=%zu ; time=%es]", iteration_count, diff_itr_fwd.count());
    DEBUG("FORWARD SHARED    [iteration=%zu ; time=%es]", iteration_count, diff_shd_fwd.count());

    delete raw;

    return 0;
}
