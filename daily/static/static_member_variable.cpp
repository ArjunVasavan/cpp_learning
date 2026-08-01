#include <iostream>
#include <array>

/* NOTE: static member variable
 *
   Normally every object of a class gets its OWN copy of each member
   variable. A static member variable is different: ALL objects share
   the SAME single copy. It is created once, when the program starts,
   and destroyed when the program ends - it exists even if no objects
   of the class are ever created. Because it's not tied to any one
   object, it behaves like a global variable that just happens to
   belong to the class.

   Declaration (inside the class) just announces the variable exists.
   Definition (outside the class) is where memory is actually
   allocated, and it must appear exactly once in the whole program.

   Exceptions: a static const integral type, or a static constexpr
   member (C++17+), can be fully initialized right inside the class -
   no separate out-of-class definition needed.

   A member function that only touches static data can itself be
   declared static, so it can be called via the class name directly,
   without needing any object. */

class Counter {
public:
    static int count;                                  // declaration only
    static const int max_allowed = 100;                // const int: in-class init OK
    static constexpr std::array<int, 3> version{1, 0, 0}; // constexpr: in-class init OK

    int id;                                              // non-static, per-object

    Counter() {
        count++;
        id = count;
    }

    static int getCount() {   // static function, no object needed
        return count;
    }
};

int Counter::count = 0;       // out-of-class definition

int main() {
    std::cout << "Before creating any objects\n";
    std::cout << "Counter::count       = " << Counter::count << "\n";
    std::cout << "Counter::getCount()  = " << Counter::getCount() << "\n";
    std::cout << "Counter::max_allowed = " << Counter::max_allowed << "\n";
    std::cout << "Counter::version     = "
              << Counter::version[0] << "." << Counter::version[1] << "." << Counter::version[2]
              << "\n\n";

    Counter c1;
    Counter c2;
    Counter c3;

    std::cout << "After creating 3 objects\n";
    std::cout << "c1.id = " << c1.id << ", c2.id = " << c2.id << ", c3.id = " << c3.id << "\n";
    std::cout << "Counter::count      = " << Counter::count << "\n";
    std::cout << "c1.count            = " << c1.count << "  (same value, accessed via an object)\n";
    std::cout << "Counter::getCount() = " << Counter::getCount() << "  (same value, via static function)\n";

    return 0;
}
