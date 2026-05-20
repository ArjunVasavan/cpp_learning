#include <iostream>
#include <memory>
using namespace std;

int main() {
    unique_ptr<int> p = make_unique<int>(42);

    if (p) {
        cout << "p has value: " << *p << "\n";
    }

    p.reset();

    if (!p) {
        cout << "p is empty\n";
    }
    return 0;
}
