std::atomic<bool> flag(false);

void setter() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    flag.store(true);
}

void checker() {
    while (!flag.load())
        std::this_thread::yield();  // give up CPU slice, don't busy spin hard
    std::cout << "flag is set\n";
}
