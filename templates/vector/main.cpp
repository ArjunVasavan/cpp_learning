#include <iostream>
#include "vector.hpp"

int main() {
    Vector<int> nums = {10, 20, 30};
    nums.push_back(40);

    for (const auto& n : nums)
        std::cout << n << ' ';   // 10 20 30 40
    std::cout << '\n';

    // bounds-checked access
    try {
        nums.at(99);
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << '\n';
    }

    // move semantics
    Vector<int> moved = std::move(nums);
    std::cout << "moved size=" << moved.size() << '\n'; // 4
    std::cout << "nums empty=" << nums.empty()  << '\n'; // 1

    return 0;
}
