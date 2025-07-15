#include <iostream>
#include <cmath>
#include <random>

using namespace std;

// Constants
const int DAYS_PER_YEAR = 365;       // Number of days in a year
const int MAX_SIMULATIONS = 10000;   // Maximum number of Monte Carlo simulations

// Structure to store Chooser Option parameters
typedef struct {
    double spotPrice;      // Current underlying asset price
    double strikePrice;    // Strike price
    double riskFreeRate;   // Risk-free interest rate
    double volatility;     // Volatility of the underlying asset
    double maturity;       // Time to maturity (in years)
    double observationTime; // Observation time for Chooser Option
} ChooserOption;

// Standard normal cumulative distribution function
double N(double x) {
    return 0.5 * erfc(-x / sqrt(2));
}

// Generate random asset price path at maturity using Geometric Brownian Motion
double generateRandomPath(ChooserOption* opt) {
    default_random_engine gen((random_device())());
    normal_distribution<> dist(0, 1);

    double currentPrice = opt->spotPrice;
    double dt = opt->maturity / DAYS_PER_YEAR;

    for (int i = 0; i < DAYS_PER_YEAR; ++i) {
        double randNum = dist(gen);
        currentPrice *= exp((opt->riskFreeRate - 0.5 * pow(opt->volatility, 2)) * dt +
                            opt->volatility * sqrt(dt) * randNum);
    }

    return currentPrice;
}

// Perform Monte Carlo simulation to estimate Chooser Option price
double monteCarloSimulation(ChooserOption* opt, int numSimulations) {
    double totalPayoff = 0.0;

    for (int i = 0; i < numSimulations; ++i) {
        double finalPrice = generateRandomPath(opt);
        double payoff = max(finalPrice - opt->strikePrice, 0.0);  // Call payoff
        totalPayoff += payoff;
    }

    double avgPayoff = totalPayoff / numSimulations;
    return avgPayoff * exp(-opt->riskFreeRate * opt->maturity);  // Discounted expected payoff
}

// Main function
int main() {
    // Initialize Chooser Option parameters
    ChooserOption option;
    option.spotPrice = 100.0;          // Spot price
    option.strikePrice = 100.0;        // Strike price
    option.riskFreeRate = 0.05;        // Risk-free rate (5%)
    option.volatility = 0.2;           // Volatility (20%)
    option.maturity = 1.0;             // Maturity (1 year)
    option.observationTime = 0.5;      // Observation time (half year)

    // Run Monte Carlo simulation
    int numSimulations = 10000;        // Number of simulations
    double optionPrice = monteCarloSimulation(&option, numSimulations);

    cout.precision(6);
    cout << "Chooser Option Price (Monte Carlo Simulation): " << fixed << optionPrice << endl;

    return 0;
}
