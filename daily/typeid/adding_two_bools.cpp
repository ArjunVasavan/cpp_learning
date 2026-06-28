#include <iostream>

int main() {
    bool a = true;
    bool b = false;

    std::cout << "size of bool is: " << sizeof(bool) << std::endl; /* 1 */
    std::cout << "size of addition of bool is:" << sizeof(a+b) << std::endl; /* 4 */

    /* NOTE: Boolian addition size
     * the reason is that compiler doesn't know how to add bool's true or false
     * so what compiler does is it convert's 
     * true -> 1
     * false -> 0
     * where when we do addition of 1 and 0 its an integer so that's the reason
     * integer comes
     */
}
