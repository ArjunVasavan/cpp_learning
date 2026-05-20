#include <iostream>

/* NOTE: Lambda
 * its a function you write inline as a parameter without giving
 * "Any Name to it"
 * Syntax:
 * [capture](parameters) -> returntype {
 *   body
 *  }
 */

 /* normal function */

// int add ( int a, int b) {
//     return  a + b;
// }

int main() {

 /* same add function on Lambda */

    auto add = [](int a, int b) {
        return a + b;
    };
    
    std::cout << "Lambda output: " << add(10,20) << std::endl;
}
