#include <iostream>
#include <memory.h>
#include <memory>

class resource {
    private:
        int id;

    public:
        resource(int val);
        ~resource();
        void use();
};

resource::resource(int val) : id(val) { 
    std::cout<< "Resouce " << id << " Created. " << std::endl;
};

resource::~resource() {
    std::cout<< "Resouce " << id << " Destroyed. " << std::endl;
}

void resource::use() {
    std::cout << "Use Called" << std::endl;
}

void processResource(std::unique_ptr<resource> ptr ){
    ptr->use();
}

void processResource(std::shared_ptr<resource> ptr ){
    ptr->use();
}

int main() {
    
    // std::unique_ptr<resource> ptr = std::make_unique<resource>(1);

    std::shared_ptr<resource> ptr = std::make_shared<resource>(1);

    processResource(ptr);

}
