// RunAdder.cpp

#include <iostream>

#include "Adder.h"
#include <tbb/tbb.h>

int main() {
    Adder adder;
    adder.print_value(std::cout);
    adder.add(5);
    adder.print_value(std::cout);
    adder.add(5);
    adder.print_value(std::cout);
    adder.clear();
    return 0;
}
