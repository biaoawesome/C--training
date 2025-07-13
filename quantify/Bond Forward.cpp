#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

// Configuration: Maximum number of steps in binomial tree
#define MAX_STEPS 1000   // Max allowed steps in the binomial tree

// Callable Bond Parameters Structure
struct CallableBondParams {
    double faceValue;      // Face value of the bond
    double couponRate;     // Annual coupon rate (e.g., 5% = 0.05)
    int maturity;          // Time to maturity in years
    int frequency;         // Number of payments per year (e.g., 2 = semi-annual)
    double callPrice;      // Call price before maturity
    int callStartYear;     // First year when issuer can call the bond
};

// Market Parameters Structure
struct MarketParams {
    double initialRate;   // Initial short-term interest rate
    double volatility;    // Volatility of interest rates
    int steps;            // Number of time steps in binomial tree
};

// Function to calculate a plain vanilla bond price without embedded options
double calculateBondPrice(double faceValue, double couponRate, double rate, int maturity, int frequency) {
    double coupon = faceValue * couponRate / frequency;
    double discountRate = rate / frequency;
    int totalPayments = maturity * frequency;
    double price = 0.0;

    for (int i = 1; i <= totalPayments; ++i) {
        price += coupon / pow(1 + discountRate, i);
    }

    // Add principal repayment at maturity
    price += faceValue / pow(1 + discountRate, totalPayments);

    return price;
}

// Binomial Tree Model to Price Callable Bonds
double priceCallableBond(const CallableBondParams& bondParams, const MarketParams& marketParams) {
    double dt = 1.0 / marketParams.steps;
    double u = exp(marketParams.volatility * sqrt(dt)); // Up factor
    double d = 1.0 / u;                                 // Down factor
    double p = (exp(marketParams.initialRate * dt) - d) / (u - d); // Risk-neutral probability
    double q = 1.0 - p;

    // Static arrays for rate and price trees
    double rateTree[MAX_STEPS + 1][MAX_STEPS + 1] = {0};
    double priceTree[MAX_STEPS + 1][MAX_STEPS + 1] = {0};

    // Initialize root node
    rateTree[0][0] = marketParams.initialRate;

    // Build interest rate tree
    for (int i = 1; i <= marketParams.steps; ++i) {
        for (int j = 0; j <= i; ++j) {
            rateTree[i][j] = marketParams.initialRate * pow(u, j) * pow(d, i - j);
        }
    }

    double coupon = bondParams.faceValue * bondParams.couponRate / bondParams.frequency;

    // Terminal prices at maturity
    for (int j = 0; j <= marketParams.steps; ++j) {
        double terminalPrice = bondParams.faceValue;
        for (int k = 1; k <= bondParams.maturity * bondParams.frequency; ++k) {
            terminalPrice += coupon / pow(1 + rateTree[marketParams.steps][j] / bondParams.frequency, k);
        }
        priceTree[marketParams.steps][j] = terminalPrice;
    }

    // Backward induction through the tree
    for (int i = marketParams.steps - 1; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            double discountedValue = (p * priceTree[i + 1][j + 1] + q * priceTree[i + 1][j]) /
                                     (1 + rateTree[i][j] * dt);

            int currentStepYear = static_cast<int>(round(static_cast<double>(i) * bondParams.maturity / marketParams.steps));

            if (currentStepYear >= bondParams.callStartYear) {
                priceTree[i][j] = std::min(discountedValue, bondParams.callPrice); // Issuer may call the bond
            } else {
                priceTree[i][j] = discountedValue;
            }
        }
    }

    return priceTree[0][0]; // Return bond price at root node
}

// Main function
int main() {
    // Define callable bond parameters
    CallableBondParams bondParams = {
        1000.0,    // Face value: $1000
        0.05,      // Coupon rate: 5%
        10,        // Maturity: 10 years
        2,         // Semi-annual coupon payments
        1050.0,    // Call price: $1050
        5          // Callable starting from year 5
    };

    // Define market parameters
    MarketParams marketParams = {
        0.03,      // Initial interest rate: 3%
        0.02,      // Interest rate volatility: 2%
        10         // Number of steps in binomial tree
    };

    // Calculate callable bond price
    double callableBondPrice = priceCallableBond(bondParams, marketParams);

    // Output result
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Callable Bond Price: $" << callableBondPrice << std::endl;

    return 0;
}
