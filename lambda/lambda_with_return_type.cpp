#include <iostream>

int main() {

    auto divide = [](float a, float b) -> float { /* -> float means it is going to return float */
        /* change -> float return type to int to see difference */
        return a/ b;
    };

    std::cout << "Output: " << divide(10,30) << std::endl;
}
