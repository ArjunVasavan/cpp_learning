#include <iostream>
using namespace std;

class MathHelper {
public:
    static int square(int x) {
        return x * x;    // no this, no member variables
    }

    static int cube(int x) {
        return x * x * x;
    }
};

int main() {
    cout << MathHelper::square(4) << endl;   // 16
    cout << MathHelper::cube(3)   << endl;   // 27

    // You don't need any object to call it
    return 0;
}
