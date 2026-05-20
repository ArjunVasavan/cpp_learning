#include <iostream>
#include <array>

#define LOG(x) std::cout<<x<<std::endl

int main() {
    std::array<int, 5> arr;

    // initialization way
    std::array<int, 7> init_arr = {1, 2, 3, 4, 5, 6, 7};

    int unsafeVal = init_arr[0]; // fast, no safety

    int safeVal = init_arr.at(0); // safe throws error if out of range

    int size = init_arr.size();

    LOG(size);

    /* iteration
     */

    /* NOTE: for( int x : init_arr ) 
     * for each element x in init_arr
     * what does : do ->
     *                  Takes element one by one from container
     *                  internally equivalent to:
     *                  for ( auto it = arr.begin(); it != arr.end(); ++it) {
     *                      int x = *it;
     *                  }
     * here x is an copy not actually an pointer or reference
     * if we want to create in such a way so that we can modify array
     * use: 
     *     for ( int& x : arr ) -> now x is an reference
     */

    for ( int x : init_arr ) {
        LOG(x);
    }

    /* filling array
     */

    arr.fill(10);

    for ( int y : arr ) {
        LOG(y);
    }

    /* Data pointer which is important for embedded
     */

    int* ptr = arr.data(); // this gives raw pointer same as C array


}
