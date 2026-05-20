#include <iostream>
#include <memory>
using namespace std;

int main() {
    shared_ptr<int> p1 = make_shared<int>(42);
    cout << "count: " << p1.use_count() << "\n";  // 1

    shared_ptr<int> p2 = p1;   // copy is allowed
    cout << "count: " << p1.use_count() << "\n";  // 2
    cout << "count: " << p2.use_count() << "\n";  // 2 same count

    shared_ptr<int> p3 = p1;
    cout << "count: " << p1.use_count() << "\n";  // 3

    return 0;
}
