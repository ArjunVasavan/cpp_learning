#include <iostream>

template <typename T, int N>
class Array {
    private:
        T m_array[N];
    public:
        int getsize() const { return N;}
};


int main() {

    Array<float,5> array;

    std::cout<<array.getsize()<<std::endl;
    
}
