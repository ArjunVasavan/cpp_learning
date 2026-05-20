#include <iostream>

/* NOTE: How to use template when returning
 */

template <typename  T> // "Hey Compiler, T is an template parameter"
class Entity {
    private:
        T element;
    public:
        Entity(T e);
        T divideBy2();
};


template <typename T> // must repeat is defination is independent
Entity<T>::Entity( T e) :element(e){}

template <typename T>
T Entity<T>::divideBy2() {
    return element/2;
}

int main() {
    Entity<int> obj(10);
    std::cout<< "Result: " << obj.divideBy2() << std::endl;
}
