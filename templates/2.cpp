#include <iostream>
#include <ostream>

template <typename T>
void print(T value) {
    std::cout<<value<<std::endl;
}

int main() {

    print<int>(5);
    print<int>(5.10f);
    
}
