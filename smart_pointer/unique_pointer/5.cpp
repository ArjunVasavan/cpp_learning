#include <iostream>
#include <memory>
using namespace std;

struct Person {
    string name;
    int age;
};

int main() {
    unique_ptr<Person> p = make_unique<Person>();
    p->name = "Vasu";
    p->age  = 22;

    cout << p->name << "\n";
    cout << p->age  << "\n";
    return 0;
}
