#include <iostream>

int main() {
    auto add = [](int a, int b) {
        return a + b;
    };

    std::cout << "Output: " << add(10,20) << std::endl;
}
