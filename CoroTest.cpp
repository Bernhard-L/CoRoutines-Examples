// CoroTest.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <format>
#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <time.h>
#include <random>

// #include <future>
// #include <coroutine>

#include <cppcoro/async_generator.hpp>
#include <cppcoro/generator.hpp>
#include <cppcoro/task.hpp>
#include <cppcoro/sync_wait.hpp>

#include <windows.h>

constexpr int _maxValue = 20;

void print_time()
{
    std::cout << std::format("{} \t ", std::chrono::system_clock::now()) << std::flush;
}

cppcoro::task<std::chrono::seconds> randomSeconds()
{
    co_return std::chrono::seconds(1 + rand() % 5 );
}

int random_value_synchron()
{
    std::random_device seed;
    std::mt19937 mtGenerator(seed());

    std::uniform_int_distribution<unsigned int> distribution(0, _maxValue);
    auto randomNumber = std::bind(distribution, mtGenerator);
    return randomNumber();
}

cppcoro::task<int> random_value()
{
    co_return random_value_synchron();
}

cppcoro::async_generator<std::string> produce_items()
{
    auto v = co_await random_value();
    while (v <= _maxValue) {
        using namespace std::string_literals;
        auto i = "item "s + std::to_string(v);
        print_time();
        std::cout << "produced " << i << '\n';
        co_yield i;
        ++v;
    }
}

cppcoro::generator<int> generatorForNumbers(int begin, int inc = 1)
{
    for (int i = begin;; i += inc) {
        co_yield i;
    }
}

cppcoro::task<> consume_items(int const n)
{
    int i = 1;
    for co_await(auto const& s : produce_items())
    {
        print_time();
        std::cout << "consumed " << s << '\n';
        if (++i > n)
            break;
    }
}

cppcoro::generator<std::string> produce_items_synchron()
{
    auto v = random_value_synchron();
    while (v <= _maxValue) {
        using namespace std::string_literals;
        auto i = "item "s + std::to_string(v);
        print_time();
        std::cout << "produced synchron " << i << '\n';
        co_yield i;
        ++v;
    }
}

void consume_items_synchron(int const n) noexcept
{
    int i = 1;
    for (auto const& s : produce_items_synchron())
    {
        print_time();
        std::cout << "consumed synchron " << s << '\n';
        if (++i > n)
            break;
    }
}


int main()
{
    std::cout << std::endl;

    consume_items_synchron(5);
    std::cout << "\n\n";
    consume_items_synchron(3);
    std::cout << "\n\n";
    consume_items_synchron(3);
    std::cout << "\n\n";
    cppcoro::sync_wait(consume_items(5));
    std::cout << "\n\n";
    cppcoro::sync_wait(consume_items(3));
    std::cout << "\n\n";
    cppcoro::sync_wait(consume_items(3));

    std::cout << "\n\n";
}
