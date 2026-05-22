#include <iostream>
#include <atomic>

/* NOTE: CAS - compare_exchange_strong
 * "Change the value only if it's still what I last saw. If someone else changed it, tell me and I'll retry."
 */

int main() {
    std::atomic<int> x{5};

    int expected = 5;
    bool ok = x.compare_exchange_strong(expected, 99);

    // x was 5, expected was 5 → match! → x becomes 99
    std::cout << ok  << "\n";  // 1 (true)
    std::cout << x   << "\n";  // 99
}
