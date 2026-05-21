#include <iostream>
#include <system_error>
using namespace std;

/* NOTE: Virtual Constructor is IMPOSSIBLE
 * for vitual to work, C++ need to know about vtable(vitual table) of object
 * the vtable is setup during construction
 * but to construct the object, we need to know the type first
 */

/* NOTE: Virtual Distructor is possible only
 * Constructor is Not possible
 */

class animal{
    public:
        animal(); /* if you add virtual here its an error */
        /* without virtual, deleting via base pointer
         * only calls animal distructor, which causes memory leak
         */
        virtual ~animal();
};

animal::animal() {
    std::cout << "Animal Created" << std::endl;
}

animal::~animal() {
    std::cout << "Animal Distroyed" << std::endl;
}

class dog : public animal {
    public:
        dog();
        ~dog();
};

dog::dog() {
    std::cout << "Dog Created" << std::endl;
}

dog::~dog() {
    std::cout << "Dog Distroyed" << std::endl;
}

int main() {
    animal* a = new dog();
    delete a;
}
