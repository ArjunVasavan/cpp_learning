#include <iostream>

/* NOTE: lvalue and rvalue
 * lvalue -> it has name and it persist after expression
 * rvalue -> it is temporary and it dies at the end of expression
 */

int main() {
    int x = 10; /* here x is an lvalue -> it has a name and address */
    int y = x; /* x is lvalue, copied to y */
    int z = x + 5;  /* here ( x + 5 ) is an rvalue -> temporary, no name and address */
}
