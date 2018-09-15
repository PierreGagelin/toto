//
// Test unit to try the benefit on exception safety
//

#include "toto.hpp"

// Define a class without exceptions
class toto_noexcept
{
public:
    std::string toto;
    toto_noexcept() noexcept : toto("hello world") {};

    // move constructor
    toto_noexcept(class toto_noexcept &&t) noexcept : toto(std::move(t.toto)) {};
};

// Define the same class with exceptions
class toto_except
{
public:
    std::string toto;
    toto_except() : toto("hello world") {};

    // move constructor
    toto_except(class toto_except &&t) : toto(std::move(t.toto)) {};
};

int main(int argc, char **argv)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> beg;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;

    std::chrono::duration<double> diff_ve;
    std::chrono::duration<double> diff_vne;

    std::vector<class toto_except> ve;
    std::vector<class toto_noexcept> vne;

    size_t iteration_count;

    (void) argc;
    (void) argv;

    iteration_count = 1 * 100 * 1000;

    // Fill a vector with possible exception during move construction
    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            class toto_except t;
            t.toto += std::to_string(i);
            ve.push_back(std::move(t));
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_ve = end - beg;

    // Fill a vector with no possible exception during move construction
    beg = std::chrono::high_resolution_clock::now();
    {
        for (size_t i = 0; i < iteration_count; ++i)
        {
            class toto_noexcept t;
            t.toto += std::to_string(i);
            vne.push_back(std::move(t));
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff_vne = end - beg;

    DEBUG("CONSTRUCTOR EXCEPTION    [iteration=%zu ; time=%es]", iteration_count, diff_ve.count());
    DEBUG("CONSTRUCTOR NO_EXCEPTION [iteration=%zu ; time=%es]", iteration_count, diff_vne.count());

    if ((ve.size() > 50) && (vne.size() > 50))
    {
        DEBUG("wow there's a lot of it");
    }

    return 0;
}

