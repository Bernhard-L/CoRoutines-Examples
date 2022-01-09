#pragma once

#include <random>

unsigned int random_number(unsigned int maxValue)
{
    std::random_device seed;
    std::mt19937 mtGenerator(seed());

    std::uniform_int_distribution<unsigned int> distribution(0, maxValue);
    return distribution(mtGenerator);
}

