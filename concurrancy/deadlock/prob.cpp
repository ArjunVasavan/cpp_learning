std::mutex m1, m2;

void thread1() {
    std::lock_guard<std::mutex> l1(m1);  // locks m1
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::lock_guard<std::mutex> l2(m2);  // waits for m2 — but thread2 holds it
}

void thread2() {
    std::lock_guard<std::mutex> l2(m2);  // locks m2
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::lock_guard<std::mutex> l1(m1);  // waits for m1 — but thread1 holds it
}
// both wait forever — deadlock
