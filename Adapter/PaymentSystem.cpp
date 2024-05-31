/*
Scenario: Conditional Use of Legacy and New Payment Systems
Situation:
The company has both legacy and new users.
Legacy users should continue using the legacy payment system.
New users should benefit from the new payment gateway's advanced features.
The Adapter will determine which system to use based on the user type.
*/
#include <iostream>
#include <string>
#include <iostream>
#include <memory>

class LegacyPaymentSystem {
public:
    virtual void processPayment(double amount) {
        std::cout << "Legacy system: Processing payment of $" << amount << std::endl;
    }

    virtual void cancelPayment(double amount) {
        std::cout << "Legacy system: Cancelling payment of $" << amount << std::endl;
    }

    virtual ~LegacyPaymentSystem() = default; // Ensure a virtual destructor for proper cleanup
};
class NewPaymentGateway {
public:
    void initiatePayment(double amount, const std::string& currency) {
        std::cout << "New gateway: Initiating payment of " << amount << " " << currency << std::endl;
    }

    void reversePayment(double amount, const std::string& currency) {
        std::cout << "New gateway: Reversing payment of " << amount << " " << currency << std::endl;
    }

    void checkPaymentStatus(int transactionId) {
        std::cout << "New gateway: Checking status for transaction ID " << transactionId << std::endl;
    }
};


class PaymentAdapter : public LegacyPaymentSystem {
    std::shared_ptr<NewPaymentGateway> newGateway;
    std::shared_ptr<LegacyPaymentSystem> legacySystem;
    std::string currency;
    bool isLegacyUser;
public:
    PaymentAdapter(std::shared_ptr<NewPaymentGateway> newGateway, std::shared_ptr<LegacyPaymentSystem> legacySystem, const std::string& currency, bool isLegacyUser)
        : newGateway(newGateway), legacySystem(legacySystem), currency(currency), isLegacyUser(isLegacyUser) {}

    void processPayment(double amount) override {
        if (isLegacyUser) {
            legacySystem->processPayment(amount);
        } else {
            newGateway->initiatePayment(amount, currency);
        }
    }

    void cancelPayment(double amount) override {
        if (isLegacyUser) {
            legacySystem->cancelPayment(amount);
        } else {
            newGateway->reversePayment(amount, currency);
        }
    }

    void checkStatus(int transactionId) {
        if (!isLegacyUser) {
            newGateway->checkPaymentStatus(transactionId);
        } else {
            std::cout << "Legacy system: Status check not available." << std::endl;
        }
    }
};



int main() {
    std::shared_ptr<LegacyPaymentSystem> legacySystem = std::make_shared<LegacyPaymentSystem>();
    std::shared_ptr<NewPaymentGateway> newGateway = std::make_shared<NewPaymentGateway>();

    // Legacy user
    PaymentAdapter legacyUserAdapter(newGateway, legacySystem, "USD", true);
    legacyUserAdapter.processPayment(100.0);
    legacyUserAdapter.cancelPayment(50.0);
    legacyUserAdapter.checkStatus(12345);

    std::cout << std::endl;

    // New user
    PaymentAdapter newUserAdapter(newGateway, legacySystem, "USD", false);
    newUserAdapter.processPayment(200.0);
    newUserAdapter.cancelPayment(100.0);
    newUserAdapter.checkStatus(67890);

    return 0;
}