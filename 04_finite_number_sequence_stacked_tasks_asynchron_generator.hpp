#include "random_number.hpp"

#include <cppcoro/async_generator.hpp>
#include <cppcoro/recursive_generator.hpp>
#include <cppcoro/sync_wait.hpp>
#include <cppcoro/task.hpp>
#include <iostream>

namespace finite_number_sequence_stacked_tasks_asynchron_generator
{
	cppcoro::async_generator<unsigned int> next_fibunacci(unsigned int maxValue)
	{
		unsigned int x = 1;
		unsigned int y = 1;
		while (y <= maxValue)
		{
			co_yield y;
			x += y;
			std::swap(x, y);
		}
	}

	//	cppcoro::async_generator<unsigned int>& relaying_task(unsigned int maxValue) noexcept { return next_fibunacci(maxValue); }
	//
	//	cppcoro::task<unsigned int> relay_item(unsigned int maxValue) noexcept
	//	{
	//	  for
	//		  co_await(const auto& s : relaying_task(stopAfter)) { co_return s; }
	//	}

	cppcoro::task<> consume_items(unsigned int maxValue) noexcept
	{
		std::cout << "fibunacci until max" << maxValue << std::endl;
	  for
		  co_await(const auto& s : next_fibunacci(maxValue)) { std::cout << "consumed item " << s << std::endl; }
	  std::cout << std::endl;
	}

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
} // namespace finite_number_sequence_stacked_tasks_asynchron_generator
