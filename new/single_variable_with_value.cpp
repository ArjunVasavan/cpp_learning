#include <iostream>

int main() {
    int* p = new int(42);
    std::cout << "Value: " << *p << std::endl;
    delete p;
}
