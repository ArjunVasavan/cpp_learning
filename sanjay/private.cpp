#include <iostream>

class Car {
private:
    int speed;
    int gear;
    int brake;

public:

    void print() {
        std::cout<<"Value speed: "<<speed<<std::endl;
        std::cout<<"Value gear : "<<gear<<std::endl;
        std::cout<<"Value brake: "<<brake<<std::endl;
    }

    Car() {
        std::cout<<"constructor called"<<std::endl;
    }

    Car(int s,int g,int b) {
        speed = s;
        gear = g;
        brake = b;
    }

    Car(Car &new_c) {
        speed = new_c.speed;
        gear = new_c.gear;
        brake = new_c.brake;
    }

};

int main() {

    std::cout<<"C"<<std::endl;
    Car c(10,20,30);
    c.print();

    std::cout<<std::endl;

    std::cout<<"B"<<std::endl;
    Car b = c;
    b.print();
}
