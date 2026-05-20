#include <iostream>
#include <memory>
using namespace std;

struct Box {
    Box()  { cout << "Box created\n";   }
    ~Box() { cout << "Box destroyed\n"; }
};

int main() {
    unique_ptr<Box> p = make_unique<Box>();
    cout << "before reset\n";
    p.reset();                  // delete now, p becomes null
    cout << "after reset\n";

    if (!p) {
        cout << "p is null now\n";
    }
    return 0;
}
