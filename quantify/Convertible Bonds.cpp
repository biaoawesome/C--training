#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>

using namespace std;

// Calculate cumulative distribution function (CDF) of standard normal distribution
double normCDF(double x) {
    return 0.5 * erfc(-x / sqrt(2.0));
}

// Calculate call option value using Black-Scholes model
double blackScholesCall(double S, double K, double T, double r, double sigma) {
    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);
    return S * normCDF(d1) - K * exp(-r * T) * normCDF(d2);
}

// Convertible Bond Class
class ConvertibleBond {
private:
    double faceValue;       // Face value of the bond
    double couponRate;      // Annual coupon rate
    double maturity;        // Maturity time in years
    double conversionPrice; // Conversion price per share
    double stockPrice;      // Current stock price
    double volatility;      // Volatility of underlying stock
    double riskFreeRate;    // Risk-free interest rate

public:
    // Constructor
    ConvertibleBond(double faceValue, double couponRate, double maturity,
                    double conversionPrice, double stockPrice,
                    double volatility, double riskFreeRate)
        : faceValue(faceValue), couponRate(couponRate), maturity(maturity),
          conversionPrice(conversionPrice), stockPrice(stockPrice),
          volatility(volatility), riskFreeRate(riskFreeRate) {}

    // Calculate present value of the bond component
    double calculateBondValue() const {
        double couponPayment = faceValue * couponRate;
        double bondValue = 0.0;
        for (int t = 1; t <= maturity; ++t) {
            bondValue += couponPayment / pow(1 + riskFreeRate, t);
        }
        bondValue += faceValue / pow(1 + riskFreeRate, maturity);
        return bondValue;
    }

    // Calculate value of the embedded call option using Black-Scholes
    double calculateOptionValue() const {
        double conversionRatio = faceValue / conversionPrice; // Number of shares per bond
        return blackScholesCall(stockPrice, conversionPrice, maturity, riskFreeRate, volatility) * conversionRatio;
    }

    // Perform Monte Carlo simulation to estimate convertible bond value
    double monteCarloSimulation(int numSimulations) const {
        random_device rd;
        mt19937 gen(rd());
        normal_distribution<> d(0, 1); // Standard normal distribution

        double totalValue = 0.0;
        for (int i = 0; i < numSimulations; ++i) {
            double simulatedStockPrice = stockPrice;
            for (int t = 0; t < static_cast<int>(maturity); ++t) {
                double dt = 1.0; // Assume annual time steps
                simulatedStockPrice *= exp((riskFreeRate - 0.5 * volatility * volatility) * dt +
                                           volatility * sqrt(dt) * d(gen));
            }

            double conversionRatio = faceValue / conversionPrice;
            double optionValue = max(0.0, simulatedStockPrice - conversionPrice) * conversionRatio;
            double bondValue = calculateBondValue();

            // Choose the higher of conversion value or straight bond value
            totalValue += max(optionValue, bondValue);
        }

        return totalValue / numSimulations; // Return average value
    }

    // Print calculated values of the convertible bond
    void printConvertibleBondValue(int numSimulations = 10000) {
        double bondValue = calculateBondValue();
        double optionValue = calculateOptionValue();
        double monteCarloValue = monteCarloSimulation(numSimulations);

        cout << "Convertible Bond Value (Bond + Option): " << fixed << setprecision(2) << bondValue + optionValue << endl;
        cout << "Monte Carlo Simulation Value: " << fixed << setprecision(2) << monteCarloValue << endl;
    }
};

int main() {
    // Define parameters for the convertible bond
    double faceValue = 1000.0;     // Face value
    double couponRate = 0.05;      // Coupon rate (5%)
    double maturity = 5.0;         // Time to maturity in years
    double conversionPrice = 50.0; // Conversion price per share
    double stockPrice = 55.0;      // Current stock price
    double volatility = 0.2;       // Annualized stock volatility (20%)
    double riskFreeRate = 0.03;    // Risk-free interest rate (3%)

    // Create convertible bond object
    ConvertibleBond convertibleBond(faceValue, couponRate, maturity,
                                    conversionPrice, stockPrice,
                                    volatility, riskFreeRate);

    // Output bond valuation results
    convertibleBond.printConvertibleBondValue();

    return 0;
}
