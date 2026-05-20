#include <iostream>

void increment(int& ref) {
    ref+=1;
}
void increment(int* ref) {
    ref+=1;
}

int main() {
    int a = 5;
    int& ref = a;
    ref = 2;
    std::cout<<a<<std::endl;
    increment(ref);
    std::cout<<a<<std::endl;
    increment(&ref);
    std::cout<<a<<std::endl;

}
