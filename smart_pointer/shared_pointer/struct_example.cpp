#include <iostream>
#include <memory>
using namespace std;

struct Student {
    string name;
    int marks;

    Student(string n, int m) : name(n), marks(m) {
        cout << "Student " << name << " created\n";
    }
    ~Student() {
        cout << "Student " << name << " destroyed\n";
    }
};

void printStudent(shared_ptr<Student> s) {
    cout << "Name: "  << s->name  << "\n";
    cout << "Marks: " << s->marks << "\n";
    cout << "count inside function: " << s.use_count() << "\n";
}

int main() {
    shared_ptr<Student> s1 = make_shared<Student>("Vasu", 95);
    cout << "count: " << s1.use_count() << "\n";

    shared_ptr<Student> s2 = s1;
    cout << "count: " << s1.use_count() << "\n";

    printStudent(s1);

    cout << "count after function: " << s1.use_count() << "\n";
    return 0;
}
