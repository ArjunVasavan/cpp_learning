#include <iostream>
#include <stdexcept>

int divide(int a, int b) {
    if (b == 0)
        throw std::runtime_error("division by zero");  // throw an exception
    return a / b;
}

int main() {
    try {
        int result = divide(10, 0);  // this throws
        std::cout << result;         // never reached
    }
    catch (const std::runtime_error& e) {
        std::cout << "caught: " << e.what() << "\n";
    }
}
