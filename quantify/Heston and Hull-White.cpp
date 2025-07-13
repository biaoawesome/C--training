#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>

// Configuration: Maximum number of simulation paths and time steps
#define MAX_PATHS 50000    // Max number of Monte Carlo paths
#define MAX_STEPS 1000     // Max number of time steps per path

// Heston model parameters
struct HestonParams {
    double kappa;    // Mean reversion speed
    double theta;    // Long-term variance
    double sigma_v;  // Volatility of volatility
    double rho;      // Correlation between asset price and volatility
    double v0;       // Initial variance
};

// Hull-White short rate model parameters
struct HullWhiteParams {
    double a;        // Mean reversion speed
    double b;        // Long-term mean interest rate
    double sigma_r;  // Volatility of the short rate
    double r0;       // Initial interest rate
};

// Random number generator setup
std::random_device rd;
std::mt19937 generator(rd());
std::normal_distribution<double> distribution(0.0, 1.0);

// Simulate correlated stock and interest rate paths using Heston and Hull-White models
void simulatePaths(
    const HestonParams& hestonParams,
    const HullWhiteParams& hwParams,
    double S0, double T, int steps, int numPaths,
    double stockPaths[][MAX_STEPS + 1],
    double ratePaths[][MAX_STEPS + 1]
) {
    double dt = T / steps;

    for (int i = 0; i < numPaths; ++i) {
        double S = S0;
        double v = hestonParams.v0;
        double r = hwParams.r0;

        stockPaths[i][0] = S;
        ratePaths[i][0] = r;

        for (int j = 1; j <= steps; ++j) {
            // Generate correlated Brownian motions
            double dW1 = distribution(generator);
            double dW2 = hestonParams.rho * dW1 +
                         std::sqrt(1 - hestonParams.rho * hestonParams.rho) * distribution(generator);

            // Update variance under Heston model
            v = std::max(0.0,
                         v + hestonParams.kappa * (hestonParams.theta - v) * dt +
                         hestonParams.sigma_v * std::sqrt(v * dt) * dW1);

            // Update stock price with stochastic volatility
            S *= std::exp((r - 0.5 * v) * dt + std::sqrt(v * dt) * dW2);

            // Update interest rate under Hull-White model
            r += hwParams.a * (hwParams.b - r) * dt +
                 hwParams.sigma_r * std::sqrt(dt) * distribution(generator);

            // Save simulated values
            stockPaths[i][j] = S;
            ratePaths[i][j] = r;
        }
    }
}

// Price European call option using Monte Carlo simulation
double priceEuropeanCall(
    double stockPaths[][MAX_STEPS + 1],
    int steps, int numPaths,
    double K, double avgRate, double T
) {
    double payoffSum = 0.0;

    for (int i = 0; i < numPaths; ++i) {
        double ST = stockPaths[i][steps];
        payoffSum += std::max(ST - K, 0.0);
    }

    return std::exp(-avgRate * T) * payoffSum / numPaths;
}

// Main function
int main() {
    // Define model parameters
    HestonParams hestonParams = {2.0, 0.02, 0.1, -0.7, 0.02};   // Heston parameters
    HullWhiteParams hwParams = {0.1, 0.03, 0.01, 0.03};         // Hull-White parameters

    double S0 = 100.0;    // Initial stock price
    double K = 100.0;     // Strike price
    double T = 1.0;       // Time to maturity in years
    int steps = 100;      // Number of time steps
    int numPaths = 10000; // Number of Monte Carlo paths

    // Check if configuration exceeds static array size
    if (numPaths > MAX_PATHS || steps > MAX_STEPS) {
        std::cerr << "Error: Simulation parameters exceed static array size." << std::endl;
        return 1;
    }

    // Use static arrays to avoid stack overflow
    static double stockPaths[MAX_PATHS][MAX_STEPS + 1];
    static double ratePaths[MAX_PATHS][MAX_STEPS + 1];

    // Simulate paths
    simulatePaths(hestonParams, hwParams, S0, T, steps, numPaths, stockPaths, ratePaths);

    // Compute average terminal interest rate
    double avgRate = 0.0;
    for (int i = 0; i < numPaths; ++i) {
        avgRate += ratePaths[i][steps];
    }
    avgRate /= numPaths;

    // Calculate European call option price
    double optionPrice = priceEuropeanCall(stockPaths, steps, numPaths, K, avgRate, T);

    // Output results
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "European Call Option Price: " << optionPrice << std::endl;

    return 0;
}
