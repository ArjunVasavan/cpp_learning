#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> l = {10, 20, 30};

    l.push_front(5);       // add at front
    l.push_back(40);       // add at end
    l.pop_front();         // remove front
    l.pop_back();          // remove end

    l.insert(next(l.begin(), 1), 99);  // insert at index 1
    l.remove(20);                       // remove by value

    for (int x : l)
        cout << x << " -> ";
    cout << "NULL\n";

    l.reverse();
    l.sort();

    return 0;
}
