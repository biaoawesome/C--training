#include <iostream>
#include <cmath>
#include <random>

using namespace std;

// Black-Scholes model parameters
const double riskFreeRate = 0.05;     // Risk-free interest rate
const double volatility = 0.2;        // Volatility of the underlying asset
const double timeToMaturity = 1.0;    // Time to maturity (in years)

// Maximum number of simulation paths
const int MAX_PATHS = 100000;
const int MAX_STEPS = 365;  // Max steps per year

// Structure to represent a partial-time barrier option
struct PartialTimeBarrierOption {
    double spotPrice;
    double strikePrice;
    double barrierPrice;
    double barrierStartTime;
    double barrierEndTime;
};

// Simulate one path and return payoff
double simulatePath(const PartialTimeBarrierOption* option, int numSteps) {
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> dist(0.0, 1.0);

    double currentPrice = option->spotPrice;
    bool barrierActivated = false;

    double dt = timeToMaturity / numSteps;

    for (int t = 0; t < numSteps; ++t) {
        double dz = dist(gen);
        currentPrice *= exp((riskFreeRate - 0.5 * pow(volatility, 2)) * dt + volatility * sqrt(dt) * dz);

        double currentTime = t * dt;
        if (currentTime >= option->barrierStartTime && currentTime <= option->barrierEndTime &&
            currentPrice <= option->barrierPrice) {
            barrierActivated = true;
            break;  // No need to continue simulation
        }
    }

    if (barrierActivated) {
        return 0.0;  // Knock-out condition triggered
    }

    return max(currentPrice - option->strikePrice, 0.0);  // Payoff at maturity
}

// Calculate option price using Monte Carlo simulation
double calculateOptionPrice(const PartialTimeBarrierOption* option, int numPaths, int numSteps) {
    double totalPayoff = 0.0;

    for (int i = 0; i < numPaths; ++i) {
        double payoff = simulatePath(option, numSteps);
        totalPayoff += payoff;
    }

    double avgPayoff = totalPayoff / numPaths;
    return exp(-riskFreeRate * timeToMaturity) * avgPayoff;
}

// Main function
int main() {
    // Initialize option parameters
    PartialTimeBarrierOption option;
    option.spotPrice = 100.0;           // Current stock price
    option.strikePrice = 105.0;         // Strike price
    option.barrierPrice = 95.0;         // Barrier level
    option.barrierStartTime = 0.25;     // Start of barrier period (in years)
    option.barrierEndTime = 0.75;       // End of barrier period (in years)

    // Simulation parameters
    int numPaths = 10000;   // Number of simulated paths
    int numSteps = MAX_STEPS;  // Daily steps

    // Compute option price
    double price = calculateOptionPrice(&option, numPaths, numSteps);

    // Output result
    cout.precision(4);
    cout << fixed << "The price of the Partial-Time Barrier Option is: " << price << endl;

    return 0;
}
