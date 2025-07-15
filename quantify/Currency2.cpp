#include <iostream>
#include <cmath>
#include <random>
#include <cstring>

using namespace std;

// Maximum length for currency type name
const int MAX_CURRENCY_LEN = 16;

// === Currency structure ===
typedef struct {
    double amount;
    char currencyType[MAX_CURRENCY_LEN];
} Currency;

// Initialize a currency
void initCurrency(Currency* c, double amount, const char* currencyType) {
    c->amount = amount;
    strncpy(c->currencyType, currencyType, MAX_CURRENCY_LEN - 1);
    c->currencyType[MAX_CURRENCY_LEN - 1] = '\0';
}

// Add two currencies (same type)
Currency addCurrency(const Currency* a, const Currency* b) {
    if (strcmp(a->currencyType, b->currencyType) != 0) {
        cerr << "Error: Cannot add different currencies" << endl;
        exit(1);
    }
    Currency result;
    initCurrency(&result, a->amount + b->amount, a->currencyType);
    return result;
}

// Subtract two currencies (same type)
Currency subtractCurrency(const Currency* a, const Currency* b) {
    if (strcmp(a->currencyType, b->currencyType) != 0) {
        cerr << "Error: Cannot subtract different currencies" << endl;
        exit(1);
    }
    Currency result;
    initCurrency(&result, a->amount - b->amount, a->currencyType);
    return result;
}

// Multiply by exchange rate
Currency multiplyByRate(const Currency* c, double rate) {
    Currency result;
    initCurrency(&result, c->amount * rate, c->currencyType);
    return result;
}

// Divide by exchange rate
Currency divideByRate(const Currency* c, double rate) {
    Currency result;
    initCurrency(&result, c->amount / rate, c->currencyType);
    return result;
}

// === Currency Converter (function only) ===
Currency convertCurrency(const Currency* from, const Currency* to, double rate) {
    if (strcmp(from->currencyType, to->currencyType) == 0) {
        cerr << "Error: Cannot convert same currency types" << endl;
        exit(1);
    }
    return multiplyByRate(from, rate);
}

// === Interest Calculator (function only) ===
double calculateCompoundInterest(double principal, double annualRate, int years) {
    return principal * pow(1 + annualRate, years);
}

// === Market Simulator ===
typedef struct {
    double currentRate;
    double volatility;
    mt19937 rng;
} MarketSimulator;

void initMarketSimulator(MarketSimulator* market, double initialRate, double volatility) {
    market->currentRate = initialRate;
    market->volatility = volatility;
    market->rng = mt19937(random_device()());
}

double simulateExchangeRate(MarketSimulator* market) {
    normal_distribution<double> dist(market->currentRate, market->volatility);
    market->currentRate = dist(market->rng);
    if (market->currentRate < 0) market->currentRate = 0.0; // Avoid negative rates
    return market->currentRate;
}

// === Main function ===
int main() {
    // Create currencies
    Currency usd, eur;
    initCurrency(&usd, 1000, "USD");
    initCurrency(&eur, 800, "EUR");

    // Test addition
    Currency tempUSD;
    initCurrency(&tempUSD, 500, "USD");
    Currency totalUSD = addCurrency(&usd, &tempUSD);
    cout << "Total USD: " << totalUSD.amount << " " << totalUSD.currencyType << endl;

    // Test subtraction
    Currency subUSD;
    initCurrency(&subUSD, 200, "USD");
    Currency remainingUSD = subtractCurrency(&usd, &subUSD);
    cout << "Remaining USD: " << remainingUSD.amount << " " << remainingUSD.currencyType << endl;

    // Convert USD to EUR
    double exchangeRate = 0.85;
    Currency convertedEUR = convertCurrency(&usd, &eur, exchangeRate);
    cout << "Converted USD to EUR: " << convertedEUR.amount << " " << convertedEUR.currencyType << endl;

    // Calculate compound interest
    double principal = 1000.0;
    double rate = 0.05; // 5% annual rate
    int years = 10;
    double futureValue = calculateCompoundInterest(principal, rate, years);
    cout << "Future value after " << years << " years at " << rate * 100 << "% interest: " << futureValue << endl;

    // Simulate exchange rates
    MarketSimulator market;
    initMarketSimulator(&market, 1.1, 0.05); // Initial rate = 1.1, volatility = 0.05
    for (int i = 0; i < 5; ++i) {
        double simulatedRate = simulateExchangeRate(&market);
        cout << "Simulated exchange rate: " << simulatedRate << endl;
    }

    return 0;
}
