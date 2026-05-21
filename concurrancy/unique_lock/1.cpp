std::mutex mtx;

void foo() {
    std::unique_lock<std::mutex> lock(mtx);  // locked

    // do some work
    lock.unlock();   // manually unlock early

    // do work that doesn't need the lock

    lock.lock();     // re-lock
    // more protected work
}   // released on destruction
