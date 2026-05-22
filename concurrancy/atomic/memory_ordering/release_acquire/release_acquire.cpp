#include <iostream>
#include <atomic>
#include <thread>

// ============================================================
// memory_order_release  (used on stores / writes)
// memory_order_acquire  (used on loads  / reads)
// ============================================================
// - these two always work as a PAIR
// - release → "I am done writing, data is ready"
//             nothing written BEFORE release can move AFTER it
// - acquire → "I will not read anything until this load is done"
//             nothing read AFTER acquire can move BEFORE it
// - together they create a safe handoff point between threads
// - use when: one thread produces data, another thread consumes it
// ============================================================

int data = 0;                    // normal variable — not atomic
std::atomic<bool> ready{false};  // flag to signal between threads

void writer() {
    // step 1: write the actual data first
    data = 42;

    // step 2: signal that data is ready
    // memory_order_release — acts as a WALL
    //   everything written ABOVE this line (data = 42)
    //   is guaranteed to be visible BEFORE this store
    //   no reordering allowed above this point
    ready.store(true, std::memory_order_release);
}

void reader() {
    // wait until writer signals ready
    // memory_order_acquire — acts as a WALL
    //   everything read BELOW this line (data)
    //   is guaranteed to happen AFTER this load
    //   no reordering allowed below this point
    while (!ready.load(std::memory_order_acquire));

    // safe to read data now
    // guaranteed to see 42 — because of release/acquire pair
    std::cout << data << "\n"; // always 42 ✅
}

int main() {
    std::thread t1(writer);
    std::thread t2(reader);

    t1.join();
    t2.join();
}
