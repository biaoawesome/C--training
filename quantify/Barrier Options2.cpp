#include <iostream>
#include <cmath>
#include <iomanip>

// Black-Scholes model to calculate the price of a European option
double blackScholesPrice(double S, double K, double T, double r, double sigma, char optionType) {
    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);

    if (optionType == 'C') {
        return S * 0.5 * (1 + erf(d1 / sqrt(2))) - K * exp(-r * T) * 0.5 * (1 + erf(d2 / sqrt(2)));
    } else if (optionType == 'P') {
        return K * exp(-r * T) * 0.5 * (1 + erf(-d2 / sqrt(2))) - S * 0.5 * (1 + erf(-d1 / sqrt(2)));
    }
    return 0.0;
}

// Static replication for Down-and-Out barrier options
double replicateDownBarrier(double S, double K, double H, double T, double r, double sigma, char optionType) {
    // Buy a standard option
    double standardOptionPrice = blackScholesPrice(S, K, T, r, sigma, optionType);
    // Sell a knock-out option at barrier level H
    double knockOutOptionPrice = blackScholesPrice(S, H, T, r, sigma, optionType);

    // Replication strategy price
    return standardOptionPrice - knockOutOptionPrice;
}

// Static replication for Out barrier options (similar structure)
double replicateOutBarrier(double S, double K, double H, double T, double r, double sigma, char optionType) {
    // Buy a standard option
    double standardOptionPrice = blackScholesPrice(S, K, T, r, sigma, optionType);
    // Sell a knock-out option at barrier level H
    double knockOutOptionPrice = blackScholesPrice(S, H, T, r, sigma, optionType);

    // Replication strategy price
    return standardOptionPrice - knockOutOptionPrice;
}

// Test case
int main() {
    // Parameters
    double S = 100.0;       // Current asset price
    double K = 100.0;       // Strike price
    double H = 90.0;        // Barrier level
    double T = 1.0;         // Time to maturity
    double r = 0.05;        // Risk-free interest rate
    double sigma = 0.2;     // Volatility

    // Calculate prices for down barrier options
    double downBarrierCallPrice = replicateDownBarrier(S, K, H, T, r, sigma, 'C');
    double downBarrierPutPrice = replicateDownBarrier(S, K, H, T, r, sigma, 'P');

    // Calculate prices for out barrier options
    double outBarrierCallPrice = replicateOutBarrier(S, K, H, T, r, sigma, 'C');
    double outBarrierPutPrice = replicateOutBarrier(S, K, H, T, r, sigma, 'P');

    // Output results with fixed precision
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Down Barrier Call Option Price: " << downBarrierCallPrice << std::endl;
    std::cout << "Down Barrier Put Option Price: " << downBarrierPutPrice << std::endl;
    std::cout << "Out Barrier Call Option Price: " << outBarrierCallPrice << std::endl;
    std::cout << "Out Barrier Put Option Price: " << outBarrierPutPrice << std::endl;

    return 0;
}
