#include <iostream>
#include <memory>
using namespace std;

struct Box {
    Box()  { cout << "Box created\n";   }
    ~Box() { cout << "Box destroyed\n"; }
};

int main() {
    shared_ptr<Box> p1 = make_shared<Box>();
    cout << "count: " << p1.use_count() << "\n";

    {
        shared_ptr<Box> p2 = p1;
        cout << "count: " << p1.use_count() << "\n";
        cout << "p2 going out of scope...\n";
    }   // p2 dies, count drops to 1, NOT destroyed yet

    cout << "count: " << p1.use_count() << "\n";
    cout << "p1 going out of scope...\n";
    return 0;
}   // p1 dies, count = 0, NOW destroyed
