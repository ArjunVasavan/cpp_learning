#include <iostream>
#include <memory>

struct Box {
    Box();
    ~Box();
};

Box::~Box() {
    std::cout << "Box Destroyed" << std::endl;
}
Box::Box() {
    std::cout << "Box Created" << std::endl;
}

int main() {

    std::cout << "Start of Main" << std::endl;

    std::unique_ptr<Box> p = std::make_unique<Box>();
    std::cout << "After Creating" << std::endl; 

}
