#include <iostream>
#include <cmath>
#include <random>

#define MAX_DIMENSIONS 100  // Maximum allowed dimensions for integration

// Define a multidimensional function to integrate
double integrand(const double* x, int dimensions) {
    // Example: f(x1, x2, ..., xn) = x1^2 + x2^2 + ... + xn^2
    double sum = 0.0;
    for (int i = 0; i < dimensions; ++i) {
        sum += x[i] * x[i];
    }
    return sum;
}

// Multidimensional integral class using Monte Carlo method
class MultidimIntegral {
public:
    // Constructor: specify dimensions, integration bounds and number of samples
    MultidimIntegral(int dimensions, double lower, double upper, int samples)
        : dimensions_(dimensions), lower_(lower), upper_(upper), samples_(samples) {}

    // Use Monte Carlo method to compute the integral
    double monteCarloIntegrate() {
        double sum = 0.0;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(lower_, upper_);

        // Generate random points and evaluate the integrand
        for (int i = 0; i < samples_; ++i) {
            double point[MAX_DIMENSIONS];

            for (int j = 0; j < dimensions_; ++j) {
                point[j] = dis(gen);  // Random point in [lower_, upper_]
            }

            sum += integrand(point, dimensions_);
        }

        // Compute the volume of the hypercube
        double volume = 1.0;
        for (int i = 0; i < dimensions_; ++i) {
            volume *= (upper_ - lower_);
        }

        // Return average value multiplied by volume
        return sum / samples_ * volume;
    }

private:
    int dimensions_;   // Number of dimensions
    double lower_;     // Lower bound of integration interval
    double upper_;     // Upper bound of integration interval
    int samples_;      // Number of Monte Carlo samples
};

// Test case for multidimensional integration
void testMultidimIntegral() {
    // Set up parameters: 2D integral over [0,1]^2 with 10,000 samples
    MultidimIntegral integral(2, 0.0, 1.0, 10000);

    // Perform integration
    double result = integral.monteCarloIntegrate();

    // Output the result
    std::cout.precision(6);
    std::cout << "The result of the multidimensional integral is: " << result << std::endl;
}

int main() {
    // Run the integration test
    testMultidimIntegral();
    return 0;
}
