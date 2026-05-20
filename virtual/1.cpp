#include <iostream>
#include <string>

class Entity {
    public:
        virtual std::string GetName() {
            return "Entity";
        }
};

class Player: public Entity {

    private:
        std::string m_name;
    public:

        Player(const std::string& name): m_name(name){}

        std::string GetName() override { // override is not mandatory actually
            return m_name;
        }
};

int main() {

    Entity* e = new Entity();
    std::cout << e->GetName() << std::endl;
    Player* p = new Player("Arjun");
    std::cout << p->GetName() << std::endl;

    Entity* v = new Player("abhimanyu");
    std::cout << v->GetName() << std::endl;
    
}
