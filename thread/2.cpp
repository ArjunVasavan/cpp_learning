#include <iostream>
#include <ostream>
#include <thread>

static bool s_Finished = false;

void doWork() {
    using namespace std::literals::chrono_literals;
    std::cout<<"Thread is: "<<std::this_thread::get_id()<<std::endl;
    while (!s_Finished) {
        std::cout<<"Working..."<<std::endl;
        std::this_thread::sleep_for(1s); // Just sleep for an second after printing
    }
}

int main() {

    std::thread worker(doWork);
    std::cin.get();

    s_Finished = true;

    worker.join();
    std::cout<<"Thread is: "<<std::this_thread::get_id()<<std::endl;
    std::cout<<"Finished\n";
}
