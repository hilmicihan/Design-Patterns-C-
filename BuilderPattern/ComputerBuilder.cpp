#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;
class Computer {
    public:
    string cpu;
    string ram;
    string storage;
    void specifications() const {
        cout<<"Computer Specifications: "<<endl;
        cout<<"CPU: "<<cpu<<endl;
        cout<<"RAM: "<<ram<<endl;
        cout<<"Storage: "<<storage<<endl;

    }
};
class ComputerBuilder {
    public:
    virtual ~ComputerBuilder() = default;
    virtual ComputerBuilder& setCPU(const string& cpuType) =0;
    virtual ComputerBuilder& setRAM(const string& ramType) =0;
    virtual ComputerBuilder& setStorage(const string& storageType) =0;
    virtual Computer* getComputer() =0;
};
class CustomComputerBuilder : public ComputerBuilder {
    private:
    Computer* computer;
    public:
    CustomComputerBuilder() {
        computer = new Computer();
        }
    ComputerBuilder& setCPU(const string& cpuType) override {
        computer->cpu = cpuType;
        return *this;

    }
    ComputerBuilder& setRAM(const string& ramType) override {
        computer->ram = ramType;
        return *this;
        
    }
    ComputerBuilder& setStorage(const string& storageType) override {
        computer->storage = storageType;
        return *this;
        
    }
    Computer* getComputer() override {
        return computer;
    }
};
int main() {
    CustomComputerBuilder builder;
    builder.setCPU("AMD Ryzen 9").setRAM("64gb DDR4").setStorage("2TB NVMe SSD");
    Computer* customComputer = builder.getComputer();
    customComputer->specifications();
}