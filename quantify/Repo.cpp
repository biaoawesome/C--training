#include <iostream>
#include <cmath>
#include <iomanip>

// Structure to hold parameter sets for multiple test cases
struct TestCase {
    double S;   // Spot price of the underlying asset
    double r;   // Repo rate (risk-free rate)
    double q;   // Dividend yield
    double T;   // Time to maturity in years
};

// Function to calculate forward price
double calculateForwardPrice(double S, double r, double q, double T) {
    return S * exp((r - q) * T);
}

// Function to discount cash flow using repo rate
double discountWithRepoRate(double cashFlow, double r, double T) {
    return cashFlow * exp(-r * T);
}

// Main function
int main() {
    // Configuration: Maximum number of test cases
    const int MAX_CASES = 10;

    // Static array of test cases
    TestCase testCases[MAX_CASES] = {
        {100.0, 0.05, 0.02, 1.0},
        {120.0, 0.04, 0.01, 2.0},
        {80.0,  0.06, 0.03, 0.5}
    };

    int numCases = 3; // Number of actual test cases used

    // Set output precision
    std::cout << std::fixed << std::setprecision(4);

    // Loop through each case and compute results
    for (int i = 0; i < numCases; ++i) {
        double forwardPrice = calculateForwardPrice(
            testCases[i].S, testCases[i].r, testCases[i].q, testCases[i].T);

        double discountedForwardPrice = discountWithRepoRate(forwardPrice, testCases[i].r, testCases[i].T);

        std::cout << "\nTest Case " << i + 1 << ":\n";
        std::cout << "Spot Price (S): " << testCases[i].S << "\n";
        std::cout << "Repo Rate (r): " << testCases[i].r << "\n";
        std::cout << "Dividend Yield (q): " << testCases[i].q << "\n";
        std::cout << "Time to Maturity (T): " << testCases[i].T << "\n";
        std::cout << "Forward Price: " << forwardPrice << "\n";
        std::cout << "Discounted Forward Price: " << discountedForwardPrice << "\n";
    }

    return 0;
}
