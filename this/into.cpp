#include <iostream>

/* NOTE: this-> pointer
 * Every Non Static Member function in C++ receives a 
 * hidden extra parameter.
 * a pointer to object which it was called.
 * this is called 'this'
 */

/* EXAMPLE:
 * if i write:
 *              obj.greet();
 * compiler internally treats it as:
 *              greet(&obj); // it passes address of obj secretly
 * and inside greet holds that address on 'this'
 */

class person {
    private:
        std::string name;
        int age;
    public:

        /* USE 1: Name Conflict in Constructor
         * here parameter name shadows Member name
         * without this->, both side refer to same parameter leading to Conflict
         */

        person(std::string name, int age ) {
            this->name = name;
            this->age = age;
        }

        /* USE 2: const method
         * you can read Members buy not modify
         */

        void print() const { // here it will be const this so we cannot modify this here

            std::cout << "Name : " << this->name << std::endl;
            std::cout << "Age  : " << this->age << std::endl;

            // this->age = 23; /* this will be an error because now this is const */

        }

        /* USE 3: returing *this for method chainin
         * when return type must be a reference *person not a copy
         */

        person& setName(std::string name) {
            this->name = name;
            return *this;
        }

        person& setAge(int age) {
            this->age = age;
            return *this;
        }

        /* USE 4: comparing with another object using this
         */

        bool isSamePerson(const person& other) const {
            return this == &other; /* for checking are both poiting to same object in memeory */
        }

        /* USE 5: passing yourself to a free function
         */

        void introduce() {
            greetWith(this); /* passing current objects address */
        }

        static void greetWith(person* p) {
            std::cout << "Hi my Name is " << p->name << std::endl;
        }

};

int main() {
    // --- Use 1: constructor with shadowed name ---
    person a("Alice", 30);
    person b("Bob", 25);

    a.print();   // Name: Alice, Age: 30
    b.print();   // Name: Bob,   Age: 25

    // --- Use 3: method chaining ---
    // Each setter returns *this, so you can chain calls
    a.setName("Alicia").setAge(31);
    a.print();   // Name: Alicia, Age: 31

    // --- Use 4: same object check ---
    std::cout << a.isSamePerson(a) << std::endl;   // 1 (true)  — same address
    std::cout << a.isSamePerson(b) << std::endl;   // 0 (false) — different address

    // --- Use 5: passing this to a free function ---
    b.introduce();   // Hi, I am Bob!

    return 0;
}
