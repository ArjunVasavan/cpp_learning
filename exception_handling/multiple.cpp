#include<iostream>
void process(int x) {
    if (x < 0)  throw std::invalid_argument("negative number");
    if (x > 100) throw std::out_of_range("too large");
    if (x == 0)  throw std::runtime_error("zero not allowed");
}

int main() {
    try {
        process(-5);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "invalid: " << e.what() << "\n";
    }
    catch (const std::out_of_range& e) {
        std::cout << "range error: " << e.what() << "\n";
    }
    catch (const std::exception& e) {   // catches anything derived from std::exception
        std::cout << "some error: " << e.what() << "\n";
    }
    catch (...) {                        // catches literally everything
        std::cout << "unknown error\n";
    }
}
