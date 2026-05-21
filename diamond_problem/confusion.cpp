#include <iostream>
using namespace std;

class Animal {
public:
    Animal() { cout << "Animal constructor called" << endl; }
};

class Dog : virtual public Animal {
public:
    Dog() { cout << "Dog constructor called" << endl; }
};

class Cat : virtual public Animal {
public:
    Cat() { cout << "Cat constructor called" << endl; }
};

class DogCat : public Dog, public Cat {
public:
    DogCat() { cout << "DogCat constructor called" << endl; }
};

int main() {
    DogCat dc;
    return 0;
}
