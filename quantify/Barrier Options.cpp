#include <iostream>
#include <cmath>

// Base class for financial options
class Option {
public:
    // Pure virtual function for pricing the option
    virtual double price() const = 0;

protected:
    // Common parameters for all options
    double strike_;         // Strike price
    double spot_;           // Current underlying asset price
    double volatility_;     // Volatility of the underlying asset
    double riskFreeRate_;   // Risk-free interest rate
    double maturity_;       // Time to maturity in years

    // Constructor
    Option(double strike, double spot, double volatility, double riskFreeRate, double maturity)
        : strike_(strike), spot_(spot), volatility_(volatility),
          riskFreeRate_(riskFreeRate), maturity_(maturity) {}
};

// Down-and-Out Barrier Option Pricing using Black-Scholes model
class DownAndOutOption : public Option {
public:
    DownAndOutOption(double strike, double spot, double volatility,
                     double riskFreeRate, double maturity, double barrier)
        : Option(strike, spot, volatility, riskFreeRate, maturity), barrier_(barrier) {}

    // Price the option using simplified Black-Scholes formula
    double price() const override {
        double d1 = (log(spot_ / strike_) + (riskFreeRate_ + 0.5 * volatility_ * volatility_) * maturity_)
                    / (volatility_ * sqrt(maturity_));
        double d2 = d1 - volatility_ * sqrt(maturity_);

        double Nd1 = 0.5 * (1.0 + erf(d1 / sqrt(2.0)));
        double Nd2 = 0.5 * (1.0 + erf(d2 / sqrt(2.0)));

        return spot_ * Nd1 - strike_ * exp(-riskFreeRate_ * maturity_) * Nd2;
    }

private:
    double barrier_;  // Barrier level below which the option becomes invalid
};

// Out-and-Out Barrier Option Pricing
class OutAndOutOption : public Option {
public:
    OutAndOutOption(double strike, double spot, double volatility,
                    double riskFreeRate, double maturity, double barrier)
        : Option(strike, spot, volatility, riskFreeRate, maturity), barrier_(barrier) {}

    // Price the option using simplified Black-Scholes formula
    double price() const override {
        double d1 = (log(spot_ / strike_) + (riskFreeRate_ + 0.5 * volatility_ * volatility_) * maturity_)
                    / (volatility_ * sqrt(maturity_));
        double d2 = d1 - volatility_ * sqrt(maturity_);

        double Nd1 = 0.5 * (1.0 + erf(d1 / sqrt(2.0)));
        double Nd2 = 0.5 * (1.0 + erf(d2 / sqrt(2.0)));

        return strike_ * exp(-riskFreeRate_ * maturity_) * Nd2 - spot_ * Nd1;
    }

private:
    double barrier_;  // Barrier level beyond which the option becomes invalid
};

// Static replication strategy class
class ReplicationStrategy {
public:
    ReplicationStrategy(double strike, double spot, double maturity)
        : strike_(strike), spot_(spot), maturity_(maturity) {}

    // Replicate the option with a simple static portfolio
    double replicateOption(const Option& option) const {
        double optionPrice = option.price();
        return optionPrice / spot_;  // Simple ratio-based replication
    }

private:
    double strike_;    // Strike price
    double spot_;      // Current underlying price
    double maturity_;  // Maturity time in years
};

// Test case: pricing and replication of two types of barrier options
void testReplication() {
    // Input parameters
    double strike = 100.0;            // Strike price
    double spot = 95.0;               // Spot price
    double volatility = 0.2;          // Volatility
    double riskFreeRate = 0.05;       // Risk-free rate
    double maturity = 1.0;            // Maturity in years
    double barrier = 90.0;            // Barrier level

    // Create options
    DownAndOutOption downAndOutOption(strike, spot, volatility, riskFreeRate, maturity, barrier);
    OutAndOutOption outAndOutOption(strike, spot, volatility, riskFreeRate, maturity, barrier);

    // Calculate and print prices
    std::cout.precision(6);
    std::cout << "Down-and-Out Option Price: " << downAndOutOption.price() << "\n";
    std::cout << "Out-and-Out Option Price: " << outAndOutOption.price() << "\n";

    // Create replication strategy
    ReplicationStrategy replication(strike, spot, maturity);

    // Replicate options
    double downAndOutReplication = replication.replicateOption(downAndOutOption);
    double outAndOutReplication = replication.replicateOption(outAndOutOption);

    // Output replication results
    std::cout << "Static Replication for Down-and-Out Option: " << downAndOutReplication << "\n";
    std::cout << "Static Replication for Out-and-Out Option: " << outAndOutReplication << "\n";
}

int main() {
    // Run the replication test
    testReplication();

    return 0;
}
