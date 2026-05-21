#include <mutex>

std::mutex mtx;

void increment() {
    for (int i = 0; i < 100000; i++) {
        std::lock_guard<std::mutex> lock(mtx);  // locks on construction
        counter++;
        // lock released automatically when lock goes out of scope
        // even if exception throws — RAII saves you
    }
}
