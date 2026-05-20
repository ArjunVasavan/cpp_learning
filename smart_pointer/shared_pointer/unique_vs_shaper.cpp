#include <iostream>
#include <memory>
using namespace std;

int main() {
    // unique_ptr — cannot copy
    unique_ptr<int> u1 = make_unique<int>(10);
    // unique_ptr<int> u2 = u1;   // ERROR

    // shared_ptr — can copy
    shared_ptr<int> s1 = make_shared<int>(20);
    shared_ptr<int> s2 = s1;    // fine
    shared_ptr<int> s3 = s1;    // fine

    cout << "unique value: " << *u1 << "\n";
    cout << "shared value via s1: " << *s1 << "\n";
    cout << "shared value via s2: " << *s2 << "\n";
    cout << "shared value via s3: " << *s3 << "\n";
    cout << "shared count: " << s1.use_count() << "\n";
    return 0;
}
