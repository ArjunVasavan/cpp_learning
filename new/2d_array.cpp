#include <iostream>

int main() {
    int** arr = new int*[3];

    for ( int i = 0 ; i < 3; i++ ) {
        arr[i] = new int[4];
    }

    arr[0][0] = 10;

    for ( int i = 0 ; i < 3 ; i++ ) {
        delete [] arr[i];
    }

    delete [] arr;

}
