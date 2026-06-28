#include <iostream>
#include <typeinfo> /* required header for typeid */

/* Function: foo
 * Takes two boolean parameters and returns their sum.
 */
auto foo(bool n, bool m) {
    return n + m;
}

int main() {

    bool a = true;
    bool b = true;

    auto c = a + b;

    /* NOTE: typeid(c).name() reveals the actual deduced type of 'c' at runtime.
     *       Even though 'a' and 'b' are bool, bool + bool promotes to int,
     *       so typeid will report 'i' (int) not 'b' (bool). */
    std::cout << "type of c      : " << typeid(c).name() << std::endl;

    /* NOTE: typeid on the expression (a + b) directly also gives int,
     *       confirming that arithmetic on bools yields int, not bool. */
    std::cout << "type of a+b    : " << typeid(a + b).name() << std::endl;

    /* NOTE: typeid(a) on a plain bool variable gives 'b' (bool),
     *       because no promotion happens without an arithmetic operation. */
    std::cout << "type of a      : " << typeid(a).name() << std::endl;

    /* NOTE: typeid on foo(a,b) return value confirms auto deduced int,
     *       since the function returns n + m which is int. */
    std::cout << "type of foo()  : " << typeid(foo(a, b)).name() << std::endl;

    std::cout << c << " " << foo(a, b) << std::endl;

    return 0;
}
