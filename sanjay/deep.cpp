#include <iostream>

class Test {
    public:
        int *ptr;

        Test(int val) {
            ptr = new int(val);
        }

        Test(const Test &t) {
            ptr = new int(*t.ptr);
        }
};

int main (int argc, char *argv[]) {
    Test t1(10);
    Test t2 = t1; // t2.ptr = t1.ptr;

    std::cout<<"T1 :"<<t1.ptr<<std::endl;
    std::cout<<"T2 :"<<t2.ptr<<std::endl;

    std::cout<<"T1 address:"<<&t1<<std::endl;
    std::cout<<"T2 address:"<<&t2<<std::endl;
}
