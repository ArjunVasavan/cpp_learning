#include <iostream>

class Animal {
    public:
        virtual ~Animal();
};

Animal::~Animal() { /* This is called when object is going to be deleted */
    std::cout << "Animal Distructor called" << std::endl;
}

class Dog: public Animal {
    public:
        ~Dog();
};

Dog::~Dog(){
    std::cout << "Dog Distructor called" << std::endl;
}

int main() {
    Animal* a = new Dog(); /* Its an Dog Object But Animal Pointer */
    delete a; /* when deleting Animal is only called where as Dog is not called */
    /* NOTE: To Solve This We Are using Virtual Keyword
     * add Virtual to Animal Destructor
     * now first Dog Distructor is called then after it
     * Animal Distructor is called
     */
}

