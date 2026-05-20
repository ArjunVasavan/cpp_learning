#include <iostream>
#include <memory>
using namespace std;

void printValue(shared_ptr<int> p) {
    cout << "inside function, count: " << p.use_count() << "\n";
    cout << "value: " << *p << "\n";
}

int main() {
    shared_ptr<int> p = make_shared<int>(42);
    cout << "before function, count: " << p.use_count() << "\n";

    printValue(p);   // copy is made, count goes up inside function

    cout << "after function, count: " << p.use_count() << "\n";
    return 0;
}
