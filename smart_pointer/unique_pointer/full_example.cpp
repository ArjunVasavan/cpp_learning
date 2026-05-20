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

void printStudent(const unique_ptr<Student> &s) {
    cout << "Name:  " << s->name  << "\n";
    cout << "Marks: " << s->marks << "\n";
}

int main() {
    unique_ptr<Student> s1 = make_unique<Student>("Vasu", 95);
    unique_ptr<Student> s2 = make_unique<Student>("Arjun", 88);

    printStudent(s1);
    printStudent(s2);

    cout << "\nMoving s1 to s3...\n";
    unique_ptr<Student> s3 = std::move(s1);

    if (!s1) cout << "s1 is empty now\n";
    printStudent(s3);

    return 0;
}
