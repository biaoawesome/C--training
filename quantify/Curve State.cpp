#include <iostream>
#include <cmath>
#include <iomanip>

#define MAX_CURVE_POINTS 100  // Maximum number of maturity points in the curve

// Class representing the state of an interest rate curve
class CurveState {
public:
    // Constructor: Initialize with maturity and rate arrays
    CurveState(const double maturities[], const double rates[], int size)
        : size(size) {
        for (int i = 0; i < size; ++i) {
            this->maturities[i] = maturities[i];
            this->rates[i] = rates[i];
        }
    }

    // Get the interest rate for a specific maturity
    double getRate(double maturity) const {
        for (int i = 0; i < size; ++i) {
            if (maturities[i] == maturity) {
                return rates[i];
            }
        }
        std::cerr << "Maturity not found in curve." << std::endl;
        return 0.0;
    }

    // Print the current curve state
    void printCurve() const {
        std::cout << "Curve State (Maturity, Rate):" << std::endl;
        for (int i = 0; i < size; ++i) {
            std::cout << "(" << maturities[i] << " years, " << std::fixed << std::setprecision(2) << rates[i] << "%)" << std::endl;
        }
    }

    // Update the curve to simulate market change
    void updateCurve(double shiftFactor) {
        for (int i = 0; i < size; ++i) {
            rates[i] += shiftFactor * std::sqrt(maturities[i]);  // Simulate market volatility
            if (rates[i] < 0) rates[i] = 0;  // Ensure non-negative rates
        }
    }

private:
    double maturities[MAX_CURVE_POINTS];  // Maturity points in years
    double rates[MAX_CURVE_POINTS];       // Corresponding interest rates (%)
    int size;                             // Number of points in the curve
};

// Function to simulate market behavior and test CurveState class
void simulateMarket() {
    // Initial curve data (assumed market has 5 different maturities)
    const int numPoints = 5;
    double maturities[numPoints] = {1.0, 2.0, 3.0, 5.0, 10.0};
    double rates[numPoints] = {2.0, 2.5, 3.0, 3.5, 4.0};  // Initial interest rates (%)

    // Create CurveState object
    CurveState curveState(maturities, rates, numPoints);

    // Print initial curve
    std::cout << "Initial Curve State:" << std::endl;
    curveState.printCurve();

    // Simulate market movement: increase rates by 1%
    double shiftFactor = 0.01;  // 1% upward shift
    curveState.updateCurve(shiftFactor);

    // Print updated curve after simulated market change
    std::cout << "\nUpdated Curve State after market change:" << std::endl;
    curveState.printCurve();
}

// Test function to run the interest rate curve simulation
void testCurveState() {
    simulateMarket();  // Run market simulation and curve output
}

// Main entry point
int main() {
    // Execute the test
    testCurveState();

    return 0;
}
