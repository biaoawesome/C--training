#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

// Maximum length for name strings
const int MAX_NAME_LEN = 64;

// Function pointer types to simulate polymorphism
typedef const char* (*GetNameFunc)(void*);
typedef double (*GetPriceFunc)(void*);
typedef double (*CalculatePriceFunc)(void*);

// Base-like structure for financial instruments
struct Instrument {
    GetNameFunc getName;
    GetPriceFunc getPrice;
    CalculatePriceFunc calculatePrice;
    char name[MAX_NAME_LEN]; // Name stored as static array
};

// Stock data
typedef struct {
    Instrument base;
    double price;
} Stock;

// Option data
typedef struct {
    Instrument base;
    double strikePrice;
    double spotPrice;
    double timeToMaturity;
    double volatility;
    double riskFreeRate;
} Option;

// Standard normal cumulative distribution function (CDF)
double normalCDF(double x) {
    return 0.5 * erfc(-x / sqrt(2.0));
}

// === Stock methods ===

const char* stockGetName(void* obj) {
    return "Stock";
}

double stockGetPrice(void* obj) {
    Stock* stock = (Stock*)obj;
    return stock->price;
}

double stockCalculatePrice(void* obj) {
    Stock* stock = (Stock*)obj;
    return stock->price;
}

void initStock(Stock* stock, const char* name, double price) {
    strncpy(stock->base.name, name, MAX_NAME_LEN - 1);
    stock->base.name[MAX_NAME_LEN - 1] = '\0';
    stock->base.getName = stockGetName;
    stock->base.getPrice = stockGetPrice;
    stock->base.calculatePrice = stockCalculatePrice;
    stock->price = price;
}

// === Option methods ===

const char* optionGetName(void* obj) {
    Option* option = (Option*)obj;
    return option->base.name;
}

double optionGetPrice(void* obj) {
    Option* option = (Option*)obj;
    return option->base.calculatePrice(obj);  // Use the virtual method
}

double optionCalculatePrice(void* obj) {
    Option* opt = (Option*)obj;
    double d1 = (log(opt->spotPrice / opt->strikePrice) +
                 (opt->riskFreeRate + 0.5 * pow(opt->volatility, 2)) *
                     opt->timeToMaturity) /
                (opt->volatility * sqrt(opt->timeToMaturity));
    double d2 = d1 - opt->volatility * sqrt(opt->timeToMaturity);

    double callPrice = opt->spotPrice * normalCDF(d1) -
                       opt->strikePrice * exp(-opt->riskFreeRate * opt->timeToMaturity) *
                           normalCDF(d2);
    return callPrice;
}

void initOption(Option* option, const char* name,
                double strikePrice, double spotPrice,
                double timeToMaturity, double volatility,
                double riskFreeRate) {
    strncpy(option->base.name, name, MAX_NAME_LEN - 1);
    option->base.name[MAX_NAME_LEN - 1] = '\0';
    option->base.getName = optionGetName;
    option->base.getPrice = optionGetPrice;
    option->base.calculatePrice = optionCalculatePrice;
    option->strikePrice = strikePrice;
    option->spotPrice = spotPrice;
    option->timeToMaturity = timeToMaturity;
    option->volatility = volatility;
    option->riskFreeRate = riskFreeRate;
}

// === Main program ===

int main() {
    // Create and test a stock
    Stock stock;
    initStock(&stock, "AAPL", 150.0);

    cout << "Instrument: " << stock.base.getName(&stock) << endl;
    cout << "Price: " << stock.base.getPrice(&stock) << endl;
    cout << "Calculated Price: " << stock.base.calculatePrice(&stock) << endl;
    cout << endl;

    // Create and test an option
    Option option;
    initOption(&option, "AAPL Call Option", 145.0, 150.0, 1.0, 0.2, 0.05);

    cout << "Instrument: " << option.base.getName(&option) << endl;
    cout << "Price: " << option.base.getPrice(&option) << endl;
    cout << "Calculated Price (Black-Scholes): " << option.base.calculatePrice(&option) << endl;

    return 0;
}
