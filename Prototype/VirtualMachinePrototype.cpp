#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Represents a virtual machine with configurable software and system settings
class VirtualMachine {
public:
    string OS;
    int CPU_cores;
    int RAM;
    vector<string> installedSoftware;

    // Constructor to initialize a VM with OS, CPU, and RAM
    VirtualMachine(const string& OS, int CPU_cores, int RAM) 
        : OS(OS), CPU_cores(CPU_cores), RAM(RAM) {}

    // Copy constructor for cloning
    VirtualMachine(const VirtualMachine& other) 
        : OS(other.OS), CPU_cores(other.CPU_cores), RAM(other.RAM), installedSoftware(other.installedSoftware) {}

    // Method to install software on the VM
    void installSoftware(const string& software) {
        installedSoftware.push_back(software);
        cout << software << " installed on " << OS << " VM." << endl;
    }

    // Display the configuration of the VM
    void displayConfiguration() const {
        cout << "VM Configuration: " << OS << " with " 
             << CPU_cores << " CPU cores and " << RAM << "GB RAM." << endl;
        cout << "Installed Software: ";
        for (const auto& software : installedSoftware) {
            cout << software << " ";
        }
        cout << endl;
    }

    // Method to clone the VM
    unique_ptr<VirtualMachine> clone() const {
        return make_unique<VirtualMachine>(*this);
    }
};

int main() {
    // Creating and configuring the original VM
    VirtualMachine vm("Ubuntu 20.04", 4, 8);
    vm.installSoftware("Docker");
    vm.installSoftware("Node.js");
    vm.displayConfiguration();

    // Cloning the original VM
    auto clonedVM = vm.clone();
    // Updating the cloned VM with additional software
    clonedVM->installSoftware("PostgreSQL");
    clonedVM->displayConfiguration();

    return 0;
}
