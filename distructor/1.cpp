#include <iostream>

class Entity {

    private:
        int x;
        int y;

    public:
        Entity() {

            std::cout << "Constructor is called " << std::endl;

        };

        ~Entity() {

            std::cout << "Distructor is called " << std::endl;

        };

};

void Function() {
    Entity obj;
}

int main() {
    Entity obj;
    Function();
}
