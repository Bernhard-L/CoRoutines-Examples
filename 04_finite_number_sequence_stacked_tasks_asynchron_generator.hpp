#include <iostream>

#include <cppcoro/async_generator.hpp>
#include <cppcoro/recursive_generator.hpp>
#include <cppcoro/sync_wait.hpp>
#include <cppcoro/task.hpp>

#include "random_number.hpp"

namespace finite_number_sequence_stacked_tasks_asynchron_generator {
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

  //  cppcoro::recursive_generator<unsigned int> relay_item(unsigned int stopAfter) noexcept
  //  {
  //      co_yield next_fibunacci(stopAfter);
  //  }
  //
  //  cppcoro::task<> consume_items(unsigned int stopAfter) noexcept
  //  {
  //    std::cout << "stopping after the next fibunacci after " << stopAfter << std::endl;
  //      for
  //          co_await(const auto & s
  //                   : relay_item(stopAfter))
  //          {
  //              std::cout << "consumed item " << s << std::endl;
  //          }
  //      std::cout << std::endl;
  //  }
  //
    void run()
    {
        std::cout << "finite_number_sequence_stacked_tasks_asynchron_generator" << std::endl << std::endl;
  //
  //      cppcoro::sync_wait(consume_items(3));
  //      cppcoro::sync_wait(consume_items(4));
  //      cppcoro::sync_wait(consume_items(5));
  //      cppcoro::sync_wait(consume_items(25));
  //
        std::cout << std::endl;
    }
}
