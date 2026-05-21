#include <thread>
#include <iostream>

int counter = 0;

void increment() {
    for (int i = 0; i < 100000; i++)
        counter++;  // 3 operations: load, add, store — not atomic
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << counter << "\n";  // should be 200000, never is
}
