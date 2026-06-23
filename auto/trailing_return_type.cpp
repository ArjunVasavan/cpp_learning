#include <iostream>
using namespace std;

// NORMAL FUNCTION (for comparison)
// return type 'int' is written BEFORE the function name
int normalAdd(int a, int b) {
    return a + b;
}

// TRAILING RETURN TYPE (simple example)
// 'auto' is a placeholder that says "return type is specified later"
// '-> int' at the end is the actual return type
auto trailingAdd(int a, int b) -> int {
    return a + b;
}
// Both functions above do the EXACT same thing, just different syntax

// WHERE TRAILING RETURN TYPE ACTUALLY BECOMES USEFUL
// T and U are unknown types (could be int, double, float, etc.)
template<typename T, typename U>
// We write 'auto' here because we don't know the return type yet
// a and b don't exist yet at this point ----+
//                                           |
auto smartAdd(T a, U b) -> decltype(a + b) { // <-- NOW a and b exist, so we can use them
    return a + b;                            // decltype(a+b) means "figure out what type a+b gives"
}

int main() {
    
    // calling normal function
    cout << normalAdd(3, 4) << endl;       // output: 7

    // calling trailing return type function (works the same)
    cout << trailingAdd(3, 4) << endl;     // output: 7

    // HERE'S THE MAGIC of smartAdd:
    int x = 5;
    double y = 2.3;
    
    // compiler sees int + double, so return type becomes double automatically
    auto result = smartAdd(x, y);
    cout << result << endl;                // output: 7.3  (not 7, because it's a double!)

    return 0;
}
