#include <iostream>
#include <stdexcept>
#include <cassert>

// Define the WeatherService interface
class WeatherService {
public:
    virtual ~WeatherService() {}
    virtual double getTemperature() const = 0;
};

// Real service implementation that might interact with an actual weather API
class RealWeatherService : public WeatherService {
public:
    double getTemperature() const override {
        return 23.5;  // Simulating a real response.
    }
};

// Mock service for use in unit tests
class MockWeatherService : public WeatherService {
public:
    double getTemperature() const override {
        return 20.0;  // Simulated temperature for testing purposes.
    }
};

// Factory for creating instances of WeatherService
class WeatherServiceFactory {
public:
    enum ServiceType {
        Real,
        Mock
    };

    static WeatherService* createWeatherService(ServiceType type) {
        switch (type) {
            case Real:
                return new RealWeatherService();
            case Mock:
                return new MockWeatherService();
            default:
                throw std::invalid_argument("Invalid service type");
        }
    }
};

// A simple component that uses WeatherService
class WeatherComponent {
public:
    WeatherComponent(WeatherService* service) : service(service) {}

    std::string performOperation() const {
        double temp = service->getTemperature();
        if (temp > 21.0) {
            return "Warm";
        } else {
            return "Cold";
        }
    }

private:
    WeatherService* service;
};

// Main function to run the test
int main() {
    try {
        // Using the factory to create a mock weather service for testing
        WeatherService* mockService = WeatherServiceFactory::createWeatherService(WeatherServiceFactory::Mock);
        WeatherComponent component(mockService);

        // Perform the test
        std::string result = component.performOperation();
        assert(result == "Cold" && "Test failed: Expected Cold");

        std::cout << "Test passed: " << result << std::endl;

        // Clean up
        delete mockService;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
