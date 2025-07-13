#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>

using namespace std;

// Random number generator class
class RandomGenerator {
private:
    mutable mt19937 gen; // Mersenne Twister RNG engine

public:
    // Constructor initializes the random engine
    RandomGenerator() : gen(random_device{}()) {}

    // Generate standard normal distributed value (mean=0, stddev=1)
    double generateNormal() const {
        normal_distribution<> dist(0.0, 1.0);
        return dist(gen);
    }

    // Generate uniformly distributed value in [min, max]
    double generateUniform(double min, double max) const {
        uniform_real_distribution<> dist(min, max);
        return dist(gen);
    }
};

// Interest Rate Swap Class
class InterestRateSwap {
private:
    double fixedRate;         // Fixed interest rate
    double notional;          // Notional amount
    int maturity;             // Maturity in years
    double floatingRate;      // Floating interest rate (e.g., LIBOR)
    double counterpartyRisk;  // Credit risk adjustment (credit spread)
    double discountRate;      // Risk-free discount rate

public:
    // Constructor
    InterestRateSwap(double fixedRate, double notional, double maturity,
                     double floatingRate, double counterpartyRisk, double discountRate)
        : fixedRate(fixedRate), notional(notional), maturity(static_cast<int>(maturity)),
          floatingRate(floatingRate), counterpartyRisk(counterpartyRisk),
          discountRate(discountRate) {}

    // Calculate present value of fixed leg payments
    double calculateFixedLegValue() const {
        double cashFlow = fixedRate * notional;
        double fixedLegValue = 0.0;

        for (int t = 1; t <= maturity; ++t) {
            fixedLegValue += cashFlow / pow(1 + discountRate, t);
        }

        return fixedLegValue;
    }

    // Calculate present value of floating leg payments
    double calculateFloatingLegValue() const {
        double floatingLegValue = 0.0;

        for (int t = 1; t <= maturity; ++t) {
            floatingLegValue += floatingRate * notional / pow(1 + discountRate, t);
        }

        return floatingLegValue;
    }

    // Adjust present value for counterparty credit risk
    double adjustForCounterpartyRisk(double legValue) const {
        return legValue * (1.0 - counterpartyRisk);
    }

    // Calculate net present value of the swap
    double calculateNetPresentValue() const {
        double fixedLegValue = calculateFixedLegValue();
        double floatingLegValue = calculateFloatingLegValue();

        fixedLegValue = adjustForCounterpartyRisk(fixedLegValue);
        floatingLegValue = adjustForCounterpartyRisk(floatingLegValue);

        return fixedLegValue - floatingLegValue;
    }
};

int main() {
    // Define parameters
    double fixedRate = 0.03;       // Fixed rate: 3%
    double notional = 1000000.0;   // Notional: $1,000,000
    double maturity = 5.0;         // Maturity: 5 years
    double floatingRate = 0.025;   // Floating rate: 2.5% (LIBOR)
    double counterpartyRisk = 0.02;// Counterparty risk: 2%
    double discountRate = 0.015;   // Discount rate: 1.5%

    // Create an interest rate swap object
    InterestRateSwap swap(fixedRate, notional, maturity, floatingRate, counterpartyRisk, discountRate);

    // Compute Net Present Value (NPV)
    double swapValue = swap.calculateNetPresentValue();

    // Output result with two decimal places
    cout << "Net Present Value of the Interest Rate Swap: "
         << fixed << setprecision(2) << swapValue << endl;

    return 0;
}
