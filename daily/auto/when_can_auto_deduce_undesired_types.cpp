#include <iostream>
#include <vector>

/* NOTE: When can auto deduce undesired type
 * "Invisible" proxy can cause auto to deduce the wrong type for an initializer expression.
 * One such type is std::vector<bool>.
 *
 * std::vector<bool> is a SPECIAL CASE in C++ — it does NOT store actual bools.
 * Instead it stores bits (1 bit per bool to save memory).
 * So when you do foo()[2], it doesn't return a bool&
 * it returns a special proxy object: std::vector<bool>::reference
 *
 * PROBLEM:
 * If you use auto to save foo()[2], auto deduces the proxy type, NOT bool.
 * foo() returns a temporary vector. After the line ends, the vector is DESTROYED.
 * Now your proxy object is pointing to DESTROYED MEMORY → Undefined Behaviour!
 *
 * SOLUTION:
 * Explicitly type the variable as bool instead of using auto.
 * This forces the proxy to convert to a real bool immediately,
 * before the temporary vector is destroyed.
 */

std::vector<bool> foo() {
    return {true, false, true, true, false};
}

void bar(bool b) {
    std::cout << std::boolalpha << b << std::endl;
}

int main() {
    //  BAD: auto deduces std::vector<bool>::reference (a proxy), NOT bool
    // The temporary vector from foo() is destroyed after this line
    // somebit is now a dangling proxy → Undefined Behaviour!
    auto somebit = foo()[2];
    bar(somebit);  // UB! proxy points to destroyed memory

    //  GOOD: explicitly use bool
    // The proxy is immediately converted to a real bool
    // before the temporary vector is destroyed
    bool safebit = foo()[2];
    bar(safebit);  // perfectly safe!
}
