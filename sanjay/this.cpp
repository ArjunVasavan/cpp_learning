#include <iostream>
using namespace std;
class Car {
public:
    int speed;

    void setSpeed(int speed) {
        this->speed = speed; // (&c)->speed = speed

        // this = ( &c )
    }

    void print() {
        cout<<"value: "<<speed<<endl;
    }
};

int main (int argc, char *argv[]) {
    Car c; // created object
    c.setSpeed(100); // setSpeed(&c[this],int speed)
    c.print();
    return 0;
}
