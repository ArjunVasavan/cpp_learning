#include <iostream>

/* NOTE: rvalue reference
 * C++11 introduced && -> a new reference type
 */

int main() {

    int x = 10;
    int& lref = x; /* lvalue reference -> binds to lvalue's */

    int&& rref = x + 10; /* rvalue reference -> binds to rvalue's only */

    /* NOTE: rvalue reference use
     * This lets you write functions with parameters using
     * rvalue reference where 
     * you know there receiving an temporary and can safely steal from it
     */
}
