#include <iostream>
#include <memory>
using namespace std;

int main() {
    shared_ptr<int> p = make_shared<int>(42);
    cout << *p << "\n";
    return 0;
}
