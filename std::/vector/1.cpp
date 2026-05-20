#include <cstddef>
#include <iostream>
#include <vector>

/* NOTE: vector
 * its an dynamic array in  c++ which grows and shrinks 
 * at runtime
 */

int main() {
    std::vector<int> v = {1, 2, 3, 4 , 5} ;

    v.push_back(6); // adding 6 at the end
    v.pop_back(); // remvoing end element

    std::cout<<v[0]<<std::endl; // Access by index ( no bound checks)
    std::cout<<v.at(0)<<std::endl; // Access with bound checks ( throws if out of range )
    std::cout<<v.size()<<std::endl; // showing how much elements are currently stored

    
    std::vector<int> new_v(5,0); // created 5 elements of all 0

    int i = 3; // insert at position i = 3
    int x = 100;
    v.insert(v.begin()+i,x); // insert at an position

    v.erase(v.begin()+i); // erase at ith position

    v.clear(); // size becomes 0

    bool isEmpty = v.empty(); // returns bool

    std::cout<<v.capacity()<<std::endl; // how much memory is currently allocated

    /* Range based iteration
     */

    std::vector<int> dArr = {1,2,3,4};

    for ( int y : dArr ) {
        std::cout<<y<<" ";
    }

    std::cout<<std::endl;

    /* index based iteration
     */

    for ( size_t i = 0; i < dArr.size(); ++i) std::cout<<dArr[i]<<" ";
    std::cout<<std::endl;


    // Iterator
    for (auto it = v.begin(); it != v.end(); ++it) std::cout << *it << " ";


    /* 2D vector
     */
    // 3x4 grid initialized to 0
    std::vector< std::vector<int> > grid(3, std::vector<int>(4, 0));

    grid[1][2] = 42;
}

