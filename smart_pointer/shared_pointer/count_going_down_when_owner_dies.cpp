#include <iostream>
#include <memory>
using namespace std;

int main() {
    shared_ptr<int> p1 = make_shared<int>(42);
    cout << "count: " << p1.use_count() << "\n";  // 1

    {
        shared_ptr<int> p2 = p1;
        cout << "count: " << p1.use_count() << "\n";  // 2

        {
            shared_ptr<int> p3 = p1;
            cout << "count: " << p1.use_count() << "\n";  // 3
        }   // p3 dies here

        cout << "count: " << p1.use_count() << "\n";  // 2
    }   // p2 dies here

    cout << "count: " << p1.use_count() << "\n";  // 1
    return 0;
}   // p1 dies here, count = 0, memory freed
