#include <iostream>

#include <cppcoro/async_generator.hpp>
#include <cppcoro/sync_wait.hpp>
#include <cppcoro/task.hpp>

#include "random_number.hpp"

namespace simple_number_sequence_asynchron_generator {
    cppcoro::async_generator<unsigned int> next_fibunacci(unsigned int stopAfter)
    {
        unsigned int x = 0;
        unsigned int y = 1;
        while (y < stopAfter)
        {
            x += y;
            std::swap(x, y);
            co_yield y;
        }
    }

    cppcoro::task<> consume_items(unsigned int stopAfter) noexcept
    {
        std::cout << "stopping after the next fibunacci after " << stopAfter << std::endl;

        for
            co_await(auto const& s
                     : next_fibunacci(stopAfter))
            {
                std::cout << "consumed item " << s << std::endl;
            }
        std::cout << std::endl;
    }

    void run()
    {
        std::cout << "simple_number_sequence_asynchron_generator" << std::endl << std::endl;

        cppcoro::sync_wait(consume_items(3));
        cppcoro::sync_wait(consume_items(4));
        cppcoro::sync_wait(consume_items(5));
        cppcoro::sync_wait(consume_items(25));

        std::cout << std::endl;
    }
}
