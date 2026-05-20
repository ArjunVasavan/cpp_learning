#include <iostream>
#include <thread>

void myFunction() {
    std::cout << "Thread running" << std::endl;
}

int main() {
    std::thread  t(myFunction);
    t.join();
}
