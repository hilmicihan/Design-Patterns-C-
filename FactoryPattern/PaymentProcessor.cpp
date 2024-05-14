#include <iostream>
#include <string>
#include <stdexcept>

class PaymentProcessor {
public:
    virtual ~PaymentProcessor() {}
    virtual void processPayment(double amount) const = 0;
};
class CreditCardProcessor : public PaymentProcessor {
public:
    void processPayment(double amount) const override {
        std::cout << "Processing credit card payment for $" << amount << std::endl;
    }
};

class PayPalProcessor : public PaymentProcessor {
public:
    void processPayment(double amount) const override {
        std::cout << "Processing PayPal payment for $" << amount << std::endl;
    }
};

class CryptoCurrencyProcessor : public PaymentProcessor {
public:
    void processPayment(double amount) const override {
        std::cout << "Processing cryptocurrency payment for $" << amount << std::endl;
    }
};
class PaymentProcessorFactory {
public:
    PaymentProcessor* getProcessor(const std::string& paymentType) {
        if (paymentType == "CreditCard") {
            return new CreditCardProcessor();
        } else if (paymentType == "PayPal") {
            return new PayPalProcessor();
        } else if (paymentType == "Crypto") {
            return new CryptoCurrencyProcessor();
        } else {
            throw std::invalid_argument("Unsupported payment type: " + paymentType);
        }
    }
};
int main() {
    PaymentProcessorFactory factory;
    PaymentProcessor* processor = nullptr;

    try {
        processor = factory.getProcessor("PayPal");
        processor->processPayment(99.99);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Clean up the allocated processor
    delete processor;
    return 0;
}
