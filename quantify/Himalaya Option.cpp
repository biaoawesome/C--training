#include <iostream>
#include <cmath>
#include <random>

#define MAX_STRIKES 100 

class HimalayaOption {
public:
    // Constructor
    HimalayaOption(double spot, const double strikes[], int strikeCount, double maturity,
                   double volatility, double riskFreeRate, int steps, int simulations)
        : S0(spot), T(maturity), sigma(volatility), r(riskFreeRate), N(steps), M(simulations) {
        K_count = strikeCount;
        for (int i = 0; i < strikeCount && i < MAX_STRIKES; ++i) {
            K[i] = strikes[i];
        }
    }

    // Calculate option price using Monte Carlo simulation
    double calculatePrice() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> dis(0.0, 1.0);

        double dt = T / N;                  // Time step size
        double discountFactor = exp(-r * T); // Discount factor

        double optionPrice = 0.0;

        // Monte Carlo simulations
        for (int i = 0; i < M; ++i) {
            double ST = S0;     // Current asset price
            bool touched = false; // Whether the barrier is hit

            // Simulate path
            for (int j = 0; j < N; ++j) {
                double Z = dis(gen); // Standard normal random number
                ST *= exp((r - 0.5 * sigma * sigma) * dt + sigma * sqrt(dt) * Z);

                // Check if any of the barriers is hit
                if (!touched) {
                    for (int k = 0; k < K_count; ++k) {
                        if (ST >= K[k]) {
                            touched = true;
                            break;
                        }
                    }
                }
            }

            // If barrier is hit, payoff is 1
            if (touched) {
                optionPrice += 1.0;
            }
        }

        // Return discounted average payoff
        return (optionPrice / M) * discountFactor;
    }

private:
    double S0;             // Initial underlying asset price
    double K[MAX_STRIKES]; // Array to store strike levels
    int K_count;           // Number of strike levels
    double T;              // Time to maturity (in years)
    double sigma;          // Volatility
    double r;              // Risk-free interest rate
    int N;                 // Number of time steps
    int M;                 // Number of Monte Carlo simulations
};

int main() {
    // Option parameters
    double spotPrice = 100.0;                          // Initial underlying price
    double strikePrices[] = {110.0, 120.0, 130.0};      // Strike levels
    int strikeCount = sizeof(strikePrices) / sizeof(strikePrices[0]); // Count strikes
    double maturity = 1.0;                               // Maturity in years
    double volatility = 0.2;                             // Volatility (20%)
    double riskFreeRate = 0.05;                          // Risk-free rate (5%)
    int steps = 100;                                     // Number of time steps
    int simulations = 1000000;                           // Number of Monte Carlo paths

    // Create Himalaya option object
    HimalayaOption option(spotPrice, strikePrices, strikeCount, maturity, volatility, riskFreeRate, steps, simulations);

    // Calculate and print option price
    double price = option.calculatePrice();
    std::cout << "Himalaya Option Price: " << price << std::endl;

    return 0;
}
