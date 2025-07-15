#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Structure to represent a Caplet
struct Caplet {
    double strike;      // Strike rate
    double maturity;    // Time to maturity
    double rate;        // Current interest rate
    double volatility;  // Volatility
};

// Black-Scholes pricing formula for Caplet
double capletPrice(double strike, double maturity, double rate, double volatility) {
    double d1 = (log(rate / strike) + 0.5 * volatility * volatility * maturity) / (volatility * sqrt(maturity));
    double d2 = d1 - volatility * sqrt(maturity);

    // Cumulative distribution function of standard normal
    double N_d1 = 0.5 * (1.0 + erf(d1 / sqrt(2.0)));
    double N_d2 = 0.5 * (1.0 + erf(d2 / sqrt(2.0)));

    return exp(-rate * maturity) * (rate * N_d1 - strike * N_d2);
}

// Simulated volatility surface (volatility smile)
double getVolatility(double strike, double maturity) {
    return 0.2 + 0.1 * log(strike / 100.0) + 0.05 * sqrt(maturity); // Example volatility surface
}

// Calculate pricing error between model and market
double calculateModelError(const double strikes[], const double maturities[],
                            const double marketPrices[], const double modelParams[], int size) {
    double totalError = 0.0;
    double rate = 0.05; // Fixed reference rate

    for (int i = 0; i < size; ++i) {
        double strike = strikes[i];
        double maturity = maturities[i];
        double volatility = modelParams[i];

        double modelPrice = capletPrice(strike, maturity, rate, volatility);
        double diff = modelPrice - marketPrices[i];
        totalError += diff * diff;
    }

    return totalError;
}

// Gradient descent optimizer for volatility calibration
void calibrateVolatilities(const double strikes[], const double maturities[],
                            const double marketPrices[], double calibratedVolatilities[], int size) {
    const double tolerance = 1e-6;
    const int maxIterations = 1000;
    double learningRate = 0.01;

    // Initialize with simulated market volatilities
    for (int i = 0; i < size; ++i) {
        calibratedVolatilities[i] = getVolatility(strikes[i], maturities[i]);
    }

    for (int iter = 0; iter < maxIterations; ++iter) {
        double error = calculateModelError(strikes, maturities, marketPrices, calibratedVolatilities, size);
        double gradient[16] = {0}; // Max size 16

        // Numerical gradient (central difference)
        for (int i = 0; i < size; ++i) {
            double oldVol = calibratedVolatilities[i];
            calibratedVolatilities[i] = oldVol + 1e-5;
            double errPlus = calculateModelError(strikes, maturities, marketPrices, calibratedVolatilities, size);
            calibratedVolatilities[i] = oldVol - 1e-5;
            double errMinus = calculateModelError(strikes, maturities, marketPrices, calibratedVolatilities, size);

            gradient[i] = (errPlus - errMinus) / (2e-5);
            calibratedVolatilities[i] = oldVol;
        }

        // Update parameters
        double newParams[16];
        for (int i = 0; i < size; ++i) {
            newParams[i] = calibratedVolatilities[i] - learningRate * gradient[i];
        }

        // Check convergence
        double newError = calculateModelError(strikes, maturities, marketPrices, newParams, size);
        if (fabs(error - newError) < tolerance) {
            break;
        }

        for (int i = 0; i < size; ++i) {
            calibratedVolatilities[i] = newParams[i];
        }
    }
}

int main() {
    const int numCaplets = 4;

    // Caplet data
    double strikes[numCaplets] = {95, 100, 105, 110};
    double maturities[numCaplets] = {1, 2, 3, 5};
    double marketPrices[numCaplets] = {2.5, 2.0, 1.8, 1.5};
    double calibratedVolatilities[numCaplets];

    // Calibrate model
    calibrateVolatilities(strikes, maturities, marketPrices, calibratedVolatilities, numCaplets);

    // Output results
    cout << fixed << setprecision(4);
    cout << "Calibrated Volatilities:" << endl;
    for (int i = 0; i < numCaplets; ++i) {
        cout << "Strike: " << strikes[i]
             << ", Maturity: " << maturities[i]
             << ", Calibrated Volatility: " << calibratedVolatilities[i] << endl;
    }

    return 0;
}
