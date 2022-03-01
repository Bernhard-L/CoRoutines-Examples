// CoroTest.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>

#include "01_simple_number_sequence_asynchron_generator.hpp"
#include "02_finite_random_number_sequence_generator.hpp"
#include "03_finite_random_number_sequence_asynchron_generator.hpp"
#include "04_finite_number_sequence_stacked_tasks_asynchron_generator.hpp"

int main()
{
    // finite_random_number_sequence_generator::run();
    // finite_random_number_sequence_asynchron_generator::run();
    simple_number_sequence_asynchron_generator::run();
    finite_number_sequence_stacked_tasks_asynchron_generator::run();

    std::cout << std::endl
              << std::endl;
}
