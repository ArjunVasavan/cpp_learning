#include <iostream>

 /* base class */

class Animal {
    public:
        void speak() {
            std::cout << "Iam an Animal" << std::endl;
        }
};

 /* Here Both are inheriting animal */
class Dog : public Animal {};
class Cat : public Animal {};

 /* Inherits from both Dog and cat */

class DogCat : public Dog, public Cat {};

int main() {
    DogCat dc;
    dc.speak(); /* this is an Error as its ambigous */
}
