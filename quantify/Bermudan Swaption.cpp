#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

// Configuration: Maximum steps in the binomial tree
#define MAX_STEPS 1000  // Max number of time steps allowed

// Swap Parameters Structure
struct SwapParams {
    double notional;     // Notional amount
    double fixedRate;    // Fixed interest rate
    int maturity;        // Maturity in years
    int frequency;       // Payment frequency per year (e.g., 2 = semi-annual)
};

// Bermudan Option Parameters Structure
struct BermudanOptionParams {
    double strikePrice;          // Exercise price
    int exerciseDates[MAX_STEPS];  // Array to store exercise years
    int numExerciseDates;        // Number of exercise dates
};

// Market Parameters Structure
struct MarketParams {
    double initialRate;   // Initial short rate
    double volatility;    // Volatility of interest rates
    int steps;            // Number of steps in binomial tree
    double discountRate;  // Discount rate for risk-neutral probability
};

// Build a binomial interest rate tree using multiplicative up/down factors
void buildRateTree(const MarketParams& marketParams, double rateTree[][MAX_STEPS + 1]) {
    double dt = 1.0 / marketParams.steps;
    double u = exp(marketParams.volatility * sqrt(dt));
    double d = 1.0 / u;

    for (int i = 0; i <= marketParams.steps; ++i) {
        for (int j = 0; j <= i; ++j) {
            rateTree[i][j] = marketParams.initialRate * pow(u, j) * pow(d, i - j);
        }
    }
}

// Calculate the present value of swap cashflows at a given rate
double calculateSwapValue(double rate, const SwapParams& swapParams, int remainingYears) {
    double dt = 1.0 / swapParams.frequency;
    double fixedPayment = swapParams.notional * swapParams.fixedRate * dt;
    double swapValue = 0.0;

    int totalPayments = remainingYears * swapParams.frequency;
    for (int i = 1; i <= totalPayments; ++i) {
        swapValue += fixedPayment / pow(1 + rate * dt, i);
    }

    return swapValue;
}

// Price a Bermudan Swaption using binomial tree
double priceBermudanSwaption(
    const SwapParams& swapParams,
    const BermudanOptionParams& optionParams,
    const MarketParams& marketParams
) {
    double rateTree[MAX_STEPS + 1][MAX_STEPS + 1] = {0};
    double priceTree[MAX_STEPS + 1][MAX_STEPS + 1] = {0};

    buildRateTree(marketParams, rateTree);

    double dt = 1.0 / marketParams.steps;
    double p = (exp(marketParams.discountRate * dt) - rateTree[1][1]) /
               (rateTree[1][0] - rateTree[1][1]);
    double q = 1.0 - p;

    // Terminal payoff at final nodes
    for (int j = 0; j <= marketParams.steps; ++j) {
        int remainingYears = std::max(0, swapParams.maturity - marketParams.steps);
        priceTree[marketParams.steps][j] = std::max(0.0, calculateSwapValue(rateTree[marketParams.steps][j], swapParams, remainingYears));
    }

    // Backward induction
    for (int i = marketParams.steps - 1; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            int currentYear = static_cast<int>(round(i * swapParams.maturity / marketParams.steps));

            bool isExerciseDate = false;
            for (int k = 0; k < optionParams.numExerciseDates; ++k) {
                if (optionParams.exerciseDates[k] == currentYear) {
                    isExerciseDate = true;
                    break;
                }
            }

            double continuation = (p * priceTree[i + 1][j + 1] + q * priceTree[i + 1][j]) / (1 + rateTree[i][j] * dt);
            double immediateExercise = 0.0;

            if (isExerciseDate) {
                int remainingYears = swapParams.maturity - currentYear;
                double swapValue = calculateSwapValue(rateTree[i][j], swapParams, remainingYears);
                immediateExercise = std::max(0.0, swapValue);
            }

            priceTree[i][j] = std::max(immediateExercise, continuation);
        }
    }

    return priceTree[0][0];
}

// Main function
int main() {
    // Define swap parameters
    SwapParams swapParams = {
        1000000.0,  // Notional: $1 million
        0.05,       // Fixed rate: 5%
        5,          // Maturity: 5 years
        2           // Semi-annual payments
    };

    // Define Bermudan option parameters
    BermudanOptionParams optionParams = {
        0.0,                  // Strike price: Not used here as intrinsic value from swap
        {1, 2, 3, 4},         // Exercise years
        4                     // Number of exercise dates
    };

    // Define market parameters
    MarketParams marketParams = {
        0.04,      // Initial interest rate: 4%
        0.02,      // Volatility: 2%
        100,       // Steps in binomial tree
        0.03       // Risk-free discount rate
    };

    // Compute Bermudan swaption price
    double swaptionPrice = priceBermudanSwaption(swapParams, optionParams, marketParams);

    // Output result
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Bermudan Swaption Price: $" << swaptionPrice << std::endl;

    return 0;
}
