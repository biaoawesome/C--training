#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>

using namespace std;

// Structure to represent a cash flow
struct Cashflow {
    double amount;
    int time;
};

// Maximum number of cash flows and steps
const int MAX_CASHFLOWS = 20;
const int MAX_STEPS = 2520; // Max simulation steps (e.g., 10 years * 252)

// Function to calculate present value of cashflows
double calculatePresentValue(const Cashflow cashflows[], int count, double discountRate) {
    double pv = 0.0;
    for (int i = 0; i < count; ++i) {
        pv += cashflows[i].amount / pow(1 + discountRate, cashflows[i].time);
    }
    return pv;
}

// Generate coupon and principal cashflows
void generateCashflows(Cashflow result[], int* count, double faceValue, double couponRate, int maturity) {
    *count = 0;
    for (int year = 1; year <= maturity; ++year) {
        result[*count].amount = faceValue * couponRate;
        result[*count].time = year;
        (*count)++;
    }
    result[*count].amount = faceValue;
    result[*count].time = maturity;
    (*count)++;
}

// Simulate CPI path using geometric Brownian motion
void simulateCPIPath(double cpiPath[], int steps, double initial, double drift, double volatility) {
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> dist(0.0, 1.0);

    double dt = 1.0 / steps;
    cpiPath[0] = initial;
    for (int i = 1; i <= steps; ++i) {
        double shock = dist(gen);
        cpiPath[i] = cpiPath[i - 1] * exp((drift - 0.5 * volatility * volatility) * dt + volatility * sqrt(dt) * shock);
    }
}

// Generate CPI-linked cashflows based on simulated CPI
void generateCPILinkedCashflows(Cashflow result[], int* count, double faceValue, double couponRate,
                                int maturity, const double cpiPath[], int stepsPerYear) {
    *count = 0;
    for (int year = 1; year <= maturity; ++year) {
        int index = year * stepsPerYear;
        if (index > MAX_STEPS) index = MAX_STEPS;
        double adjustedCoupon = faceValue * couponRate * cpiPath[index] / 100.0;
        result[*count].amount = adjustedCoupon;
        result[*count].time = year;
        (*count)++;
    }
    result[*count].amount = faceValue;
    result[*count].time = maturity;
    (*count)++;
}

// Calculate the present value of the swap
double calculateSwapPV(double faceValue, double couponRate, int maturity,
                       double discountRate, double cpiInitial, double cpiDrift, double cpiVolatility,
                       int stepsPerYear) {
    // Fixed bond cashflows
    Cashflow fixedFlows[MAX_CASHFLOWS];
    int fixedCount;
    generateCashflows(fixedFlows, &fixedCount, faceValue, couponRate, maturity);
    double fixedPV = calculatePresentValue(fixedFlows, fixedCount, discountRate);

    // CPI bond cashflows
    int totalSteps = maturity * stepsPerYear;
    double cpiPath[MAX_STEPS + 1];
    simulateCPIPath(cpiPath, totalSteps, cpiInitial, cpiDrift, cpiVolatility);

    Cashflow cpiFlows[MAX_CASHFLOWS];
    int cpiCount;
    generateCPILinkedCashflows(cpiFlows, &cpiCount, faceValue, couponRate, maturity, cpiPath, stepsPerYear);
    double cpiPV = calculatePresentValue(cpiFlows, cpiCount, discountRate);

    // Swap PV is difference between CPI bond and fixed bond
    return cpiPV - fixedPV;
}

int main() {
    // Bond parameters
    double faceValue = 1000.0;
    double couponRate = 0.05;
    int maturity = 10;
    double discountRate = 0.02;

    // CPI parameters
    double cpiInitial = 100.0;
    double cpiDrift = 0.02;
    double cpiVolatility = 0.03;
    int stepsPerYear = 252; // Daily simulation

    // Calculate swap value
    double swapValue = calculateSwapPV(faceValue, couponRate, maturity, discountRate,
                                       cpiInitial, cpiDrift, cpiVolatility, stepsPerYear);

    // Output result
    cout << fixed << setprecision(2);
    cout << "CPI to Fixed Swap Present Value: " << swapValue << endl;

    return 0;
}
