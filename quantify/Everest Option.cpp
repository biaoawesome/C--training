#include <iostream>
#include <random>
#include <cmath>

// Everest Option (also known as Peak Option) pricing using Monte Carlo simulation
class EverestOption {
public:
    // Constructor to initialize option parameters
    EverestOption(double spot, double strike, double maturity,
                  double volatility, double riskFreeRate)
        : spot_(spot), strike_(strike), maturity_(maturity),
          volatility_(volatility), riskFreeRate_(riskFreeRate) {}

    // Calculate the price of the Everest option using Monte Carlo simulation
    double calculateOptionPrice(int numSimulations) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> dist(0.0, 1.0);

        double optionPrice = 0.0;

        for (int i = 0; i < numSimulations; ++i) {
            double currentPrice = spot_;
            double maxPrice = spot_;
            double dt = maturity_ / 252.0; // Time step per trading day

            // Simulate the asset path over 252 days
            for (int t = 0; t < 252; ++t) {
                double shock = dist(gen); // Standard normal random shock
                currentPrice *= exp((riskFreeRate_ - 0.5 * volatility_ * volatility_) * dt
                                   + volatility_ * sqrt(dt) * shock);
                maxPrice = (currentPrice > maxPrice) ? currentPrice : maxPrice;
            }

            // Compute payoff: max(maxPrice - strike, 0)
            double payoff = (maxPrice > strike_) ? (maxPrice - strike_) : 0.0;
            optionPrice += payoff;
        }

        // Average and discount back to present value
        optionPrice /= numSimulations;
        optionPrice *= exp(-riskFreeRate_ * maturity_);
        return optionPrice;
    }

private:
    double spot_;           // Initial underlying price
    double strike_;         // Strike price
    double maturity_;       // Time to maturity in years
    double volatility_;     // Volatility of the underlying
    double riskFreeRate_;   // Risk-free interest rate
};

int main() {
    // Set up option parameters
    double spotPrice = 100.0;      // Spot price
    double strikePrice = 120.0;    // Strike price
    double maturity = 1.0;         // Maturity in years
    double volatility = 0.2;       // Volatility (20%)
    double riskFreeRate = 0.05;    // Risk-free rate (5%)

    // Create Everest option object
    EverestOption option(spotPrice, strikePrice, maturity, volatility, riskFreeRate);

    // Run Monte Carlo simulation
    int numSimulations = 10000;    // Number of simulations
    double price = option.calculateOptionPrice(numSimulations);

    // Output result
    std::cout.precision(6);
    std::cout << "Everest Option Price: " << price << std::endl;

    return 0;
}
