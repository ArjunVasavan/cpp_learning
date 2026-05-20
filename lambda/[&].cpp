#include <iostream>
 /* capture by reference */
int main() {
    int count = 10;
    auto increment = [&]() { /* means use the actual count variable */
        count++;
    };

    increment();
    increment();

    std::cout << "Output: " << count << std::endl;
}
