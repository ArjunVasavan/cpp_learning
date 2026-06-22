#include <iostream>

/* NOTE: auto type deduction
 * auto type deduction is same as template type deduction
 * but auto type deduction assumes that a braced initializer represent a std::initializer_list
 * a template type deduction doesn't hold such premises
 */

int main() {
    
    int* ip;
    auto aip = ip; /* aip is a pointer to an integer */

    const int* cip;
    auto acip = cip; /* acip is a pointer to const integer ( the value cannot be modified but memory address can be modified) */


    const int* const cicp = ip;
    auto acicp = cicp; /* acicp is still a pointer pointing to a constant integer, the constantness of pointer is discarded */

    auto x = 27; /* x is neither a pointer nor a reference, x's type is int */
    const auto cx = x; /* cx is neither a pointer nor a reference, cs's type is const int */

    const auto &rx = x; /* rx is a non universal reference, rx is an reference to an constant integer  */

    auto&& uref1 = x; /* x is integer and lvalue, so uref1's type is int& */

    auto&& uref2 = cx;  /* cx is a const int and an lvalue,  so uref2's type is const int & */

    /* NOTE: && -> move semantics
     * & -> is for copy in reference
     * && -> is for moving the data to new reference here thus older moved data will be empty ( happens only for rvalue's)
     */

    auto&& uref3 = 27; /* 27 is an integer and an rvalue, so our uref3's type is int&& */

    auto x3 = {24}; /* type is std::initializer_list<int> , value is {24} */

    // auto x4 = {1,2.0}; /* error! cannot deduce T for std::initializer_list<t>  */
    
    /* NOTE: auto creating initializer_list
     * as you can see if you use braced initializers, auto is forces to create 
     * a varible of type std::initializer_list<t>,
     * if it cannot deduce the type of t, then it's shown as an error and code is rejected
     */

    /* FIXME: auto when using reference
     * we have noticed that auto can give correct type of pointer, but inorder to get an reference
     * we must write auto& , for consistency we can write auto* incase we are expecting an pointer
     */
}
