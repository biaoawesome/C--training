#include <iostream>
#include <cmath>

#define MAX_STEPS 1000  // 最大支持的时间步数

// Define a class for European Call Option pricing using Binomial Tree
class EuropeanOption {
public:
    // Constructor
    EuropeanOption(double spot, double strike, double maturity,
                   double volatility, double riskFreeRate, int steps)
        : S0(spot), K(strike), T(maturity), sigma(volatility),
          r(riskFreeRate), N(steps) {}

    // Calculate option price using binomial tree
    double calculatePrice() {
        double dt = T / N;
        double u = exp(sigma * sqrt(dt));
        double d = exp(-sigma * sqrt(dt));
        double p = (exp(r * dt) - d) / (u - d);

        // Initialize the price and option value arrays
        double priceTree[MAX_STEPS + 1][MAX_STEPS + 1] = {0.0};
        double optionTree[MAX_STEPS + 1][MAX_STEPS + 1] = {0.0};

        // Set terminal payoff: max(S_T - K, 0)
        for (int i = 0; i <= N; ++i) {
            double ST = S0 * pow(u, N - i) * pow(d, i);
            optionTree[i][N] = fmax(ST - K, 0.0);
            priceTree[i][N] = ST;
        }

        // Backward induction to compute option values at each node
        for (int j = N - 1; j >= 0; --j) {
            for (int i = 0; i <= j; ++i) {
                double ST = S0 * pow(u, j - i) * pow(d, i);
                priceTree[i][j] = ST;

                // Risk-neutral valuation
                optionTree[i][j] = (p * optionTree[i][j + 1] + (1 - p) * optionTree[i + 1][j + 1]) * exp(-r * dt);
            }
        }

        // Return current option price
        return optionTree[0][0];
    }

private:
    double S0;    // Initial underlying asset price
    double K;     // Strike price
    double T;     // Time to maturity (in years)
    double sigma; // Volatility
    double r;     // Risk-free interest rate
    int N;        // Number of time steps
};

int main() {
    // Option parameters
    double spotPrice = 100.0;       // Initial underlying price
    double strikePrice = 100.0;     // Strike price
    double maturity = 1.0;          // Maturity in years
    double volatility = 0.2;        // Volatility (20%)
    double riskFreeRate = 0.05;     // Risk-free rate (5%)
    int steps = 100;                // Number of time steps

    // Create European option object
    EuropeanOption option(spotPrice, strikePrice, maturity, volatility, riskFreeRate, steps);

    // Calculate and print option price
    double price = option.calculatePrice();
    std::cout << "European Option Price: " << price << std::endl;

    return 0;
}
