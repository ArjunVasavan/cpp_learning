#include <iostream>

/* 
 * Function: foo
 * Takes two boolean parameters and returns their sum.
 * 'auto' return type is deduced at compile time.
 * Adding two bools promotes them to 'int' (true=1, false=0),
 * so the return type will be deduced as 'int'.
 */
auto foo(bool n, bool m) {
    return n + m;
}

int main() {
    bool a = true;
    bool b = true;

    auto c = a + b;

    std::cout << c << " -> Type is: " << typeid(c).name() << std::endl;
    std::cout << c << " " << foo(a, b) << std::endl;

    return 0;
}
