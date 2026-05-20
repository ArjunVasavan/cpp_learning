#include <iostream>
#include <thread>

int main() {
    std::thread t([] () {
            std::cout << "Thread running from lambda" << std::endl;
            });

    t.join();
}
