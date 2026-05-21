#include <iostream>
#include <memory>

// strategy interface
class CompressionStrategy {
public:
    virtual void compress(const std::string& data) = 0;
    virtual ~CompressionStrategy() = default;
};

// concrete strategies
class RLECompression : public CompressionStrategy {
public:
    void compress(const std::string& data) override {
        std::cout << "RLE compressing: " << data << "\n";
    }
};

class HuffmanCompression : public CompressionStrategy {
public:
    void compress(const std::string& data) override {
        std::cout << "Huffman compressing: " << data << "\n";
    }
};

// context — uses whichever strategy is set
class DataTransmitter {
    std::unique_ptr<CompressionStrategy> strategy;

public:
    void setStrategy(std::unique_ptr<CompressionStrategy> s) {
        strategy = std::move(s);
    }

    void transmit(const std::string& data) {
        if (strategy) strategy->compress(data);
        std::cout << "transmitting...\n";
    }
};

int main() {
    DataTransmitter transmitter;

    transmitter.setStrategy(std::make_unique<RLECompression>());
    transmitter.transmit("sensor_data_001");

    transmitter.setStrategy(std::make_unique<HuffmanCompression>());
    transmitter.transmit("sensor_data_002");
}
