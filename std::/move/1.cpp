#include <iostream>
#include <utility>
#include <vector>

/* NOTE: move
 * it converts an object into an rvalue so move semantics can happen
 * lvalue -> has a name and its stable eg: x
 * rvalue -> temporary, and can be stolen from
 * what move does it is treat x like an temporary and steals its resources
 * std::move works based on what the object contains, not where it is stored.
 * resources owning object example : vector , string, file handles, buffers
 * 
 * int x = 10; -> x is a lvalue
 * int y = x;  -> copy
 *
 */

int main() {

    std::vector<int> a = {1,2,3};
    
    std::vector<int> b  = std::move(a);

    /* What happens
     * b takes ownership of internal memeory
     * a becomes valid but empty
     * its not an deep copy so its faster
     * its just an pointer transfer
     */
}
