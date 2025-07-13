#include <iostream>
#include <functional>
#include <random>
#include <chrono>

const size_t MAX_DIM = 10; // Maximum allowed dimension for static arrays

// Random number generator class
class RandomGenerator {
public:
    // Constructor initializes the random number generator and uniform distribution
    RandomGenerator(int seed = 42) : gen(seed), dist(0.0, 1.0) {}

    // Generate a uniform random point within given bounds
    void generateUniformRandomPoint(const double lowerBounds[], const double upperBounds[], double pointOut[], size_t dim) {
        for (size_t i = 0; i < dim; ++i) {
            // Generate random number in [lowerBounds[i], upperBounds[i]]
            pointOut[i] = lowerBounds[i] + dist(gen) * (upperBounds[i] - lowerBounds[i]);
        }
    }

private:
    std::mt19937 gen; // Mersenne Twister RNG
    std::uniform_real_distribution<double> dist; // Uniform distribution
};

// Monte Carlo integrator class
class MonteCarloIntegrator {
public:
    // Constructor initializes the random number generator
    MonteCarloIntegrator(int seed = 42) : randomGenerator(seed) {}

    // Monte Carlo method to compute multi-dimensional integral
    double integrate(const std::function<double(const double*, size_t)>& func,
                     const double lowerBounds[],
                     const double upperBounds[],
                     size_t dim,
                     int numSamples) {
        double sum = 0.0;
        double point[MAX_DIM]; // Static array to hold the random point

        for (int i = 0; i < numSamples; ++i) {
            // Generate random point
            randomGenerator.generateUniformRandomPoint(lowerBounds, upperBounds, point, dim);
            // Evaluate function and accumulate
            sum += func(point, dim);
        }

        // Compute volume of integration region
        double volume = 1.0;
        for (size_t i = 0; i < dim; ++i) {
            volume *= (upperBounds[i] - lowerBounds[i]);
        }

        // Return integral estimate
        return volume * sum / numSamples;
    }

private:
    RandomGenerator randomGenerator;
};

// Multi-dimensional integral main class
class MultidimIntegral {
public:
    // Constructor initializes random seed
    MultidimIntegral(int seed = 42) : seed(seed) {}

    // Interface to compute multi-dimensional integral
    double computeIntegral(const std::function<double(const double*, size_t)>& func,
                           const double lowerBounds[],
                           const double upperBounds[],
                           size_t dim,
                           int numSamples) {
        MonteCarloIntegrator integrator(seed);
        return integrator.integrate(func, lowerBounds, upperBounds, dim, numSamples);
    }

private:
    int seed; // Random seed
};

// Test case
int main() {
    const size_t dim = 2; // Dimension of integral
    double lowerBounds[MAX_DIM] = {0.0, 0.0}; // Lower bounds
    double upperBounds[MAX_DIM] = {1.0, 1.0}; // Upper bounds

    // Define integrand function: f(x1, x2, ..., xd) = x1 + x2 + ... + xd
    auto func = [](const double* x, size_t dim) {
        double sum = 0.0;
        for (size_t i = 0; i < dim; ++i) {
            sum += x[i];
        }
        return sum;
    };

    int numSamples = 1000000; // Number of samples
    MultidimIntegral integrator; // Create integrator object

    // Record start time
    auto start = std::chrono::high_resolution_clock::now();

    // Compute integral
    double result = integrator.computeIntegral(func, lowerBounds, upperBounds, dim, numSamples);

    // Record end time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Output results
    std::cout << "Computed integral: " << result << std::endl;
    std::cout << "Time elapsed: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
