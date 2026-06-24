#include <iostream>
#include <vector>

 /* this decltype(auto) was introduced in c++ 14  */
/* PART 1: The basic difference */

int globalValue = 100;

int& getRef() {
    return globalValue; /* returns a REFERENCE (an alias, not a copy) */
}

void part1_basic_difference() {
    /* auto strips the reference — you get a plain copy */
    auto a = getRef();        /* type of a → int (copy) */
    a = 999;
    std::cout << globalValue; /* still 100 — we only changed the copy */

    /* auto& you explicitly ask for a reference */
    auto& b = getRef();       /* type of b → int& (reference) */
    b = 999;
    std::cout << globalValue; /* now 999 — we modified the original */

    globalValue = 100;        /* Reset */

    /* decltype(auto) automatically deduces the reference from the expression */
    decltype(auto) c = getRef(); /* type of c → int& (reference, deduced automatically) */
    c = 999;
    std::cout << globalValue;    /* now 999 — same as auto&, but deduced for us */
    globalValue = 100;
}


/* PART 2: Wrapper function — the main use case */

/* BAD wrapper — auto strips the reference
   Callers get a copy and can't modify the original */
auto bad_wrapper() {
    return getRef(); /* getRef() returns int&
                        but auto makes the return type int (copy)
                        the reference is lost! */
}

/* GOOD wrapper — decltype(auto) preserves whatever getRef() actually returns */
decltype(auto) good_wrapper() {
    return getRef(); /* getRef() returns int&
                        decltype(auto) sees that and keeps it int& */
}

void part2_wrapper() {
    /* bad_wrapper() = 42;  COMPILE ERROR — bad_wrapper() returns a temporary int
                             you can't assign to a temporary */

    good_wrapper() = 42;      /* Works fine! good_wrapper() returns int&
                                  so we can assign through it */
    std::cout << globalValue; /* 42 */
    globalValue = 100;
}


/* PART 3: Generic wrapper (the real-world pattern)
   We don't know what someFunction returns — value? reference? const?
   decltype(auto) figures it out automatically. */

template <typename Func, typename... Args>
decltype(auto) call(Func&& f, Args&&... args) {
    /* std::forward preserves whether args are lvalues or rvalues
       decltype(auto) preserves whatever f returns */
    return f(std::forward<Args>(args)...);
}

int& getElement(std::vector<int>& v, int i) {
    return v[i]; /* returns a reference into the vector */
}

void part3_generic_wrapper() {
    std::vector<int> v = {10, 20, 30};

    /* call() wraps getElement() perfectly
       because decltype(auto) preserves the int& return type */
    decltype(auto) elem = call(getElement, v, 1); /* elem is int& */
    elem = 99;

    std::cout << v[1]; /* 99 — we modified the vector through the reference */
}


/* PART 4: The gotcha — (x) vs x
   This is the one tricky rule to remember with decltype(auto) */

decltype(auto) safe_return() {
    int x = 42;
    return x; /* decltype(x) → int (safe copy, x is just a name) */
}

/* DON'T DO THIS — dangling reference
   decltype(auto) dangerous_return() {
       int x = 42;
       return (x);  decltype((x)) → int& (reference to a local!)
                    x is destroyed when function returns → crash
   }

   Rule: bare name   →  gives the declared type (int)
         (parentheses) →  gives a reference type (int&)
   With decltype(auto), this distinction matters! */

void part4_gotcha() {
    auto val = safe_return(); /* val is int, value is 42 */
    std::cout << val;         /* 42, safe */
}


/* PART 5: Quick cheat sheet in code form */

void part5_cheat_sheet() {
    int x = 10;
    int& ref = x;

    auto           a = ref; /* int  — always copies, safe default */
    auto&          b = ref; /* int& — you explicitly want a reference */
    decltype(auto) c = ref; /* int& — deduced from expression, same as auto& here */

    /* When does decltype(auto) shine over auto& ?
       When you don't KNOW if the thing returns a ref or a value
       (e.g. inside a template wrapping an unknown function)
       auto& would FORCE a reference even if the function returns a value → compile error
       decltype(auto) handles both cases correctly */

    (void)a; (void)b; (void)c; /* suppress unused warnings */
}


int main() {
    part1_basic_difference();
    part2_wrapper();
    part3_generic_wrapper();
    part4_gotcha();
    part5_cheat_sheet();
    return 0;
}
