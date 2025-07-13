#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>

#define MAX_STEPS 10000  // Maximum number of steps in a year for simulation
#define MAX_SIMULATIONS 100000  // Maximum number of Monte Carlo simulations

// Bond Parameters Structure
struct BondParams {
    double faceValue;    // Face value of the bond
    double couponRate;   // Annual coupon rate (e.g., 3% = 0.03)
    int maturity;        // Time to maturity in years
    int frequency;       // Payment frequency per year (e.g., 2 = semi-annual)
};

// CPI Parameters Structure
struct CPIParams {
    double initialCPI;   // Initial Consumer Price Index
    double drift;        // Annual growth rate of CPI
    double volatility;   // Volatility of CPI
};

// Market Parameters Structure
struct MarketParams {
    double interestRate;  // Risk-free interest rate
    int simulations;      // Number of Monte Carlo simulations
    int steps;            // Number of time steps per year
};

// Function to simulate CPI path using Geometric Brownian Motion
void simulateCPIPath(const CPIParams& cpiParams, const MarketParams& marketParams, double cpiPath[]) {
    std::mt19937 gen(42);  // Fixed seed for reproducibility
    std::normal_distribution<> dist(0.0, 1.0);

    double dt = 1.0 / marketParams.steps;
    cpiPath[0] = cpiParams.initialCPI;

    for (int i = 1; i <= marketParams.steps; ++i) {
        double randomShock = dist(gen);
        cpiPath[i] = cpiPath[i - 1] * std::exp((cpiParams.drift - 0.5 * cpiParams.volatility * cpiParams.volatility) * dt +
                                              cpiParams.volatility * std::sqrt(dt) * randomShock);
    }
}

// Calculate coupon payment adjusted by CPI
double calculateCouponValue(const BondParams& bondParams, const double cpiPath[], int step, int frequency) {
    return bondParams.faceValue * bondParams.couponRate * cpiPath[step] / 100.0 / frequency;
}

// Price the inflation-linked bond using Monte Carlo simulation with CPI impact
double priceBond(const BondParams& bondParams, const CPIParams& cpiParams, const MarketParams& marketParams) {
    double totalBondPrice = 0.0;
    double dt = 1.0 / marketParams.steps;
    double discountRate = marketParams.interestRate * dt;

    // Preallocate static arrays for CPI paths
    double cpiPath[MAX_STEPS + 1];

    // Monte Carlo Simulation
    for (int sim = 0; sim < marketParams.simulations && sim < MAX_SIMULATIONS; ++sim) {
        simulateCPIPath(cpiParams, marketParams, cpiPath);
        double totalCashFlow = 0.0;

        // Compute discounted cashflows over all periods
        int totalPeriods = bondParams.maturity * bondParams.frequency;
        for (int t = 0; t < totalPeriods; ++t) {
            int step = (t * marketParams.steps) / totalPeriods;
            double coupon = calculateCouponValue(bondParams, cpiPath, step, bondParams.frequency);
            totalCashFlow += coupon / std::pow(1 + discountRate, t + 1);
        }

        // Add principal repayment at maturity
        totalCashFlow += bondParams.faceValue / std::pow(1 + discountRate, totalPeriods);

        // Accumulate bond price
        totalBondPrice += totalCashFlow;
    }

    // Return average price across all simulations
    return totalBondPrice / marketParams.simulations;
}

// Main function
int main() {
    // Define bond parameters
    BondParams bondParams = {
        1000000.0,  // Face value: $1 million
        0.03,       // Coupon rate: 3%
        10,         // Maturity: 10 years
        2           // Semi-annual payments
    };

    // Define CPI parameters
    CPIParams cpiParams = {
        100.0,      // Initial CPI: 100
        0.02,       // CPI annual drift: 2%
        0.03        // CPI volatility: 3%
    };

    // Define market parameters
    MarketParams marketParams = {
        0.02,       // Risk-free interest rate: 2%
        10000,      // Number of Monte Carlo simulations
        252         // Steps per year: 252 trading days
    };

    // Calculate bond price
    double bondPrice = priceBond(bondParams, cpiParams, marketParams);

    // Output result
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Inflation-Linked Bond Price: " << bondPrice << std::endl;

    return 0;
}
