#include <iostream>
#include <memory>

// abstract base
class Sensor {
public:
    virtual void read() = 0;
    virtual ~Sensor() = default;
};

// concrete types
class TemperatureSensor : public Sensor {
public:
    void read() override { std::cout << "reading temperature\n"; }
};

class PressureSensor : public Sensor {
public:
    void read() override { std::cout << "reading pressure\n"; }
};

// factory — caller only deals with base class pointer
class SensorFactory {
public:
    static std::unique_ptr<Sensor> create(const std::string& type) {
        if (type == "temperature") return std::make_unique<TemperatureSensor>();
        if (type == "pressure")    return std::make_unique<PressureSensor>();
        throw std::invalid_argument("unknown sensor: " + type);
    }
};

int main() {
    auto s1 = SensorFactory::create("temperature");
    auto s2 = SensorFactory::create("pressure");

    s1->read();
    s2->read();
}
