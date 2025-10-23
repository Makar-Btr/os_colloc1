#include <iostream>

#include "tasks.hpp"

int main() {

    for(long long num : calculate_factorials(5))
        std::cout << num << std::endl;
    
    return 0;
}