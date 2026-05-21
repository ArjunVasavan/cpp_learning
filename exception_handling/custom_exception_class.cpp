#include <stdexcept>
#include <iostream>
#include <string>

class NetworkError : public std::runtime_error {
    int error_code;
public:
    NetworkError(const std::string& msg, int code)
        : std::runtime_error(msg), error_code(code) {}

    int code() const { return error_code; }
};

int main() {
    try {
        throw NetworkError("connection refused", 503);
    }
    catch (const NetworkError& e) {
        std::cout << e.what() << " | code: " << e.code() << "\n";
    }
    catch (const std::runtime_error& e) {  // also catches it (base class)
        std::cout << "runtime error\n";
    }
}
