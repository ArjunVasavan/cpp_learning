#include <iostream>
#include <atomic>
#include <thread>

// ============================================================
// memory_order_relaxed
// ============================================================
// - weakest memory ordering
// - only guarantees the operation is atomic (no torn reads/writes)
// - does NOT guarantee any ordering between threads
// - compiler/CPU can reorder these operations freely
// - use when: you only care about the final value, not order
// - example use: counters, statistics, metrics
// ============================================================

// atomic<int> — only one thread can touch this at a time
// initialized to 0
std::atomic<int> counter{0};

void increment() {
    for (int i = 0; i < 1000; i++) {

        // fetch_add — atomically adds 1 to counter, returns old value
        // memory_order_relaxed — we only want atomicity
        //                        no need to sync/coordinate with other threads
        //                        just increment safely, order doesn't matter
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {

    std::thread t1(increment); // thread 1 starts incrementing
    std::thread t2(increment); // thread 2 starts incrementing (same time)

    t1.join(); // main waits for t1 to finish
    t2.join(); // main waits for t2 to finish

    // .load() — safely reads the value from atomic
    // always prints 2000 — because fetch_add is atomic
    // even though no ordering, the increments themselves are safe
    std::cout << counter.load() << "\n";
}
