#include <iostream>
#include <memory>

int main() {

    std::unique_ptr<int> p = std::make_unique<int>(42);
    std::cout << "Output: " << *p << std::endl;
    
}
