//
// @brief Test unit on smart pointers
//

#include "toto.hpp"

constexpr size_t iteration_count = 10 * 1000 * 1000;
size_t hit;

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
use_val(T ptr) noexcept
{
    if (ptr->value > -1)
    {
        ++ptr->value;
    }
}

template <typename T>
__attribute__((noinline)) void
use_ref(T &ptr) noexcept
{
    if (ptr->value > -1)
    {
        ++ptr->value;
    }
}

template <typename T, void (*func)(T)>
__attribute__((noinline)) void timebox(T param, const char *msg)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> beg;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    std::chrono::duration<double> diff;

    // Execute the call several times
    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            func(param);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff = end - beg;

    if (param->value > 1234567890ul)
    {
        ++hit;
    }

    DEBUG("%s [iteration=%zu ; time=%es]", msg, iteration_count, diff.count());
}

//
// @brief Basic usage smart_ptr
//
int main(int , char **)
{
    auto raw = new struct shared_int;
    auto itr = boost::intrusive_ptr<struct shared_int>(new struct shared_int);
    auto shd = std::shared_ptr<struct shared_int>(new struct shared_int);

    raw->value = std::rand();
    itr->value = std::rand();
    shd->value = std::rand();

    timebox<struct shared_int *, use_val>(raw, "VAL RAW");
    timebox<boost::intrusive_ptr<struct shared_int>, use_val>(itr, "VAL ITR");
    timebox<std::shared_ptr<struct shared_int>, use_val>(shd, "VAL SHD");

    timebox<struct shared_int *&, use_ref>(raw, "REF RAW");
    timebox<boost::intrusive_ptr<struct shared_int>&, use_ref>(itr, "REF ITR");
    timebox<std::shared_ptr<struct shared_int>&, use_ref>(shd, "REF SHD");

    DEBUG("Number of hits [count=%zu]", hit);

    delete raw;

    return 0;
}
