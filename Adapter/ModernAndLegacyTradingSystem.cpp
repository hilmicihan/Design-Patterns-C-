/*
Scenario: Combining Legacy and Modern Trading Systems in Binance
Situation:
The company has a legacy trading system with some functions that are still useful and reliable.
The company wants to integrate a new, advanced Binance API for   features and more robust trading capabilities.
The goal is to use the Adapter Design Pattern to allow the integration of the new system while still utilizing the useful functions from the legacy system.

*/
#include <iostream>
#include <string>
#include <memory>
using namespace std; 
class LegacyTradingSystem {
public:
    virtual void placeOrder(const string& symbol, double quantity, double price) {
        cout << "Legacy system: Placing order for " << quantity << " of " << symbol << " at $" << price << endl;
    }

    virtual void cancelOrder(const string& orderId) {
        cout << "Legacy system: Cancelling order with ID " << orderId << endl;
    }

    virtual double getBalance(const string& currency) {
        cout << "Legacy system: Getting balance for " << currency << endl;
        return 1000.0;  // Placeholder balance
    }

    virtual void generateReport(const string& symbol) {
        cout << "Legacy system: Generating report for " << symbol << endl;
    }
};

class BinanceAPI {
public:
    void createOrder(const string& symbol, double quantity, double price, const string& type) {
        cout << "Binance API: Creating " << type << " order for " << quantity << " of " << symbol << " at $" << price << endl;
    }

    void removeOrder(const string& orderId) {
        cout << "Binance API: Removing order with ID " << orderId << endl;
    }

    double fetchBalance(const string& currency) {
        cout << "Binance API: Fetching balance for " << currency << endl;
        return 5000.0;  // Placeholder balance
    }

    void advancedTradeAnalytics(const string& symbol) {
        cout << "Binance API: Performing advanced trade analytics for " << symbol << endl;
    }
};


class TradingAdapter : public LegacyTradingSystem {
    shared_ptr<BinanceAPI> binanceApi;
    shared_ptr<LegacyTradingSystem> legacySystem;
    string currency;
public:
    TradingAdapter(shared_ptr<BinanceAPI> api, shared_ptr<LegacyTradingSystem> legacy, const string& cur)
        : binanceApi(api), legacySystem(legacy), currency(cur) {}

    void placeOrder(const string& symbol, double quantity, double price) override {
        binanceApi->createOrder(symbol, quantity, price, "LIMIT");
    }

    void cancelOrder(const string& orderId) override {
        binanceApi->removeOrder(orderId);
    }

    double getBalance(const string& currency) override {
        return legacySystem->getBalance(currency);
    }

    void generateReport(const string& symbol) override {
        legacySystem->generateReport(symbol);
    }

    void performAdvancedAnalytics(const string& symbol) {
        binanceApi->advancedTradeAnalytics(symbol);
    }
};
/*

int main() {
    shared_ptr<LegacyTradingSystem> legacySystem = make_shared<LegacyTradingSystem>();
    legacySystem->placeOrder("BTCUSD", 1.0, 50000.0);
    legacySystem->cancelOrder("12345");
    cout << "Legacy balance: " << legacySystem->getBalance("USD") << endl;
    legacySystem->generateReport("BTCUSD");

    shared_ptr<BinanceAPI> binanceApi = make_shared<BinanceAPI>();
    TradingAdapter adapter(binanceApi, legacySystem, "USD");

    // Using the adapter to interact with the new Binance API via the legacy interface
    adapter.placeOrder("ETHUSD", 2.0, 3000.0);
    adapter.cancelOrder("67890");
    cout << "New system balance: " << adapter.getBalance("USD") << endl;

    // Using the adapter to perform advanced analytics using the new Binance API
    adapter.performAdvancedAnalytics("BTCUSD");

    // Still using legacy system's report generation
    adapter.generateReport("ETHUSD");

    return 0;
}
*/


/*

Benefits:
Backward Compatibility: Existing functionality from the legacy system that is still useful is retained and used.
Enhanced Functionality: The adapter allows the new system's advanced features to be used, providing additional benefits while maintaining compatibility with the old system.
Incremental Transition: The system can gradually transition from the legacy trading system to the new Binance API, minimizing risks and disruptions.
Maintainability: The adapter encapsulates the logic for choosing between the legacy and new systems, making the codebase cleaner and easier to maintain.
Flexibility: The system can be easily extended to handle additional conditions or new features without significant changes to the existing code.
*/