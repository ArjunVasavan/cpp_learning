#include <algorithm>
#include <cstddef>
#include <iostream>

class buffer {

    int* data;
    size_t size;

    public:
 /* regular constructor */
    buffer(size_t s) : size(s), data(new int[s]) {};

 /* copy constructor - deep copy */

    buffer(const buffer& other ) : size(other.size), data(new int[other.size]) {
        std::copy(other.data,other.data+size,data);
    }

 /* move constructor -> steal dont copy */

    buffer (buffer&& other) : size(other.size), data(other.data) {
        other.data = nullptr; /* leave source in valid but empty state */
        other.size = 0;
    }

 /* move assignment */

    buffer& operator=(buffer&& other ) {
        if ( this != &other ) {
            delete [] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~buffer() { delete [] data;}

};

int main() {
    
}
