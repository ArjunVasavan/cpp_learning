#include <iostream>

/* NOTE: AUTO
 * it will automatically find whats the type is supposed to be
 * there are few good things and few bad things
 */

int main() {

    int a = 5;

    auto b = 'A';

    std::cout<<b<<std::endl;
    std::cout<<b+0<<std::endl;
    std::cout<<b+a<<std::endl;
}
