#include <iostream>

 /* Capture by Value */

int main() {

    int x = 10;
    int y = 20;

    auto add = [=]() { /* = means copy x and y into lambda */
        return x + y;
    };
    
    std::cout << "Output:" << add() << std::endl;
}
