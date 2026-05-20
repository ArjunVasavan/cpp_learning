#include <iostream>
#include <thread>

int main() {
   int x = 10; 
   std::thread t( [x] () {
           std::cout << "x is " << x << std::endl;
           });
   t.join();
}
