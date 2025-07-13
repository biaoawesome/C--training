#include <iostream>
#include <cmath>

#define MAX_RATES 100  // Maximum number of interest rates supported

// Helper class to calculate the basis swap rate
class BasisSwapRateHelper {
public:
    // Constructor: takes notional, arrays of fixed and floating rates, and their count
    BasisSwapRateHelper(double notional, const double* fixedRates, const double* floatingRates, int count)
        : notional_(notional), count_(count) {
        // Copy fixed rates into internal array
        for (int i = 0; i < count_; ++i) {
            fixedRates_[i] = fixedRates[i];
            floatingRates_[i] = floatingRates[i];
        }
    }

    // Calculate the basis swap rate
    double calculateBasisSwapRate() {
        double fixedSum = 0.0;
        double floatingSum = 0.0;

        // Sum up all fixed and floating rate values
        for (int i = 0; i < count_; ++i) {
            fixedSum += fixedRates_[i];
            floatingSum += floatingRates_[i];
        }

        // Compute the basis swap rate
        return (fixedSum - floatingSum) / notional_;
    }

private:
    double notional_;                    // Notional amount
    double fixedRates_[MAX_RATES];      // Array of fixed interest rates
    double floatingRates_[MAX_RATES];    // Array of floating interest rates
    int count_;                          // Number of rate entries
};

// Test function for the BasisSwapRateHelper class
void testBasisSwapRateHelper() {
    // Simulated market data
    double notional = 1000000;  // Notional amount: 1 million

    // Example fixed and floating rates
    double fixedRates[] = {0.02, 0.025, 0.03};
    double floatingRates[] = {0.015, 0.02, 0.022};
    int count = sizeof(fixedRates) / sizeof(fixedRates[0]);  // Get array size

    // Create helper object
    BasisSwapRateHelper helper(notional, fixedRates, floatingRates, count);

    // Calculate basis swap rate
    double basisSwapRate = helper.calculateBasisSwapRate();

    // Output result
    std::cout.precision(4);
    std::cout << "Basis Swap Rate: " << basisSwapRate * 100 << "%" << std::endl;
}

int main() {
    // Run the basis swap rate calculation test
    testBasisSwapRateHelper();

    return 0;
}
