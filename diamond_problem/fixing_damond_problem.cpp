#include <iostream>

 /* base class */

class Animal {
    public:
        void speak() {
            std::cout << "Iam an Animal" << std::endl;
        }
};

 /* Here Both are inheriting animal */
/* NOTE: Solving Diamond Problem
 * here we added virtual to both classes when inheriting
 */
class Dog : virtual public Animal {};
class Cat : virtual public Animal {};

 /* Inherits from both Dog and cat */

class DogCat : public Dog, public Cat {};

int main() {
    DogCat dc;
    dc.speak(); 
}
