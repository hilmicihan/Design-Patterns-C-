#include <iostream>
#include <stdexcept>
#include <string>
class Computer {
public:
    std::string cpu;
    std::string ram;
    std::string storage;

    void specifications() const {
        std::cout << "Computer Specifications:" << std::endl;
        std::cout << "CPU: " << cpu << std::endl;
        std::cout << "RAM: " << ram << std::endl;
        std::cout << "Storage: " << storage << std::endl;
    }
};
class ComputerBuilder {
public:
    virtual ~ComputerBuilder() = default;
    virtual ComputerBuilder& setCPU(const std::string& cpuType) = 0;
    virtual ComputerBuilder& setRAM(const std::string& ramType) = 0;
    virtual ComputerBuilder& setStorage(const std::string& storageType) = 0;
    virtual Computer* getComputer() = 0;
};

class CustomComputerBuilder : public ComputerBuilder {
private:
    Computer* computer;

public:
    CustomComputerBuilder() { computer = new Computer(); }

    ComputerBuilder& setCPU(const std::string& cpuType) override {
        computer->cpu = cpuType;
        return *this;
    }

    ComputerBuilder& setRAM(const std::string& ramType) override {
        computer->ram = ramType;
        return *this;
    }

    ComputerBuilder& setStorage(const std::string& storageType) override {
        computer->storage = storageType;
        return *this;
    }

    Computer* getComputer() override {
        return computer;
    }
};
int main() {
    CustomComputerBuilder builder;

    // Simulating dynamic configuration
    builder.setCPU("AMD Ryzen 9").setRAM("64GB DDR4").setStorage("2TB NVMe SSD");
    Computer* customComputer = builder.getComputer();
      builder.setCPU("AMD Ryzen 3").setRAM("64GB DDR4").setStorage("2TB NVMe SSD");
      Computer* customComputer2 = builder.getComputer();
    customComputer->specifications();
     customComputer2->specifications();
    return 0;
}
