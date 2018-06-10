//
// @brief Test unit on smart pointers
//

#include <chrono>  // now
#include <cstdlib> // rand
#include <memory>  // shared_ptr

#include <boost/intrusive_ptr.hpp> // intrusive_ptr

#include "gtest/gtest.h"

#include "toto.hpp"

int RAND;

class tu_smart_ptr : public testing::Test
{
    virtual void SetUp() override final;
    virtual void TearDown() override final;
};

void tu_smart_ptr::SetUp()
{
    RAND = std::rand();
}

void tu_smart_ptr::TearDown()
{
}

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
void use_ptr(T ptr)
{
    if (RAND > -1)
    {
        ++ptr->value;
    }
}

template <typename T>
void swap_ptr(T ptr1, T ptr2)
{
    T dummy;

    dummy = ptr1;
    ptr1 = ptr2;
    ptr2 = dummy;
}

//
// @brief Basic usage smart_ptr
//
TEST_F(tu_smart_ptr, smart_ptr)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> beg;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    std::chrono::duration<double> diff_raw;
    std::chrono::duration<double> diff_itr;
    std::chrono::duration<double> diff_shd;

    class shared_int *raw;
    boost::intrusive_ptr<class shared_int> intrusive;
    std::shared_ptr<class shared_int> shared;
    class shared_int *ptr;
    size_t iteration_count;

    iteration_count = 10 * 1000 * 1000;

    // Allocate different types of pointers
    raw = new class shared_int;
    ptr = new class shared_int;
    intrusive = boost::intrusive_ptr<class shared_int>(ptr);
    ptr = new class shared_int;
    shared = std::shared_ptr<class shared_int>(ptr);

    raw->value = RAND;
    intrusive->value = RAND;
    shared->value = RAND;

    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            use_ptr(raw);
            swap_ptr(raw, raw);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_raw = end - beg;

    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            use_ptr(intrusive);
            swap_ptr(intrusive, intrusive);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_itr = end - beg;

    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            use_ptr(shared);
            swap_ptr(shared, shared);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_shd = end - beg;

    DEBUG("COPY RAW       [iteration=%zu ; time=%es]", iteration_count, diff_raw.count());
    DEBUG("COPY INTRUSIVE [iteration=%zu ; time=%es]", iteration_count, diff_itr.count());
    DEBUG("COPY SHARED    [iteration=%zu ; time=%es]", iteration_count, diff_shd.count());

    delete raw;
}
