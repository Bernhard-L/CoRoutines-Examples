#include <iostream>

#include <cppcoro/generator.hpp>

#include "random_number.hpp"

namespace finite_random_number_sequence_generator {
    constexpr unsigned int _maxValue = 10;

    cppcoro::generator<unsigned int> produce_items()
    {
        auto v = random_number(_maxValue);
        while (v <= _maxValue) {
            std::cout << "produced item " << v << std::endl;
            co_yield v;
            ++v;
        }
    }

    void consume_items(unsigned int n) noexcept
    {
        std::cout << "processing up to " << n << " items" << std::endl;

        unsigned int i = 1;
        for (auto const& s : produce_items()) {
            std::cout << "consumed item " << s << std::endl;
            if (++i > n)
                break;
        }
        std::cout << std::endl;
    }

    void run()
    {
        std::cout << "finite_random_number_sequence_generator max(" << _maxValue << ")" << std::endl << std::endl;

        consume_items(3);
        consume_items(4);
        consume_items(5);

        std::cout << std::endl;
    }
}
