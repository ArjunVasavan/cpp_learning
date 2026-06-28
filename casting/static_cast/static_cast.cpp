/*
 * NOTE: static_cast in C++
 * WHAT IT IS:
 *   static_cast is a compile-time cast operator in C++.
 *   It explicitly converts one type to another without any runtime overhead.
 *
 * WHAT IT DOES INTERNALLY:
 *   - Resolved entirely at compile time (no runtime type checking).
 *   - For numeric types: reinterprets or truncates the bit representation.
 *   - For pointers: adjusts the pointer offset at compile time (e.g., in inheritance).
 *   - Does NOT check if a downcast is actually safe (unlike dynamic_cast).
 *   - Generates no extra machine code for simple numeric conversions.
 *   - For bool: any non-zero becomes true (1), zero becomes false (0).
 */

#include <iostream>

/* Base class with a virtual destructor to enable polymorphism */
struct Animal {
    virtual ~Animal() {}
    virtual void speak() { std::cout << "Animal speaks\n"; }
};

/* Derived class inheriting from Animal */
struct Dog : Animal {
    void speak() override { std::cout << "Dog barks\n"; }
};

int main() {

    /* -------------------------------------------------------
     * 1. NUMERIC CONVERSION
     *    double → int: decimal part is truncated, not rounded.
     *    Internally: compiler strips the fractional bits.
     * ------------------------------------------------------- */
    double d = 9.99;
    int i = static_cast<int>(d);
    std::cout << "double 9.99 → int : " << i << "\n"; /* output: 9 */

    /* -------------------------------------------------------
     * 2. INT TO CHAR
     *    int → char: uses ASCII value of the integer.
     *    Internally: compiler narrows the int to 1 byte.
     * ------------------------------------------------------- */
    int ascii = 65;
    char ch = static_cast<char>(ascii);
    std::cout << "int 65 → char     : " << ch << "\n"; /* output: A */

    /* -------------------------------------------------------
     * 3. BOOL CONVERSION
     *    int → bool: 0 becomes false, any non-zero becomes true.
     *    bool → int: true becomes 1, false becomes 0.
     *    Internally: simple zero/non-zero check at compile time.
     * ------------------------------------------------------- */
    int n = 42;
    bool b = static_cast<bool>(n);
    std::cout << "int 42 → bool     : " << b << "\n"; /* output: 1 (true) */

    bool flag = true;
    int val = static_cast<int>(flag);
    std::cout << "bool true → int   : " << val << "\n"; /* output: 1 */

    /* -------------------------------------------------------
     * 4. UPCAST (Derived → Base)
     *    Safe and implicit, but using static_cast makes it explicit.
     *    Internally: no pointer adjustment needed (Dog IS-A Animal).
     * ------------------------------------------------------- */
    Dog dog;
    Animal* a = static_cast<Animal*>(&dog); /* Dog → Animal (safe) */
    a->speak(); /* output: Dog barks (virtual dispatch still works) */

    /* -------------------------------------------------------
     * 5. DOWNCAST (Base → Derived)
     *    Only safe if the actual object is truly a Dog.
     *    Internally: compiler adjusts pointer offset at compile time.
     *    WARNING: No runtime check — wrong cast = undefined behavior!
     * ------------------------------------------------------- */
    Animal* a2 = new Dog();
    Dog* d2 = static_cast<Dog*>(a2); /* safe: a2 actually points to a Dog */
    d2->speak(); /* output: Dog barks */
    delete a2;

    /* -------------------------------------------------------
     * 6. VOID POINTER CONVERSION
     *    void* → typed pointer: restores original type from raw memory.
     *    Internally: compiler trusts you on the type — no check done.
     * ------------------------------------------------------- */
    int x = 100;
    void* vp = &x;                          /* any pointer can become void* */
    int* ip = static_cast<int*>(vp);        /* void* → int* (you must know the type) */
    std::cout << "void* → int*      : " << *ip << "\n"; /* output: 100 */

    return 0;
}
