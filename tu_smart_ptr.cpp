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
void use_ptr_val(T ptr) __attribute__((noinline));
template <typename T>
void use_ptr_val(T ptr)
{
    if (RAND > RAND_MAX)
    {
        ++ptr->value;
    }
}

template <typename T>
void use_ptr_ref(T &ptr) __attribute__((noinline));
template <typename T>
void use_ptr_ref(T &ptr)
{
    if (RAND > RAND_MAX)
    {
        ++ptr->value;
    }
}

//
// @brief Basic usage smart_ptr
//
TEST_F(tu_smart_ptr, smart_ptr)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> beg;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;

    std::chrono::duration<double> diff_raw_val;
    std::chrono::duration<double> diff_itr_val;
    std::chrono::duration<double> diff_shd_val;
    std::chrono::duration<double> diff_raw_ref;
    std::chrono::duration<double> diff_itr_ref;
    std::chrono::duration<double> diff_shd_ref;

    class shared_int *raw;
    boost::intrusive_ptr<class shared_int> intrusive;
    std::shared_ptr<class shared_int> shared;
    class shared_int *ptr;
    size_t iteration_count;

    iteration_count = 100 * 1000 * 1000;

    // Allocate different types of pointers
    raw = new class shared_int;
    ptr = new class shared_int;
    intrusive = boost::intrusive_ptr<class shared_int>(ptr);
    ptr = new class shared_int;
    shared = std::shared_ptr<class shared_int>(ptr);

    raw->value = RAND;
    intrusive->value = RAND;
    shared->value = RAND;

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

    DEBUG("VALUE RAW       [iteration=%zu ; time=%es]", iteration_count, diff_raw_val.count());
    DEBUG("VALUE INTRUSIVE [iteration=%zu ; time=%es]", iteration_count, diff_itr_val.count());
    DEBUG("VALUE SHARED    [iteration=%zu ; time=%es]", iteration_count, diff_shd_val.count());
    DEBUG("REFERENCE RAW       [iteration=%zu ; time=%es]", iteration_count, diff_raw_ref.count());
    DEBUG("REFERENCE INTRUSIVE [iteration=%zu ; time=%es]", iteration_count, diff_itr_ref.count());
    DEBUG("REFERENCE SHARED    [iteration=%zu ; time=%es]", iteration_count, diff_shd_ref.count());

    delete raw;
}
