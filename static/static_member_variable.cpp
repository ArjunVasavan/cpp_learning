#include <iostream>
using namespace std;

class Person {
public:
    string name;
    static int count;   // shared by ALL Person objects

    Person(string name) {
        this->name = name;
        count++;        // every new object increments the same count
    }
};

int Person::count = 0;  // must define it outside the class

int main() {
    Person a("Alice");
    Person b("Bob");
    Person c("Charlie");

    cout << Person::count << endl;   // 3 — not a.count or b.count
    return 0;
}
