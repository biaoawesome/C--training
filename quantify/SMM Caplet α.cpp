#include <iostream>
#include <cmath>
#include <random>

using namespace std;

// Constants
const int DAYS_PER_YEAR = 365;       // Number of days in a year

// Standard normal cumulative distribution function
double N(double x) {
    return 0.5 * erfc(-x / sqrt(2));
}

// SMM Caplet parameters structure
typedef struct {
    double spotRate;       // Current interest rate
    double strikePrice;    // Strike price (strike rate)
    double meanReversion;  // Speed of mean reversion
    double longTermMean;   // Long-term mean interest rate
    double volatility;     // Volatility of the interest rate
    double maturity;       // Time to maturity (in years)
    int numPaths;          // Number of Monte Carlo simulation paths
} SMMCaplet;

// Simulate interest rate path using SMM model
void simulateRatePath(SMMCaplet* caplet, double path[]) {
    random_device rd;
    default_random_engine gen(rd());
    normal_distribution<> dist(0, 1);  // Standard normal distribution

    double dt = caplet->maturity / DAYS_PER_YEAR;
    path[0] = caplet->spotRate;

    for (int i = 1; i <= DAYS_PER_YEAR; ++i) {
        double dz = dist(gen);
        double dS = caplet->meanReversion * (caplet->longTermMean - path[i - 1]) * dt +
                    caplet->volatility * path[i - 1] * sqrt(dt) * dz;
        path[i] = path[i - 1] + dS;
    }
}

// Calculate Caplet price using Monte Carlo simulation
double priceCaplet(SMMCaplet* caplet) {
    double totalPayoff = 0.0;
    double path[DAYS_PER_YEAR + 1];  // Static array to store simulated rate path

    for (int i = 0; i < caplet->numPaths; ++i) {
        simulateRatePath(caplet, path);
        double finalRate = path[DAYS_PER_YEAR];
        double payoff = max(finalRate - caplet->strikePrice, 0.0);
        totalPayoff += payoff;
    }

    return totalPayoff / caplet->numPaths;
}

// Calibrate mean reversion parameter (alpha) using gradient descent
double calibrateAlpha(SMMCaplet* caplet, double alphaStart, double learningRate, int iterations) {
    double alpha = alphaStart;

    for (int i = 0; i < iterations; ++i) {
        caplet->meanReversion = alpha;
        double modelPrice = priceCaplet(caplet);
        double marketPrice = 5.0;  // Assume market price is 5.0
        double error = modelPrice - marketPrice;

        // Gradient descent update
        alpha -= learningRate * error;

        if (i % 10 == 0) {
            cout << "Iteration " << i << ": alpha = " << alpha << ", error = " << error << endl;
        }
    }

    return alpha;
}

// Main function
int main() {
    // Initialize SMM Caplet parameters
    SMMCaplet caplet;
    caplet.spotRate = 0.05;          // Initial interest rate: 5%
    caplet.strikePrice = 0.04;       // Strike rate: 4%
    caplet.meanReversion = 0.1;      // Initial mean reversion speed
    caplet.longTermMean = 0.03;      // Long-term average rate: 3%
    caplet.volatility = 0.02;        // Volatility: 2%
    caplet.maturity = 1.0;           // Maturity: 1 year
    caplet.numPaths = 1000;          // Number of simulation paths

    // Run pricing
    double capletPrice = priceCaplet(&caplet);
    cout << "Simulated Caplet Price: " << capletPrice << endl;

    // Run calibration
    double calibratedAlpha = calibrateAlpha(&caplet, 1.0, 0.01, 100);
    cout << "Calibrated Alpha: " << calibratedAlpha << endl;

    return 0;
}
