#include <future>
#include <iostream>

int heavyComputation(int x) {
    return x * x;  // imagine this takes time
}

int main() {
    // launch in separate thread
    std::future<int> result = std::async(std::launch::async, heavyComputation, 10);

    std::cout << "doing other work...\n";

    // block here until result is ready
    std::cout << "result: " << result.get() << "\n";  // prints 100
}
