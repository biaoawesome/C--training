#include <iostream>
#include <cmath>
#include <algorithm>

#define MAX_OPTIONS 100  // Maximum number of options to process in batch mode

// Cumulative distribution function for standard normal distribution N(x)
double normalCDF(double x) {
    return 0.5 * erfc(-x / std::sqrt(2.0));  // Using complementary error function
}

// Calculate the price of a European call option using Black's formula
double blackCallOptionPrice(double F0, double K, double T, double r, double sigma) {
    double d1 = (std::log(F0 / K) + (0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    double callPrice = std::exp(-r * T) * (F0 * normalCDF(d1) - K * normalCDF(d2));
    return callPrice;
}

// Calculate the price of a European put option using Black's formula
double blackPutOptionPrice(double F0, double K, double T, double r, double sigma) {
    double d1 = (std::log(F0 / K) + (0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    double putPrice = std::exp(-r * T) * (K * normalCDF(-d2) - F0 * normalCDF(-d1));
    return putPrice;
}

// Test function to compute and print prices for multiple options
void testBlackFormulaBatch() {
    // Example market data for multiple options
    const int numOptions = 3;

    double F0s[MAX_OPTIONS]     = {100.0, 110.0, 95.0};   // Futures prices
    double Ks[MAX_OPTIONS]      = {95.0, 105.0, 90.0};    // Strike prices
    double Ts[MAX_OPTIONS]      = {1.0, 0.5, 2.0};        // Time to maturity (years)
    double rs[MAX_OPTIONS]      = {0.05, 0.04, 0.06};     // Risk-free rates
    double sigmas[MAX_OPTIONS]  = {0.2, 0.25, 0.18};      // Volatilities

    // Arrays to store results
    double callPrices[MAX_OPTIONS];
    double putPrices[MAX_OPTIONS];

    // Compute prices for all options
    for (int i = 0; i < numOptions; ++i) {
        callPrices[i] = blackCallOptionPrice(F0s[i], Ks[i], Ts[i], rs[i], sigmas[i]);
        putPrices[i] = blackPutOptionPrice(F0s[i], Ks[i], Ts[i], rs[i], sigmas[i]);
    }

    // Print results
    std::cout.precision(4);
    std::cout << "Option\tCall Price\tPut Price\n";
    for (int i = 0; i < numOptions; ++i) {
        std::cout << i + 1 << "\t"
                  << std::fixed << callPrices[i] << "\t\t"
                  << putPrices[i] << "\n";
    }
}

int main() {
    // Run the batch pricing test using Black's formula
    testBlackFormulaBatch();
    return 0;
}
