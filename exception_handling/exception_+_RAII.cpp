#include <filesystem>
#include <iostream>
class FileHandle {
    FILE* f;
public:
    FileHandle(const char* name) {
        f = fopen(name, "r");
        if (!f) throw std::runtime_error("cannot open file");
        std::cout << "file opened\n";
    }
    ~FileHandle() {
        if (f) { fclose(f); std::cout << "file closed\n"; }
    }
};

void process() {
    FileHandle fh("test.txt");  // opens file
    throw std::runtime_error("something went wrong");
    // even though we throw, ~FileHandle() runs — file is closed
}

int main() {
    try {
        process();
    }
    catch (const std::exception& e) {
        std::cout << "caught: " << e.what() << "\n";
    }
}
