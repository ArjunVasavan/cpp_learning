#include <iostream>

int main() {
    auto greet = []() {
        std::cout << "Hello, How Are You i think  " << std::endl;
    };

    greet();
}
