#include <iostream>
#include <thread>
#include <atomic>
// NOTE: Basic operation
//
// std::atomic<int> x{10};
//
// // Read
// int val = x.load();
//
// // Write
// x.store(20);
//
// // Read + Write atomically (returns old value)
// int old = x.exchange(99);   // x becomes 99, old = 20
//
// // Arithmetic (returns old value)
// x.fetch_add(5);   // x = x + 5
// x.fetch_sub(2);   // x = x - 2

// Without atomic, this counter would have a race condition.
// Multiple threads reading/writing the same int = undefined behavior.
std::atomic<int> counter(0);  // atomic guarantees thread-safe access


void increment() {
    for (int i = 0; i < 100000; i++) {
        counter++;  // this is ONE indivisible (atomic) operation
        // no two threads can corrupt each other's write
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    // always prints 200000 — no data race, no lost updates
    std::cout << "Counter: " << counter << "\n";
    return 0;
}
