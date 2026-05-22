#include <iostream>
#include <atomic>
#include <thread>

// ============================================================
// memory_order_acq_rel
// ============================================================
// - combination of acquire + release in ONE operation
// - only used on read-modify-write (RMW) operations
//   examples: fetch_add, fetch_sub, exchange, compare_exchange
// - the READ  part has acquire semantics
// - the WRITE part has release semantics
// - use when: a thread both reads AND writes atomically
//             and needs to sync with threads on BOTH sides
// - example use: passing a value through a middleman thread
// ============================================================

std::atomic<int> x{0};

// thread 1 — producer
// writes a value using release
void producer() {
    // store 42 into x
    // release — "I am done writing, 42 is ready"
    x.store(42, std::memory_order_release);
}

// thread 2 — middleman
// reads the value AND writes a new one atomically
void middleman() {
    int expected = 42;

    // compare_exchange — read x, if it equals expected, write 100
    // memory_order_acq_rel:
    //   acquire side — "I won't read until x == 42 is visible"
    //   release side — "my write of 100 is ready for consumer"
    while (!x.compare_exchange_weak(expected, 100,
                                    std::memory_order_acq_rel)) {
        expected = 42; // reset and retry if failed
    }
}

// thread 3 — consumer
// reads the final value using acquire
void consumer() {
    int val;

    // spin until x becomes 100
    // acquire — "I won't read data until middleman's write is visible"
    while ((val = x.load(std::memory_order_acquire)) != 100);

    // guaranteed to see 100 — because of acq_rel in middleman
    std::cout << val << "\n"; // always 100 ✅
}

int main() {
    std::thread t1(producer);
    std::thread t2(middleman);
    std::thread t3(consumer);

    t1.join();
    t2.join();
    t3.join();
}
