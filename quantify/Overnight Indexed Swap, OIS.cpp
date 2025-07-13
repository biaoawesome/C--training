#include <iostream>
#include <cmath>
#include <iomanip>

const size_t MAX_OIS_POINTS = 10; // Maximum number of OIS points allowed

// Define OIS rate data point
struct OISPoint {
    double time;  // Time in years
    double rate;  // Annualized OIS rate
};

// Calculate discount factors using continuous compounding
void calculateDiscountFactors(const OISPoint oisData[], double discountFactors[], int numPoints) {
    for (int i = 0; i < numPoints; ++i) {
        discountFactors[i] = std::exp(-oisData[i].rate * oisData[i].time);
    }
}

// Compute NPV of fixed leg
double calculateFixedLegNPV(double fixedRate, double notional,
                            const double discountFactors[], int numPayments, double paymentFrequency) {
    double npv = 0.0;
    for (int i = 0; i < numPayments; ++i) {
        npv += fixedRate * notional * discountFactors[i] * paymentFrequency;
    }
    return npv;
}

// Compute NPV of floating leg assuming zero spread
double calculateFloatingLegNPV(double notional, const double discountFactors[],
                               int numPayments, double paymentFrequency) {
    double npv = 0.0;
    for (int i = 0; i < numPayments; ++i) {
        // Assume future floating rates are equal to current OIS rates
        npv += notional * discountFactors[i] * paymentFrequency;
    }
    return npv;
}

// Main function
int main() {
    // Input market data (OIS points)
    OISPoint oisData[MAX_OIS_POINTS] = {
        {0.25, 0.01},   // 3 months, annual rate 1%
        {0.5, 0.011},   // 6 months, annual rate 1.1%
        {1.0, 0.012},   // 1 year, annual rate 1.2%
        {2.0, 0.014},   // 2 years, annual rate 1.4%
        {5.0, 0.018}    // 5 years, annual rate 1.8%
    };
    int numOISPoints = 5;

    double notional = 1e6;           // Notional amount
    double fixedRate = 0.015;        // Fixed rate (1.5%)
    double paymentFrequency = 0.5;   // Payment every half year

    // Array to store discount factors
    double discountFactors[MAX_OIS_POINTS];

    // Calculate discount factors
    calculateDiscountFactors(oisData, discountFactors, numOISPoints);

    // Determine number of payments based on frequency and number of discount factors
    int numPayments = static_cast<int>(1.0 / paymentFrequency * discountFactors[0]);

    // Ensure we don't exceed the number of available discount factors
    numPayments = std::min(numPayments, numOISPoints);

    // Calculate NPVs of fixed and floating legs
    double fixedLegNPV = calculateFixedLegNPV(fixedRate, notional, discountFactors, numPayments, paymentFrequency);
    double floatingLegNPV = calculateFloatingLegNPV(notional, discountFactors, numPayments, paymentFrequency);

    // Swap price is the difference between the two legs
    double swapPrice = fixedLegNPV - floatingLegNPV;

    // Output results
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Discount Factors:" << std::endl;
    for (int i = 0; i < numPayments; ++i) {
        std::cout << "Time " << oisData[i].time << " years: " << discountFactors[i] << std::endl;
    }

    std::cout << "\nNPV of Fixed Leg: " << fixedLegNPV << std::endl;
    std::cout << "NPV of Floating Leg: " << floatingLegNPV << std::endl;
    std::cout << "Swap Price: " << swapPrice << std::endl;

    return 0;
}
