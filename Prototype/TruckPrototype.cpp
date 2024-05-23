#include <iostream>
#include <memory>
#include <string>

// Prototype base class
class VehiclePrototype {
public:
    virtual void display() const = 0;
    virtual std::unique_ptr<VehiclePrototype> clone() const = 0;
    virtual ~VehiclePrototype() {}
};

// Concrete class implementing Prototype
class Truck : public VehiclePrototype {
public:
    std::string model;
    std::string color;
    int horsepower;
    double capacity;

    Truck(const std::string& model, const std::string& color, int horsepower, double capacity)
        : model(model), color(color), horsepower(horsepower), capacity(capacity) {}

    void display() const override {
        std::cout << "Truck Model: " << model 
                  << ", Color: " << color 
                  << ", Horsepower: " << horsepower 
                  << ", Capacity: " << capacity << " tons" << std::endl;
    }

    std::unique_ptr<VehiclePrototype> clone() const override {
        return std::make_unique<Truck>(*this);
    }
};

int main() {
    std::unique_ptr<VehiclePrototype> truckPrototype = std::make_unique<Truck>("Ford Truck", "White", 350, 2.5);
    truckPrototype->display();

    // Clone the truck, no need to reinitialize properties
    auto clonedTruck = truckPrototype->clone();
    clonedTruck->display();

    return 0;
}
