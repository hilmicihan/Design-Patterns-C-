#include <iostream>
#include <stdexcept>
#include <string>

// Base message class
class Message {
public:
    virtual ~Message() {}
};

// Email message subclass
class EmailMessage : public Message {
public:
    std::string recipientEmail;
    std::string subject;
    std::string body;

    EmailMessage(const std::string& recipientEmail, const std::string& subject, const std::string& body)
        : recipientEmail(recipientEmail), subject(subject), body(body) {}
};

// SMS message subclass
class SMSMessage : public Message {
public:
    std::string phoneNumber;
    std::string content;

    SMSMessage(const std::string& phoneNumber, const std::string& content)
        : phoneNumber(phoneNumber), content(content) {}
};

// Push notification message subclass
class PushNotificationMessage : public Message {
public:
    std::string deviceToken;
    std::string message;

    PushNotificationMessage(const std::string& deviceToken, const std::string& message)
        : deviceToken(deviceToken), message(message) {}
};

// Communication service interface
class CommunicationService {
public:
    virtual void sendMessage(const Message& message) = 0;
    virtual ~CommunicationService() {}
};

// Email service implementation
class EmailService : public CommunicationService {
public:
    void sendMessage(const Message& message) override {
        const EmailMessage& emailMessage = dynamic_cast<const EmailMessage&>(message);
        std::cout << "Emailing to " << emailMessage.recipientEmail
                  << " with subject '" << emailMessage.subject
                  << "': " << emailMessage.body << std::endl;
    }
};

// SMS service implementation
class SMSService : public CommunicationService {
public:
    void sendMessage(const Message& message) override {
        const SMSMessage& smsMessage = dynamic_cast<const SMSMessage&>(message);
        std::cout << "Sending SMS to " << smsMessage.phoneNumber
                  << ": " << smsMessage.content << std::endl;
    }
};

// Push notification service implementation
class PushNotificationService : public CommunicationService {
public:
    void sendMessage(const Message& message) override {
        const PushNotificationMessage& pushMessage = dynamic_cast<const PushNotificationMessage&>(message);
        std::cout << "Sending Push Notification to " << pushMessage.deviceToken
                  << ": " << pushMessage.message << std::endl;
    }
};

// Factory for creating communication services
class CommunicationFactory {
public:
    enum ServiceType {
        EMAIL,
        SMS,
        PUSH_NOTIFICATION
    };

    static CommunicationService* getCommunicationService(ServiceType type) {
        switch (type) {
            case EMAIL:
                return new EmailService();
            case SMS:
                return new SMSService();
            case PUSH_NOTIFICATION:
                return new PushNotificationService();
            default:
                throw std::invalid_argument("Unsupported service type");
        }
    }
};

// Main function demonstrating usage of the communication services
int main() {
    // Create messages
    EmailMessage email("user@example.com", "Welcome", "Hello, welcome to our service!");
    SMSMessage sms("1234567890", "Your code is 12345");
    PushNotificationMessage push("device_token_here", "You have a new notification");

    // Get services
    CommunicationService* emailService = CommunicationFactory::getCommunicationService(CommunicationFactory::EMAIL);
    CommunicationService* smsService = CommunicationFactory::getCommunicationService(CommunicationFactory::SMS);
    CommunicationService* pushService = CommunicationFactory::getCommunicationService(CommunicationFactory::PUSH_NOTIFICATION);

    // Send messages
    emailService->sendMessage(email);
    smsService->sendMessage(sms);
    pushService->sendMessage(push);

    // Clean up
    delete emailService;
    delete smsService;
    delete pushService;

    return 0;
}
