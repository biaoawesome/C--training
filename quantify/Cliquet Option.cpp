#include <iostream>
#include <cmath>
#include <random>

#define MAX_SIMULATIONS 100000  // Maximum number of Monte Carlo simulations

// Cliquet Option Pricing Class
class CliquetOption {
public:
    // Constructor: Initialize parameters
    CliquetOption(double S0, double K, double T, int n, double r, double sigma)
        : S0(S0), K(K), T(T), n(n), r(r), sigma(sigma) {}

    // Price the cliquet option using Monte Carlo simulation
    double price(int numSimulations) {
        // Static array to store simulated prices
        double optionPrices[MAX_SIMULATIONS];

        // Run Monte Carlo simulations
        for (int i = 0; i < numSimulations; ++i) {
            double payoff = 0.0;
            double S = S0;  // Start with initial asset price

            for (int j = 1; j <= n; ++j) {
                // Generate random normal variable
                double Z = generateNormalRandom();

                // Simulate asset price path using geometric Brownian motion
                double dt = T / n;
                S = S * std::exp((r - 0.5 * sigma * sigma) * dt + sigma * std::sqrt(dt) * Z);

                // Calculate payoff per period
                double payoffPeriod = std::max(S - S0, 0.0);
                payoff += payoffPeriod;

                // Reset base price for next period
                S0 = S;
            }

            // Discount final payoff and store
            optionPrices[i] = payoff * std::exp(-r * T);
        }

        // Compute average price
        double sum = 0.0;
        for (int i = 0; i < numSimulations; ++i) {
            sum += optionPrices[i];
        }

        return sum / numSimulations;
    }

private:
    double S0;     // Initial asset price
    double K;      // Strike price
    double T;      // Time to maturity (in years)
    int n;         // Number of observation periods
    double r;      // Risk-free interest rate
    double sigma;  // Volatility of the underlying asset

    // Generate standard normal random number
    double generateNormalRandom() {
        static std::mt19937 gen(42);  // Fixed seed for reproducibility
        std::normal_distribution<> d(0.0, 1.0);
        return d(gen);
    }
};

// Test function to simulate a cliquet option
void testCliquetOption() {
    // Set pricing parameters
    double S0 = 100.0;   // Initial asset price
    double K = 100.0;    // Strike price
    double T = 1.0;      // Time to maturity (1 year)
    int n = 12;          // Monthly reset (12 periods)
    double r = 0.05;     // Risk-free rate (5%)
    double sigma = 0.2;  // Volatility (20%)

    // Create CliquetOption instance
    CliquetOption option(S0, K, T, n, r, sigma);

    // Set number of simulations
    int numSimulations = 10000;

    // Calculate and print estimated option price
    double estimatedPrice = option.price(numSimulations);
    std::cout << "The estimated price of the Cliquet Option is: " << estimatedPrice << std::endl;
}

// Main entry point
int main() {
    // Run the cliquet option test
    testCliquetOption();

    return 0;
}
