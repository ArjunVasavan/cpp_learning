#include <iostream>

class Logger {
    // private constructor — nobody can call Logger()
    Logger() { std::cout << "Logger created\n"; }

    // delete copy and move — prevent duplication
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger& getInstance() {
        static Logger instance;  // created once, on first call
        return instance;
    }

    void log(const std::string& msg) {
        std::cout << "[LOG]: " << msg << "\n";
    }
};

int main() {
    Logger::getInstance().log("system started");
    Logger::getInstance().log("sensor initialized");
    // both calls use the exact same object
}
