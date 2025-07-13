#include <iostream>
#include <cmath>
#include <random>

using namespace std;

// Maximum allowed number of Libor rates and paths
const size_t MAX_LIBORS = 10;
const size_t MAX_PATHS = 1000;    // Reduced for demo purposes
const size_t MAX_STEPS = 252;

// Structure to hold Libor Market Model parameters
struct LMMParams {
    double mu[MAX_LIBORS];       // Drift terms
    double sigma[MAX_LIBORS];    // Volatility terms
    double L0[MAX_LIBORS];       // Initial Libor rates
    double dt;                   // Time step
    int numPaths;                // Number of simulation paths
    int numSteps;                // Number of time steps
};

// Libor Market Model class
class LiborMarketModel {
private:
    LMMParams params;

public:
    // Constructor: initialize model with given parameters
    LiborMarketModel(const LMMParams& p) : params(p) {}

    // Simulate Libor rate paths using Euler-Maruyama method
    void simulatePaths(double*** paths) {
        int n = params.numSteps;
        int m = params.numPaths;
        int libors = sizeof(params.mu) / sizeof(params.mu[0]);

        random_device rd;
        mt19937 gen(rd());
        normal_distribution<> dis(0.0, 1.0);

        // Initialize all paths with initial Libor values
        for (int path = 0; path < m; ++path) {
            for (int i = 0; i < libors; ++i) {
                paths[path][i][0] = params.L0[i];
            }
        }

        // Simulate each time step for all paths
        for (int path = 0; path < m; ++path) {
            for (int t = 1; t <= n; ++t) {
                for (int i = 0; i < libors; ++i) {
                    double dW = dis(gen) * sqrt(params.dt); // Brownian increment
                    paths[path][i][t] = paths[path][i][t - 1] *
                                        (1 + params.mu[i] * params.dt + params.sigma[i] * dW);
                }
            }
        }
    }

    // Calculate swap price based on simulated paths (simple discounted cash flows)
    double swapPrice(double*** paths, double notional) {
        int T = params.numSteps;
        int m = params.numPaths;
        double price = 0.0;

        // Sum cash flows over all paths
        for (int path = 0; path < m; ++path) {
            double cashFlow = 0.0;
            for (int t = 1; t <= T; ++t) {
                cashFlow += paths[path][0][t] * notional * params.dt;
            }
            price += cashFlow;
        }

        return price / m; // Average over paths
    }
};

// Allocate 3D array on heap
double*** allocate3DArray(int paths, int libors, int steps) {
    double*** arr = new double**[paths];
    for (int i = 0; i < paths; ++i) {
        arr[i] = new double*[libors];
        for (int j = 0; j < libors; ++j) {
            arr[i][j] = new double[steps + 1]();
        }
    }
    return arr;
}

// Free 3D array
void free3DArray(double*** arr, int paths, int libors) {
    for (int i = 0; i < paths; ++i) {
        for (int j = 0; j < libors; ++j) {
            delete[] arr[i][j];
        }
        delete[] arr[i];
    }
    delete[] arr;
}

// Main function
int main() {
    // Define model parameters
    LMMParams params = {
        {0.02, 0.03},          // drifts mu
        {0.01, 0.02},          // volatilities sigma
        {0.03, 0.04},          // initial Libor rates L0
        1.0 / 252.0,           // daily time step
        1000,                  // number of Monte Carlo paths
        252                    // number of time steps (one year)
    };

    // Allocate memory on heap
    double*** paths = allocate3DArray(params.numPaths, MAX_LIBORS, params.numSteps);

    // Create Libor market model object
    LiborMarketModel lmm(params);

    // Simulate Libor rate paths
    lmm.simulatePaths(paths);

    // Compute interest rate swap price
    double notional = 1000000.0; // Notional amount
    double price = lmm.swapPrice(paths, notional);

    // Output result
    cout << "Simulated swap price: " << price << endl;

    // Free allocated memory
    free3DArray(paths, params.numPaths, MAX_LIBORS);

    return 0;
}
