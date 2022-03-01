#include <iostream>

#include <cppcoro/async_generator.hpp>
#include <cppcoro/sync_wait.hpp>
#include <cppcoro/task.hpp>

#include "random_number.hpp"

namespace finite_random_number_sequence_asynchron_generator {
    constexpr unsigned int _maxValue = 10;

    cppcoro::task<unsigned int> random_value(unsigned int maxValue)
    {
        co_return random_number(maxValue);
    }

    cppcoro::async_generator<unsigned int> produce_items()
    {
        auto v = co_await random_value(_maxValue);
        while (v <= _maxValue) {
            std::cout << "produced item " << v << std::endl;
            co_yield v;
            ++v;
        }
    }

    cppcoro::task<> consume_items(unsigned int n) noexcept
    {
        std::cout << "processing up to " << n << " items" << std::endl;

        unsigned int i = 1;
        for
            co_await(auto const& s
                     : produce_items())
            {
                std::cout << "consumed item " << s << std::endl;
                if (++i > n)
                    break;
            }
        std::cout << std::endl;
    }

    void run()
    {
        std::cout << "finite_random_number_sequence_asynchron_generator max(" << _maxValue << ")" << std::endl << std::endl;

        cppcoro::sync_wait(consume_items(3));
        cppcoro::sync_wait(consume_items(3));
        cppcoro::sync_wait(consume_items(3));
        cppcoro::sync_wait(consume_items(4));
        cppcoro::sync_wait(consume_items(5));

        std::cout << std::endl;
    }
}
