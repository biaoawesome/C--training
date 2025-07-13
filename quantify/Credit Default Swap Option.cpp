#include <iostream>
#include <cmath>
#include <algorithm>

#define MAX_YEARS 100  // Maximum number of years for default probabilities

// Class to represent a Credit Default Swap (CDS) contract
class CreditDefaultSwap {
public:
    // Constructor: Initialize CDS with spread, notional, recovery rate, and discount rate
    CreditDefaultSwap(double spread, double notional, double recoveryRate, double discountRate)
        : spread(spread), notional(notional), recoveryRate(recoveryRate), discountRate(discountRate) {}

    // Set cached spread value (simulate changes in spread)
    void setCachedSpread(double cachedSpread) {
        spread = cachedSpread;
    }

    // Calculate the price of the CDS contract
    double calculateCDSPrice(int maturityYears, const double defaultProbabilities[]) {
        double cdsPrice = 0.0;

        // Loop through each year and compute cash flows
        for (int t = 1; t <= maturityYears; ++t) {
            double discountFactor = exp(-discountRate * t);  // Discount factor
            double survivalProbability = 1.0;                // Start with no default

            // Adjust survival probability based on historical default probabilities
            for (int i = 0; i < t; ++i) {
                survivalProbability *= (1 - defaultProbabilities[i]);
            }

            // Premium payment per year
            double premiumPayment = spread * survivalProbability * discountFactor * notional;

            // Default payment if default occurs in this year
            double defaultPayment = (1 - recoveryRate) * notional * defaultProbabilities[t - 1] * discountFactor;

            // Accumulate total CDS price
            cdsPrice += premiumPayment + defaultPayment;
        }

        return cdsPrice;
    }

private:
    double spread;         // Annual spread (in decimal)
    double notional;       // Notional amount
    double recoveryRate;   // Recovery rate after default
    double discountRate;   // Risk-free discount rate
};

// Class to represent a CDS Option
class CDSOption {
public:
    // Constructor: Initialize option parameters
    CDSOption(double strikePrice, double notional, double maturityTime, double volatility, double discountRate)
        : strikePrice(strikePrice), notional(notional), maturityTime(maturityTime),
          volatility(volatility), discountRate(discountRate) {}

    // Calculate the price of the CDS Option using intrinsic value model
    double calculateOptionPrice(CreditDefaultSwap& cds, int maturityYears, const double defaultProbabilities[]) {
        double cdsPrice = cds.calculateCDSPrice(maturityYears, defaultProbabilities);

        // Intrinsic value of the option
        double optionValue = std::max(0.0, cdsPrice - strikePrice);

        // Apply discounting to get present value
        double optionPremium = optionValue * exp(-discountRate * maturityTime);

        return optionPremium;
    }

private:
    double strikePrice;    // Strike price of the option
    double notional;       // Notional amount
    double maturityTime;   // Time to maturity of the option
    double volatility;     // Volatility of the underlying CDS
    double discountRate;   // Risk-free discount rate
};

// Test function to price a CDS Option
void testCDSOption() {
    // Create a CDS contract: spread=0.02, notional=1,000,000, recovery=0.4, discount=0.03
    CreditDefaultSwap cds(0.02, 1000000, 0.4, 0.03);

    // Set cached spread to new value: 0.03
    cds.setCachedSpread(0.03);

    // Define static array of annual default probabilities
    const int maturityYears = 5;
    double defaultProbabilities[MAX_YEARS] = {0.01, 0.015, 0.02, 0.025, 0.03};

    // Create a CDS Option: strike=1,000,000, maturity=5 years, volatility=0.2, discount=0.03
    CDSOption cdsOption(1000000, 1000000, 5, 0.2, 0.03);

    // Calculate the price of the CDS Option
    double cdsOptionPrice = cdsOption.calculateOptionPrice(cds, maturityYears, defaultProbabilities);

    // Output the result
    std::cout << "The calculated CDS Option price is: " << cdsOptionPrice << std::endl;
}

// Main function to run the test
int main() {
    // Execute the CDS Option pricing test
    testCDSOption();

    return 0;
}
