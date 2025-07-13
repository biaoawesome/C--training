#include <iostream>
#include <cmath>

#define MAX_OPTIONS 100  // Maximum number of options to process in batch mode

// Cumulative distribution function for standard normal distribution N(x)
double normalCDF(double x) {
    return 0.5 * erfc(-x / std::sqrt(2.0));  // Using complementary error function
}

// Calculate call option delta using the Black-Scholes formula
double blackCallDelta(double F0, double K, double T, double r, double sigma) {
    double d1 = (std::log(F0 / K) + (0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    return normalCDF(d1);
}

// Calculate put option delta using the Black-Scholes formula
double blackPutDelta(double F0, double K, double T, double r, double sigma) {
    double d1 = (std::log(F0 / K) + (0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    return normalCDF(d1) - 1.0;
}

// Test function to compute and print deltas for multiple options
void testBlackDeltaBatch() {
    // Example market data for multiple options
    const int numOptions = 3;

    double F0s[MAX_OPTIONS]     = {100.0, 110.0, 95.0};   // Futures prices
    double Ks[MAX_OPTIONS]      = {95.0, 105.0, 90.0};    // Strike prices
    double Ts[MAX_OPTIONS]      = {1.0, 0.5, 2.0};        // Time to maturity (years)
    double rs[MAX_OPTIONS]      = {0.05, 0.04, 0.06};     // Risk-free rates
    double sigmas[MAX_OPTIONS]  = {0.2, 0.25, 0.18};      // Volatilities

    // Arrays to store results
    double callDeltas[MAX_OPTIONS];
    double putDeltas[MAX_OPTIONS];

    // Compute deltas for all options
    for (int i = 0; i < numOptions; ++i) {
        callDeltas[i] = blackCallDelta(F0s[i], Ks[i], Ts[i], rs[i], sigmas[i]);
        putDeltas[i] = blackPutDelta(F0s[i], Ks[i], Ts[i], rs[i], sigmas[i]);
    }

    // Print results
    std::cout.precision(4);
    std::cout << "Option\tCall Delta\tPut Delta\n";
    for (int i = 0; i < numOptions; ++i) {
        std::cout << i + 1 << "\t"
                  << std::fixed << callDeltas[i] << "\t\t"
                  << putDeltas[i] << "\n";
    }
}

int main() {
    // Run the batch delta calculation test
    testBlackDeltaBatch();
    return 0;
}
