#include <iostream>
using namespace std;

/* FLAW 1: writing decltype(a+b) at front
   a and b are not known yet when compiler reads front
   this will give ERROR */
/*
template<typename T, typename U>
decltype(a + b) badAdd(T a, U b) {
    return a + b;
}
*/

/* FLAW 1 FIXED: use trailing return type
   now a and b are already known when compiler reaches -> decltype(a+b) */
template<typename T, typename U>
auto goodAdd(T a, U b) -> decltype(a + b) {
    return a + b;
}


/* FLAW 2: writing T as return type at front
   T is only the type of a
   if b is bigger type like double, result gets cut off
   this compiles fine but gives WRONG answer */
template<typename T, typename U>
T badTAdd(T a, U b) {
    return a + b;   /* double gets cut to int here, loses decimal */
}

/* FLAW 2 FIXED: use decltype(a+b) so compiler finds actual correct type */
template<typename T, typename U>
auto goodTAdd(T a, U b) -> decltype(a + b) {
    return a + b;   /* now double stays double, no information lost */
}


/* FLAW 3: not using trailing return type in cpp11
   in cpp11 we NEED -> decltype to get correct return type
   in cpp14 compiler can figure it out automatically with just auto */
template<typename T, typename U>
auto cpp14Add(T a, U b) {
    return a + b;   /* works in cpp14 and above only */
}


int main() {

    /* testing FLAW 1 fix */
    auto r1 = goodAdd(3, 2.5);
    cout << "FLAW 1 FIXED - int + double = " << r1 << endl;   /* output: 5.5 */

    /* testing FLAW 2 - wrong behavior */
    auto r2 = badTAdd(3, 2.5);
    cout << "FLAW 2 WRONG - int + double = " << r2 << endl;   /* output: 5 not 5.5 */

    /* testing FLAW 2 fix */
    auto r3 = goodTAdd(3, 2.5);
    cout << "FLAW 2 FIXED - int + double = " << r3 << endl;   /* output: 5.5 */

    /* testing FLAW 3 - cpp14 way */
    auto r4 = cpp14Add(3, 2.5);
    cout << "FLAW 3 cpp14 - int + double = " << r4 << endl;   /* output: 5.5 */

    return 0;
}
