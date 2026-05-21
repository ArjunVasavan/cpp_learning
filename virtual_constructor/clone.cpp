#include <iostream>
using namespace std;

class Animal {
public:
    virtual Animal* clone() const = 0;
    virtual void    speak() const = 0;
    virtual ~Animal() {}
};

class Dog : public Animal {
private:
    string name;
public:
    Dog(string name) : name(name) {}

    Animal* clone() const override {
        return new Dog(*this);   // copy constructor — copies name too
    }
    void speak() const override {
        cout << name << " says Woof!" << endl;
    }
};

int main() {
    Animal* original = new Dog("Bruno");
    Animal* copy     = original->clone();

    original->speak();   // Bruno says Woof!
    copy->speak();       // Bruno says Woof! — full copy

    delete original;
    delete copy;
    return 0;
}
