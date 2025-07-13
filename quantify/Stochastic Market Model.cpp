#include <iostream>
#include <cmath>
#include <random>

using namespace std;

// Maximum allowed number of time steps (N + 1)
const int MAX_PATH_POINTS = 253; // e.g., 252 steps + initial value

// Class for Simulating Market using Geometric Brownian Motion (GBM)
class SMM_Market {
private:
    double S0;   // Initial asset price
    double mu;   // Drift (expected return)
    double sigma; // Volatility
    double T;    // Time horizon (in years)
    int N;       // Number of time steps
    int M;       // Number of simulation paths

    random_device rd;
    mt19937 gen;                 // Random number generator
    normal_distribution<> d;     // Standard normal distribution

public:
    // Constructor to initialize market parameters
    SMM_Market(double S0, double mu, double sigma, double T, int N, int M)
        : S0(S0), mu(mu), sigma(sigma), T(T), N(N), M(M), gen(rd()), d(0.0, 1.0) {}

    // Simulate a single path of asset prices using GBM
    void simulatePath(double outPath[MAX_PATH_POINTS]) {
        double dt = T / N;
        outPath[0] = S0;

        for (int i = 1; i <= N; ++i) {
            double dW = d(gen) * sqrt(dt);  // Brownian motion increment
            outPath[i] = outPath[i - 1] * exp((mu - 0.5 * sigma * sigma) * dt + sigma * dW);
        }
    }

    // Perform Monte Carlo simulation to estimate option price
    double monteCarloOptionPrice(int optionType, double strikePrice, int numPaths = 10000) {
        double sumPayoff = 0.0;
        double path[MAX_PATH_POINTS];

        for (int i = 0; i < numPaths; ++i) {
            simulatePath(path);
            double finalPrice = path[N];  // Final price in this path

            double payoff = 0.0;
            if (optionType == 1) {  // European Call Option
                payoff = max(0.0, finalPrice - strikePrice);
            } else if (optionType == 2) {  // European Put Option
                payoff = max(0.0, strikePrice - finalPrice);
            }

            sumPayoff += payoff;
        }

        double optionPrice = (sumPayoff / numPaths) * exp(-mu * T);
        return optionPrice;
    }
};
int main() {
    // Define model parameters
    double S0 = 100.0;    // Initial stock price
    double mu = 0.05;     // Expected return
    double sigma = 0.2;   // Volatility
    double T = 1.0;       // Time to maturity
    int N = 252;          // Number of time steps
    int M = 10000;        // Number of simulation paths

    // Create market object
    SMM_Market market(S0, mu, sigma, T, N, M);

    // Calculate European call option price with strike price = 100
    double strikePrice = 100.0;
    double callPrice = market.monteCarloOptionPrice(1, strikePrice, M);
    cout << "European Call Option Price: " << callPrice << endl;

    // Calculate European put option price with strike price = 100
    double putPrice = market.monteCarloOptionPrice(2, strikePrice, M);
    cout << "European Put Option Price: " << putPrice << endl;

    return 0;
}
