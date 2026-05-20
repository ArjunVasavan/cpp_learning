#include <iostream>
#include <memory>
using namespace std;

int main() {
    unique_ptr<int> p1 = make_unique<int>(42);
    unique_ptr<int> p2 = p1;   // try to copy
    return 0;
}
