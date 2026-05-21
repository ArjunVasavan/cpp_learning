#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::queue<int> dataQueue;
std::mutex mtx;
std::condition_variable cv;
bool done = false;

void producer() {
    for (int i = 0; i < 5; i++) {
        std::unique_lock<std::mutex> lock(mtx);
        dataQueue.push(i);
        std::cout << "produced: " << i << "\n";
        cv.notify_one();  // wake up consumer
    }
    std::unique_lock<std::mutex> lock(mtx);
    done = true;
    cv.notify_one();
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        // wait releases lock and sleeps until notified
        // re-acquires lock before continuing
        cv.wait(lock, [] { return !dataQueue.empty() || done; });

        while (!dataQueue.empty()) {
            std::cout << "consumed: " << dataQueue.front() << "\n";
            dataQueue.pop();
        }

        if (done) break;
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}
