#include <iostream>

class Animal {
    public:
        ~Animal();
};

Animal::~Animal() { /* This is called when object is going to be deleted */
    std::cout << "Distructor called" << std::endl;
}

int main() {

}
