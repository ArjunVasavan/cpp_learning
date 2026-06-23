#include <iostream>
using namespace std;

int arr[5] = {1, 2, 3, 4, 5};

/* auto return - returns a COPY of element
   copy means a new temporary value is created
   assigning to a temporary makes no sense
   so getCopy(0) = 99 would be an ERROR */
auto getCopy(int index) {
    return arr[index];
}

/* decltype(arr[index]) means give me exact type of arr[index]
   arr[index] is int& which is reference to int not just int
   so this function returns actual reference to array element
   that means getRef(0) = 99 directly changes arr[0] */
auto getRef(int index) -> decltype(arr[index]) {
    return arr[index];
}

/* writing int directly - perfectly fine for simple functions
   no reason to use auto -> int here */
int simpleAdd(int a, int b) {
    return a + b;
}

/* auto -> int is useful when function is part of a group
   where all functions start with auto
   makes it visually consistent and easier to scan */
auto consistentAdd(int a, int b) -> int {
    return a + b;
}

/* auto -> T means reader immediately sees it returns same type as input */
template<typename T>
auto doubleIt(T a) -> T {
    return a * 2;
}

/* without trailing - reader has to trace inside function to know return type */
auto badReadable(int a, int b) {
    return a + b;
}

/* with trailing - reader immediately sees return type without reading body */
auto goodReadable(int a, int b) -> int {
    return a + b;
}

struct MyClass {

    struct Inner {
        int value;
    };

    /* without trailing - we have to write MyClass::Inner
       which is redundant because we are already inside MyClass */
    MyClass::Inner badGet() {
        return Inner{42};
    }

    /* with trailing - Inner is already in scope here
       so we can write just Inner without MyClass:: prefix */
    auto goodGet() -> Inner {
        return Inner{42};
    }
};

/* auto deduces return type but strips reference
   so this returns a copy of x */
int x = 10;

auto returnsValue() {
    return x;
}

/* decltype(auto) keeps reference
   (x) with parentheses tells decltype it is an expression
   so this returns int& which is actual reference to x
   that means returnsRef() = 5 directly changes x */
decltype(auto) returnsRef() {
    return (x);
}

int main() {

    /* getCopy returns temporary copy so we cannot assign to it */
    getCopy(0);
    cout << arr[0] << endl;   /* output: 1, original unchanged */

    /* getRef returns reference to arr[0]
       so assigning 99 directly changes the array */
    getRef(0) = 99;
    cout << arr[0] << endl;   /* output: 99, original changed */

    /* all three do same thing just different styles */
    cout << simpleAdd(3, 4) << endl;       /* output: 7 */
    cout << consistentAdd(3, 4) << endl;   /* output: 7 */
    cout << doubleIt(5) << endl;           /* output: 10 */

    /* badReadable and goodReadable do same thing */
    cout << badReadable(3, 4) << endl;     /* output: 7 */
    cout << goodReadable(3, 4) << endl;    /* output: 7 */

    /* testing nested types */
    MyClass obj;
    MyClass::Inner i1 = obj.badGet();
    MyClass::Inner i2 = obj.goodGet();
    cout << i1.value << endl;   /* output: 42 */
    cout << i2.value << endl;   /* output: 42 */

    /* returnsRef gives reference to x so assigning 5 changes x */
    returnsRef() = 5;
    cout << x << endl;                /* output: 5 */
    cout << returnsValue() << endl;   /* output: 5 */

    return 0;
}
