#include <iostream>

void increment(int& ref) {
    ref+=1;
}
void increment(int* ref) {
    ref+=1;
}

int main() {
    int a = 5;
    int b = 6;
    int& ref = a;
    ref = b; // -> a = b is happened
    std::cout<<a<<std::endl;
    increment(ref);
    std::cout<<a<<std::endl;
    increment(&ref);
    std::cout<<a<<std::endl;

}
