#include <iostream>
#include <string>

std::string getName() {
    return "Arjun ";
}

int main() {

    auto b = getName();

    b.append("Hello");

    std::cout<<b<<std::endl;
}
