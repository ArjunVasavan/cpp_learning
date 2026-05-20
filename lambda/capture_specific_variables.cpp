#include <iostream>

int main() {
    
    int x = 10;
    int y = 20;
    int z = 30;

    auto fn = [x,&y]() { /* copy x,  reference y and ignore z */
        // x = 50;  /* if you do this you will get error of not modifyiable */
        y = 50;
    };

}
