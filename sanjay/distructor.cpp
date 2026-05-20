#include <any>
#include <cstdlib>
#include <iostream>
using  namespace std ;
class Car {
    public:
        int* ptr;
        ~Car() {
            cout << "Destructor called"<<endl;
            delete ptr;
        }

        Car() {
            cout << "Constructor called"<<endl;
            ptr = (int*)malloc(sizeof(int)*10);
        }
};

int main (int argc, char *argv[]) {

    {
        Car c;
        {{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}
    }

    Car c;

    return 0;
}
