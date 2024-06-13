#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;
/*
Composite Design Pattern 🌳

The Composite Design Pattern allows you to compose objects into tree structures to represent part-whole hierarchies. 
🌲 It lets clients treat individual objects and compositions of objects uniformly,
 making it perfect for building complex structures like organizational charts, file systems, or UI components. 🎨

Benefits:

Uniformity: Treat individual and composite objects the same way. 🔄
Flexibility: Easily extend your system with new components. ➕
Simplicity: Simplifies client code by providing a consistent interface. 💡
Example: Imagine building a computer system where both simple components (like CPU and RAM) and 
complex components (like a motherboard containing multiple parts) can be managed and priced uniformly. 🖥️💻
            Computer
            /    \
    Motherboard   Mouse
    /     \    \
Ram        CPU  GPU

*/
// Abstract base class representing a computer component
class ComputerComponent {
public:
    virtual double getPrice() const = 0;  // Pure virtual method to get the price of the component
    virtual void add(shared_ptr<ComputerComponent> component) {
        throw runtime_error("Cannot add to a leaf component");
    }
    virtual void display(const string& indent = "") const = 0;  // Pure virtual method to display the component details
    virtual ~ComputerComponent() = default;  // Virtual destructor for proper cleanup
};

// Leaf component: Mouse
class Mouse : public ComputerComponent {
private:
    double price;
public:
    Mouse(double price) : price(price) {}

    double getPrice() const override {
        return price;
    }

    void display(const string& indent = "") const override {
        cout << indent << "Mouse: $" << price << endl;
    }
};

// Leaf component: HD (Hard Drive)
class HD : public ComputerComponent {
private:
    double price;
public:
    HD(double price) : price(price) {}

    double getPrice() const override {
        return price;
    }

    void display(const string& indent = "") const override {
        cout << indent << "HD: $" << price << endl;
    }
};

// Leaf component: RAM
class RAM : public ComputerComponent {
private:
    double price;
public:
    RAM(double price) : price(price) {}

    double getPrice() const override {
        return price;
    }

    void display(const string& indent = "") const override {
        cout << indent << "RAM: $" << price << endl;
    }
};

// Leaf component: SSD (Solid State Drive)
class SSD : public ComputerComponent {
private:
    double price;
public:
    SSD(double price) : price(price) {}

    double getPrice() const override {
        return price;
    }

    void display(const string& indent = "") const override {
        cout << indent << "SSD: $" << price << endl;
    }
};

// Leaf component: CPU (Central Processing Unit)
class CPU : public ComputerComponent {
private:
    double price;
public:
    CPU(double price) : price(price) {}

    double getPrice() const override {
        return price;
    }

    void display(const string& indent = "") const override {
        cout << indent << "CPU: $" << price << endl;
    }
};

// Leaf component: GPU (Graphics Processing Unit)
class GPU : public ComputerComponent {
private:
    double price;
public:
    GPU(double price) : price(price) {}

    double getPrice() const override {
        return price;
    }

    void display(const string& indent = "") const override {
        cout << indent << "GPU: $" << price << endl;
    }
};

// Composite component: Motherboard
class Motherboard : public ComputerComponent {
private:
    vector<shared_ptr<ComputerComponent>> components;
    double price;
public:
    Motherboard(double price) : price(price) {}

    void add(shared_ptr<ComputerComponent> component) override {
        components.push_back(component);
    }

    double getPrice() const override {
        double total = price;
        for (const auto& component : components) {
            total += component->getPrice();
        }
        return total;
    }

    void display(const string& indent = "") const override {
        cout << indent << "Motherboard: $" << price << endl;
        for (const auto& component : components) {
            component->display(indent + "  ");
        }
    }
};

// Composite component: Computer
class CompositeComputerComponent : public ComputerComponent {
private:
    string name;
    vector<shared_ptr<ComputerComponent>> components;
public:
    CompositeComputerComponent(const string& name) : name(name) {}

    void add(shared_ptr<ComputerComponent> component) override {
        components.push_back(component);
    }

    double getPrice() const override {
        double total = 0;
        for (const auto& component : components) {
            total += component->getPrice();
        }
        return total;
    }

    void display(const string& indent = "") const override {
        cout << indent << name << ":" << endl;
        for (const auto& component : components) {
            component->display(indent + "  ");
        }
        cout << indent << "Total Price: $" << getPrice() << endl;
    }
};

// Main function to demonstrate the Composite Pattern
int main() {
    // Creating leaf components
    shared_ptr<ComputerComponent> mouse = make_shared<Mouse>(25.0);
    shared_ptr<ComputerComponent> hd = make_shared<HD>(75.0);
    shared_ptr<ComputerComponent> ram1 = make_shared<RAM>(50.0);
    shared_ptr<ComputerComponent> ram2 = make_shared<RAM>(50.0);
    shared_ptr<ComputerComponent> ssd = make_shared<SSD>(100.0);
    shared_ptr<ComputerComponent> cpu = make_shared<CPU>(200.0);
    shared_ptr<ComputerComponent> gpu = make_shared<GPU>(300.0);
    
    // Creating composite component: Motherboard
    shared_ptr<Motherboard> motherboard = make_shared<Motherboard>(150.0);
    motherboard->add(ram1);
    motherboard->add(ram2);
    motherboard->add(cpu);
    motherboard->add(gpu);

    // Creating composite component: Computer
    shared_ptr<CompositeComputerComponent> computer = make_shared<CompositeComputerComponent>("Computer");
    computer->add(mouse);
    computer->add(hd);
    computer->add(ssd);
    computer->add(motherboard);

    // Displaying the structure and total price of the computer
    computer->display();

    return 0;
}
