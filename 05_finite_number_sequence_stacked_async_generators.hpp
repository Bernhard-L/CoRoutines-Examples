#include "random_number.hpp"

#include <cppcoro/async_generator.hpp>
#include <cppcoro/recursive_generator.hpp>
#include <cppcoro/sync_wait.hpp>
#include <cppcoro/task.hpp>
#include <iostream>

namespace finite_number_sequence_stacked_async_generators
{
	cppcoro::generator<unsigned int> next_fibunacci(unsigned int maxValue)
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

	cppcoro::recursive_generator<unsigned int> relaying_task_recursive_1(unsigned int maxValue) noexcept
	{
		for (auto s : next_fibunacci(maxValue))
		{
			std::cout << "relaying_task_recursive-1 item " << s << std::endl;
			co_yield s;
		}
	}

	cppcoro::recursive_generator<unsigned int> relaying_task_recursive_2(unsigned int maxValue) noexcept
	{
		for (auto s : relaying_task_recursive_1(maxValue))
		{
			std::cout << "relaying_task_recursive-2 item " << s << std::endl;
			co_yield s;
		}
	}

	cppcoro::async_generator<unsigned int> relay_asyncron(unsigned int maxValue) noexcept
	{
		for (auto s : relaying_task_recursive_2(maxValue))
		{
			std::cout << "relay_asyncron item " << s << std::endl;
			co_yield s;
		}
	}

	cppcoro::task<> consume_items(unsigned int maxValue) noexcept
	{
		std::cout << "fibunacci until max" << maxValue << std::endl;
		for
			co_await(const auto& s : relay_asyncron(maxValue)) //
			{
				std::cout << "consumed item " << s << std::endl;
			}
		std::cout << std::endl;
	}

	void run()
	{
		std::cout << "finite_number_sequence_stacked_async_generators" << std::endl << std::endl;

		cppcoro::sync_wait(consume_items(3));
		cppcoro::sync_wait(consume_items(4));
		cppcoro::sync_wait(consume_items(5));
		cppcoro::sync_wait(consume_items(25));

		std::cout << std::endl;
	}
} // namespace finite_number_sequence_stacked_async_generators
