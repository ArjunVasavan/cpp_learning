#include <iostream>
using namespace std;

/* decltype was introduced in C++11
   it asks compiler what TYPE is this expression
   it does NOT run the expression, just checks its type */

void part1_decltype_basics() {

    int    a = 5;
    double b = 3.2;

    /* a is int so decltype(a) gives int */
    decltype(a) x = 100;
    cout << "x = " << x << endl;

    /* b is double so decltype(b) gives double */
    decltype(b) y = 9.99;
    cout << "y = " << y << endl;

    /* int + double = double so decltype(a+b) gives double */
    decltype(a + b) z = a + b;
    cout << "z = " << z << endl;
}

/* normal function - return type written before function name */
int normalAdd(int a, int b) {
    return a + b;
}

/* trailing return type - introduced in C++11
   auto keyword means return type will be specified later
   -> int at the end is the actual return type
   both functions do exact same thing */
auto trailingAdd(int a, int b) -> int {
    return a + b;
}

/* this is where trailing return type becomes necessary
   T and U are unknown types, could be int double float anything
   we cannot write return type at front because we dont know it yet
   decltype(a + b) means whatever type a+b produces becomes return type
   a and b only exist after parameter list so we write return type there */
template<typename T, typename U>
auto smartAdd(T a, U b) -> decltype(a + b) {
    return a + b;
}

/* in C++14 you can skip the -> decltype part
   compiler figures out return type automatically
   but in C++11 we need -> decltype */
template<typename T, typename U>
auto smartAddCpp14(T a, U b) {
    return a + b;
}

int main() {

    /* part 1 - decltype basics */
    part1_decltype_basics();

    /* part 2 - normal vs trailing return type */
    cout << normalAdd(3, 4) << endl;     /* output: 7 */
    cout << trailingAdd(3, 4) << endl;   /* output: 7 */

    /* part 3 - smartAdd with different types */

    /* int + int = int */
    auto r1 = smartAdd(3, 4);
    cout << r1 << endl;       /* output: 7 */

    /* int + double = double, so result is 5.5 not 5 */
    auto r2 = smartAdd(3, 2.5);
    cout << r2 << endl;       /* output: 5.5 */

    /* double + double = double */
    auto r3 = smartAdd(1.1, 2.2);
    cout << r3 << endl;       /* output: 3.3 */

    /* part 4 - cpp14 way, no need for -> decltype */
    auto r4 = smartAddCpp14(3, 2.5);
    cout << r4 << endl;       /* output: 5.5 */

    return 0;
}
