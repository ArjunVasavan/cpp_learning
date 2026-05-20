#include <iostream>
#include <thread>

void task( int id ) {
    std::cout << "Thread ID: " << id << "running..." << std::endl;
}

int main() {
    std::thread t1(task,1);
    std::thread t2(task,2);
    std::thread t3(task,3);
    std::thread t4(task,4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}
