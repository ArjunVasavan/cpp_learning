#include <iostream>
#include <string>

class Dog {
    public:
        std::string name;
        Dog(std::string n) { name = n ;}
};

int main() {
    Dog* d = new Dog("Laika");
    std::cout << "Dogs Name is : " << d->name << std::endl;
    delete d;

    Dog* dogs = new Dog[3]{{"Laika"},{"Tommy"},{"Bruno"}};
    std::cout << "Dogs Name: " << dogs[1].name << std::endl;
}
