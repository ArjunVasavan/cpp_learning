#include <iostream>
#include <ostream>

template <typename T>
void print(T value) {
    std::cout<<value<<std::endl;
}

int main() {

    print(5);
    print("Hello World");
    print(5.10);
    
}
