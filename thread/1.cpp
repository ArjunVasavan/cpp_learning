#include <iostream>
#include <thread>

static bool s_Finished = false;

void doWork() {
    while (!s_Finished) {
        std::cout<<"Working..."<<std::endl;
    }
}

int main() {

    std::thread worker(doWork);

    std::cin.get();

    s_Finished = true;

    worker.join();

    std::cin.get();
    
}
