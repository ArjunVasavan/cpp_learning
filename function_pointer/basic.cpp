#include <iostream>

/* A simple function to point to */
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

/* Function that takes a function pointer as a parameter */
int compute(int a, int b, int (*operation)(int, int)) {
    return operation(a, b);
}

int main() {
    /* Declaring a function pointer */
    int (*funcPtr)(int, int) = add;

    /* Calling the function through the pointer */
    std::cout << "Add: " << funcPtr(5, 3) << std::endl;

    /* Reassigning the pointer to a different function */
    funcPtr = subtract;
    std::cout << "Subtract: " << funcPtr(5, 3) << std::endl;

    /* Passing a function pointer to another function */
    std::cout << "Compute (add): " << compute(10, 4, add) << std::endl;
    std::cout << "Compute (subtract): " << compute(10, 4, subtract) << std::endl;

    /* Array of function pointers */
    int (*operations[2])(int, int) = { add, subtract };
    std::cout << "Array call: " << operations[0](7, 2) << std::endl;
    std::cout << "Array call: " << operations[1](7, 2) << std::endl;

    /* Using typedef/using for cleaner syntax */
    using OpFunc = int (*)(int, int);
    OpFunc op = add;
    std::cout << "Using alias: " << op(6, 6) << std::endl;

    return 0;
}
