#include <cmath>
#include <iostream>
#include <string>
#include <thread>

void printNumer( int n, std::string message) {
    std::cout << "printNumer: " << message << " " << n << std::endl;
}

int main() {
    std::thread t(printNumer, 42, "number is ");
    /* Arguments go directly after the function */
    t.join();
}
