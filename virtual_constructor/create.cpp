#include <iostream>
using namespace std;

class Animal {
public:
    virtual Animal* create() const = 0;   // "virtual constructor"
    virtual void    speak()  const = 0;
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    Animal* create() const override {
        return new Dog();   // knows to create a Dog
    }
    void speak() const override {
        cout << "Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    Animal* create() const override {
        return new Cat();   // knows to create a Cat
    }
    void speak() const override {
        cout << "Meow!" << endl;
    }
};

int main() {
    Animal* a = new Dog();

    // We only know it's an Animal*, but create() makes the right type
    Animal* b = a->create();

    a->speak();   // Woof!
    b->speak();   // Woof! — b is a Dog too, even though we used Animal*

    delete a;
    delete b;
    return 0;
}
