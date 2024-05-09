#include <iostream>
#include <string>
#include <mutex>

class DatabaseConfig {
private:
    // Private static instance
    static DatabaseConfig* instance;
    static std::mutex mutex;

    // Configuration details
    std::string dbHost;
    int dbPort;
    std::string dbName;
    std::string dbUser;
    std::string dbPassword;

    // Private constructor
    DatabaseConfig() : dbHost("localhost"), dbPort(3306), dbName("default"), dbUser("root"), dbPassword("password") {}

    // Deleted copy constructor and assignment operator
    DatabaseConfig(const DatabaseConfig&) = delete;
    DatabaseConfig& operator=(const DatabaseConfig&) = delete;

public:
    // Static method to get the instance
    static DatabaseConfig* getInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (instance == nullptr) {
            instance = new DatabaseConfig();
        }
        return instance;
    }

    // Methods to set database configuration
    void setConfiguration(const std::string& host, int port, const std::string& name, const std::string& user, const std::string& password) {
        dbHost = host;
        dbPort = port;
        dbName = name;
        dbUser = user;
        dbPassword = password;
    }

    // Methods to get database configuration
    void printConfiguration() const {
        std::cout << "DB Host: " << dbHost
                  << "\nDB Port: " << dbPort
                  << "\nDB Name: " << dbName
                  << "\nDB User: " << dbUser
                  << "\nDB Password: " << dbPassword << std::endl;
    }
};

// Initialize the static member
DatabaseConfig* DatabaseConfig::instance = nullptr;
std::mutex DatabaseConfig::mutex;

// Main function to demonstrate Singleton usage
int main() {
    // Get the Singleton instance and configure database
    DatabaseConfig* config = DatabaseConfig::getInstance();
    config->setConfiguration("192.168.1.100", 5432, "myDatabase", "admin", "admin123");
    config->printConfiguration();

    // Get another instance and print to show same configuration
    DatabaseConfig* config2 = DatabaseConfig::getInstance();
    config2->printConfiguration();

    return 0;
}
