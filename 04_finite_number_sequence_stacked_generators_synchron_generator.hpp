#include "random_number.hpp"

#include <cppcoro/async_generator.hpp>
#include <cppcoro/recursive_generator.hpp>
#include <cppcoro/sync_wait.hpp>
#include <cppcoro/task.hpp>
#include <iostream>

namespace finite_number_sequence_stacked_generators_synchron_generator
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

	cppcoro::generator<unsigned int> relaying_task(unsigned int maxValue) noexcept
	{
		for (auto s : next_fibunacci(maxValue))
		{
			co_yield s;
		}
	}

	cppcoro::generator<unsigned int> relay_item(unsigned int maxValue) noexcept
	{
		for (auto s : relaying_task(maxValue))
		{
			co_yield s;
		}
	}

	void consume_items(unsigned int maxValue) noexcept
	{
		std::cout << "fibunacci until max" << maxValue << std::endl;
		for (const auto& s : relay_item(maxValue))
		{
			std::cout << "consumed item " << s << std::endl;
		}
		std::cout << std::endl;
	}

	void run()
	{
		std::cout << "finite_number_sequence_stacked_generators_synchron_generator" << std::endl << std::endl;

		consume_items(3);
		consume_items(4);
		consume_items(5);
		consume_items(25);

		std::cout << std::endl;
	}
} // namespace finite_number_sequence_stacked_generators_synchron_generator
