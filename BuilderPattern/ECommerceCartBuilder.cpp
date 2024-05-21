#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Product class
class Product {
public:
    std::string name;
    double price;

    Product(const std::string& name, double price) : name(name), price(price) {}
};

// ShoppingCart class
class ShoppingCart {
private:
    struct CartItem {
        Product product;
        int quantity;

        CartItem(const Product& product, int quantity)
            : product(product), quantity(quantity) {}
    };

    std::vector<CartItem> items;
    double discountPercent;
    std::string deliveryPreference;

public:
    ShoppingCart() : discountPercent(0.0), deliveryPreference("Standard") {}

    void addProduct(const Product& product, int quantity) {
        items.push_back(CartItem(product, quantity));
    }

    void applyDiscount(double discount) {
        discountPercent = discount;
    }

    void setDeliveryPreference(const std::string& preference) {
        deliveryPreference = preference;
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& item : items) {
            total += item.product.price * item.quantity;
        }
        double discountAmount = total * (discountPercent / 100);
        return total - discountAmount;
    }

    void checkout() const {
        std::cout << "Finalizing order with the following items:" << std::endl;
        for (const auto& item : items) {
            std::cout << "Product: " << item.product.name
                      << ", Price: $" << item.product.price
                      << ", Quantity: " << item.quantity << std::endl;
        }
        std::cout << "Total after discount: $" << calculateTotal() << std::endl;
        std::cout << "Discount: " << discountPercent << "%" << std::endl;
        std::cout << "Delivery: " << deliveryPreference << std::endl;
        std::cout << "Thank you for your order!" << std::endl;
    }
};

// CartBuilder interface
class CartBuilder {
public:
    virtual ~CartBuilder() {}
    virtual CartBuilder& addProduct(const Product& product, int quantity) = 0;
    virtual CartBuilder& applyDiscount(double discount) = 0;
    virtual CartBuilder& setDeliveryPreference(const std::string& preference) = 0;
    virtual std::unique_ptr<ShoppingCart> getCart() = 0;
};

// ConcreteCartBuilder implementation
class ConcreteCartBuilder : public CartBuilder {
private:
    std::unique_ptr<ShoppingCart> cart;

public:
    ConcreteCartBuilder() { cart = std::make_unique<ShoppingCart>(); }
    
    CartBuilder& addProduct(const Product& product, int quantity) override {
        cart->addProduct(product, quantity);
        return *this;
    }

    CartBuilder& applyDiscount(double discount) override {
        cart->applyDiscount(discount);
        return *this;
    }

    CartBuilder& setDeliveryPreference(const std::string& preference) override {
        cart->setDeliveryPreference(preference);
        return *this;
    }

    std::unique_ptr<ShoppingCart> getCart() override {
        return std::move(cart);
    }
};

// Main function demonstrating usage of the builder
int main() {
    ConcreteCartBuilder builder;
    builder.addProduct(Product("Laptop", 999.99), 1)
           .addProduct(Product("USB Cable", 19.99), 2)
           .applyDiscount(10)
           .setDeliveryPreference("Express");

    auto cart = builder.getCart();
    cart->checkout();

    return 0;
}
