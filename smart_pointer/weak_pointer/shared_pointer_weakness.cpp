#include <iostream>
#include <memory> /* memory weak pointer and make shared belongs here */
using namespace std;

struct B;  // forward declaration /* telling compiler B exist and i will define it later */

struct A {
    shared_ptr<B> bPtr; /* a shared pointer that points to B object  */
    ~A() { cout << "A destroyed\n"; }
};

struct B {
    shared_ptr<A> aPtr;  // <-- this causes the problem
    ~B() { cout << "B destroyed\n"; }
};

int main() {
    shared_ptr<A> a = make_shared<A>(); /* creats object A in heap Memory */
    shared_ptr<B> b = make_shared<B>(); /*  */

    a->bPtr = b;   // A holds B
    b->aPtr = a;   // B holds A  <-- circular reference!

    // ref count of a = 2, ref count of b = 2
    // when main ends, count drops to 1 each, never 0
    // so destructors NEVER called = MEMORY LEAK

    cout << "a use count: " << a.use_count() << endl;  // 2
    cout << "b use count: " << b.use_count() << endl;  // 2

    return 0;
    // neither "A destroyed" nor "B destroyed" prints!
}
