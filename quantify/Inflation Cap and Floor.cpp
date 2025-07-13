#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>

// Configuration: Maximum number of simulation paths and steps
#define MAX_PATHS 10000   // Max number of Monte Carlo paths
#define MAX_STEPS 100     // Max number of time steps per path

// Inflation Parameters Structure
struct InflationParams {
    double initialRate;   // Initial inflation rate (e.g., 2% = 0.02)
    double volatility;    // Annualized volatility (e.g., 1% = 0.01)
    double maturity;      // Time to maturity in years
    double upperLimit;    // Cap level (e.g., 2.5% = 0.025)
    double lowerLimit;    // Floor level (e.g., 1.5% = 0.015)
    double discountRate;  // Annual risk-free discount rate
    int numPaths;         // Number of Monte Carlo paths to simulate
    int steps;            // Number of time steps per path
};

// Random number generator setup
std::random_device rd;
std::mt19937 generator(rd());
std::normal_distribution<double> distribution(0.0, 1.0);

// Simulate inflation rate paths using log-normal process
void simulateInflationPaths(const InflationParams& params, double paths[][MAX_STEPS + 1]) {
    double dt = params.maturity / params.steps;

    for (int i = 0; i < params.numPaths; ++i) {
        paths[i][0] = params.initialRate;  // Initial inflation rate
        for (int j = 1; j <= params.steps; ++j) {
            double dW = sqrt(dt) * distribution(generator); // Brownian increment
            paths[i][j] = paths[i][j - 1] * exp(-0.5 * params.volatility * params.volatility * dt +
                                                params.volatility * dW);
        }
    }
}

// Calculate price of an inflation cap option
double priceInflationCap(const InflationParams& params, const double paths[][MAX_STEPS + 1]) {
    double payoffSum = 0.0;
    double discountFactor = exp(-params.discountRate * params.maturity);

    for (int i = 0; i < params.numPaths; ++i) {
        double terminalRate = paths[i][params.steps];
        double payoff = std::max(terminalRate - params.upperLimit, 0.0);
        payoffSum += payoff;
    }

    return discountFactor * payoffSum / params.numPaths;
}

// Calculate price of an inflation floor option
double priceInflationFloor(const InflationParams& params, const double paths[][MAX_STEPS + 1]) {
    double payoffSum = 0.0;
    double discountFactor = exp(-params.discountRate * params.maturity);

    for (int i = 0; i < params.numPaths; ++i) {
        double terminalRate = paths[i][params.steps];
        double payoff = std::max(params.lowerLimit - terminalRate, 0.0);
        payoffSum += payoff;
    }

    return discountFactor * payoffSum / params.numPaths;
}

// Main function
int main() {
    // Define inflation parameters
    InflationParams params = {
        0.02,    // Initial inflation rate: 2%
        0.01,    // Volatility: 1%
        1.0,     // Maturity: 1 year
        0.025,   // Cap strike: 2.5%
        0.015,   // Floor strike: 1.5%
        0.03,    // Discount rate: 3%
        10000,   // Number of Monte Carlo paths
        100      // Time steps per path
    };

    // Check if the configuration is within static array limits
    if (params.numPaths > MAX_PATHS || params.steps > MAX_STEPS) {
        std::cerr << "Error: Simulation parameters exceed static array size." << std::endl;
        return 1;
    }

    // Use a static local array to avoid stack overflow
    static double paths[MAX_PATHS][MAX_STEPS + 1];

    // Simulate inflation paths
    simulateInflationPaths(params, paths);

    // Calculate inflation cap and floor prices
    double capPrice = priceInflationCap(params, paths);
    double floorPrice = priceInflationFloor(params, paths);

    // Output results
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Inflation Cap Price: " << capPrice << std::endl;
    std::cout << "Inflation Floor Price: " << floorPrice << std::endl;

    return 0;
}
