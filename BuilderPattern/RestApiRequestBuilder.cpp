#include <iostream>
#include <map>
#include <string>
#include <memory>

// Represents an HTTP request
class HttpRequest {
public:
    std::string method;
    std::string url;
    std::map<std::string, std::string> headers;
    std::string body;

    void send() const {
        std::cout << "Sending " << method << " request to " << url << std::endl;
        std::cout << "Headers: " << std::endl;
        for (const auto& header : headers) {
            std::cout << header.first << ": " << header.second << std::endl;
        }
        if (!body.empty()) {
            std::cout << "Body: " << body << std::endl;
        }
    }
};

// Builder interface for HttpRequest
class HttpRequestBuilder {
public:
    virtual HttpRequestBuilder& setMethod(const std::string& method) = 0;
    virtual HttpRequestBuilder& setUrl(const std::string& url) = 0;
    virtual HttpRequestBuilder& addHeader(const std::string& key, const std::string& value) = 0;
    virtual HttpRequestBuilder& setBody(const std::string& body) = 0;
    virtual std::unique_ptr<HttpRequest> build() = 0;
};

// Concrete builder implementation
class ConcreteHttpRequestBuilder : public HttpRequestBuilder {
private:
    std::unique_ptr<HttpRequest> httpRequest;

public:
    ConcreteHttpRequestBuilder() : httpRequest(new HttpRequest()) {}

    HttpRequestBuilder& setMethod(const std::string& method) override {
        httpRequest->method = method;
        return *this;
    }

    HttpRequestBuilder& setUrl(const std::string& url) override {
        httpRequest->url = url;
        return *this;
    }

    HttpRequestBuilder& addHeader(const std::string& key, const std::string& value) override {
        httpRequest->headers[key] = value;
        return *this;
    }

    HttpRequestBuilder& setBody(const std::string& body) override {
        httpRequest->body = body;
        return *this;
    }

    std::unique_ptr<HttpRequest> build() override {
        return std::move(httpRequest);
    }
};

// Example usage
int main() {
    ConcreteHttpRequestBuilder builder;
    auto request = builder.setMethod("POST")
                          .setUrl("http://example.com/api/data")
                          .addHeader("Content-Type", "application/json")
                          .setBody(R"({"key": "value"})")
                          .build();
    request->send();
    return 0;
}
