void thread1() {
    std::lock_guard<std::mutex> l1(m1);  // m1 first
    std::lock_guard<std::mutex> l2(m2);  // m2 second
}

void thread2() {
    std::lock_guard<std::mutex> l1(m1);  // m1 first — same order
    std::lock_guard<std::mutex> l2(m2);  // m2 second
}
