#include <iostream>

int main() {
    
    auto a = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout << "size of auto initialized with curly braces is: " << sizeof(a) << std::endl;

    std::cout << "The reason is it becomes std::initalizer_list<...> type" << std::endl;

}
