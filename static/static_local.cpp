#include <iostream>
using namespace std;

void counter() {
    static int count = 0;  // initialized ONCE, not every call
    count++;
    cout << "Called " << count << " times" << endl;
}

int main() {
    counter();   // Called 1 times
    counter();   // Called 2 times
    counter();   // Called 3 times
    return 0;
}
