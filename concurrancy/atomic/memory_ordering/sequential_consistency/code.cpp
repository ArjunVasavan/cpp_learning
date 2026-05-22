#include <iostream>
#include <atomic>
#include <thread>

// ============================================================
// memory_order_seq_cst  (Sequential Consistency)
// ============================================================
// - strongest memory ordering
// - ALL threads see ALL atomic operations in the SAME order
// - this is the DEFAULT if you don't specify any ordering
// - acts like a global lock on the order of operations
// - every seq_cst operation has an implicit WALL on both sides
//   (both acquire AND release built in)
// - use when: you are unsure which ordering to use
//             or correctness is more important than performance
// - downside: slowest of all orderings
// ============================================================

std::atomic<bool> x{false};
std::atomic<bool> y{false};
std::atomic<int>  result{0};

void write_x() {
    // store true into x
    // seq_cst — every thread will see this in the same global order
    x.store(true, std::memory_order_seq_cst);
}

void write_y() {
    // store true into y
    // seq_cst — every thread will see this in the same global order
    y.store(true, std::memory_order_seq_cst);
}

void read_x_then_y() {
    // wait until x is true
    while (!x.load(std::memory_order_seq_cst));

    // now check y
    if (!y.load(std::memory_order_seq_cst)) {
        // x was true but y was false
        // this is a valid observation
        result.fetch_add(1, std::memory_order_relaxed);
    }
}

void read_y_then_x() {
    // wait until y is true
    while (!y.load(std::memory_order_seq_cst));

    // now check x
    if (!x.load(std::memory_order_seq_cst)) {
        // y was true but x was false
        // this is a valid observation
        result.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {
    std::thread t1(write_x);
    std::thread t2(write_y);
    std::thread t3(read_x_then_y);
    std::thread t4(read_y_then_x);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // with seq_cst — result is never 2
    // because all threads agree on the same order of x and y stores
    // so it is impossible for BOTH threads to see the other flag as false
    std::cout << result.load() << "\n"; // 0 or 1, never 2 ✅
}
