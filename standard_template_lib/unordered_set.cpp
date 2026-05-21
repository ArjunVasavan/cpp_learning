/* NOTE: unordered_set — Quick Reference
 *
 * WHAT IT IS:
 *   A container that stores UNIQUE values with fast O(1) lookup.
 *   Internally uses a hash table — so elements have no sorted order.
 *
 * WHERE IT IS USED:
 *   - Checking if a value exists (duplicate detection)
 *   - Storing visited nodes in graph/tree problems
 *   - Storing prefixes for fast lookup (like in our prefix problem)
 *   - Removing duplicates from a collection
 *   - Anywhere you need fast "have I seen this?" checks
 *
 * HEADER REQUIRED:
 *   #include <unordered_set>
 *
 * COMMON OPERATIONS:
 *   s.insert(val)  → add a value         — O(1) avg
 *   s.count(val)   → 1 if found, 0 if not — O(1) avg
 *   s.erase(val)   → remove a value       — O(1) avg
 *   s.size()       → number of elements   — O(1)
 *
 * vs ordered set:
 *   unordered_set → O(1) lookup, no sorting  (use when order doesn't matter)
 *   set           → O(log n) lookup, sorted  (use when order matters)
 */

#include <iostream>
#include <unordered_set>
using namespace std;

int main() {

    /* Declare an unordered_set that stores integers */
    unordered_set<int> s;

    /* insert() adds a value into the set */
    s.insert(1234);
    s.insert(123);
    s.insert(12);
    s.insert(1);

    /* Duplicates are silently ignored */
    s.insert(12);   /* already exists — set stays the same */

    /* count() returns 1 if value exists, 0 if not */
    /* used like a yes/no existence check */
    if (s.count(12)) {
        cout << "12 is in the set" << endl;   /* this prints */
    }

    if (s.count(99)) {
        cout << "99 is in the set" << endl;   /* this does NOT print */
    }

    /* Loop through all elements — order is NOT guaranteed */
    /* unordered means no sorting, just fast lookup */
    for (auto val : s) {
        cout << val << " ";
    }
    cout << endl;

    /* size() tells how many unique elements are stored */
    cout << "Total elements: " << s.size() << endl;   /* prints 4 */

    /* erase() removes a value if it exists */
    s.erase(123);
    cout << "After erasing 123, size: " << s.size() << endl;   /* prints 3 */

    return 0;
}
