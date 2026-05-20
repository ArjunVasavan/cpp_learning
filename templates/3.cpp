#include <iostream>
#include <iterator>
#include <memory>

template <int N>
class Array {
    private:
        int m_array[N];
    public:
        int getsize() const { return N;}
};


int main() {

    Array<5> array;

    std::cout<<array.getsize()<<std::endl;
    
}
