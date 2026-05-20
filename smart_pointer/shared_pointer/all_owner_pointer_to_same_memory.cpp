#include <iostream>
#include <memory>
using namespace std;

int main() {
    shared_ptr<int> p1 = make_shared<int>(42);
    shared_ptr<int> p2 = p1;
    shared_ptr<int> p3 = p1;

    cout << "p1 address: " << p1.get() << "\n";
    cout << "p2 address: " << p2.get() << "\n";
    cout << "p3 address: " << p3.get() << "\n";

    // change value through p1
    *p1 = 100;

    // all see the change
    cout << "p1 value: " << *p1 << "\n";
    cout << "p2 value: " << *p2 << "\n";
    cout << "p3 value: " << *p3 << "\n";
    return 0;
}
