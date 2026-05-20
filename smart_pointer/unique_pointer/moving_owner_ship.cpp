#include <iostream>
#include <memory>
using namespace std;

int main() {
    unique_ptr<int> p1 = make_unique<int>(42);
    cout << "p1 points to: " << p1.get() << "\n";

    unique_ptr<int> p2 = std::move(p1);   // transfer ownership
    cout << "p2 points to: " << p2.get() << "\n";
    cout << "p1 points to: " << p1.get() << "\n";  // null now

    cout << "value via p2: " << *p2 << "\n";
    return 0;
}
