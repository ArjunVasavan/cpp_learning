#include <iostream>

int main() {
    int* arr = new int[5];
    arr[0] = 10;
    arr[1] = 20;
    delete [] arr;
}
