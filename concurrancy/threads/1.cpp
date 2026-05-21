#include <iostream>
#include <thread>

void task(int id) {
    std::cout << "thread " << id << " running\n";
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);

    t1.join();  // main waits for t1 to finish
    t2.join();  // main waits for t2 to finish

    std::cout << "both done\n";
}
