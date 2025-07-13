#include <iostream>
#include <cmath>
#include <iomanip>

#define MAX_INTERVALS 1000  // Maximum number of intervals allowed

// Probability density function (PDF) for standard normal distribution N(0, 1)
double normalDistributionPDF(double x) {
    return (1.0 / sqrt(2 * M_PI)) * exp(-0.5 * x * x);
}

// Function to discretize the normal distribution into equal-width intervals and compute probabilities
void quantizeNormalDistribution(double lower_bound, double upper_bound, int num_intervals) {
    if (num_intervals <= 0 || num_intervals > MAX_INTERVALS) {
        std::cerr << "Number of intervals must be between 1 and " << MAX_INTERVALS << std::endl;
        return;
    }

    double interval_width = (upper_bound - lower_bound) / num_intervals;

    // Use static array instead of vector
    double quantized_probs[MAX_INTERVALS] = {0.0};

    // Compute probability for each interval
    for (int i = 0; i < num_intervals; ++i) {
        double start = lower_bound + i * interval_width;
        double end = lower_bound + (i + 1) * interval_width;

        double probability = 0.0;
        for (double x = start; x < end; x += 0.001) {
            probability += normalDistributionPDF(x) * 0.001;  // Riemann sum approximation
        }

        quantized_probs[i] = probability;
    }

    // Output results in tabular format
    std::cout << "Quantized Interval | Probability\n";
    std::cout << "---------------------------------\n";
    for (int i = 0; i < num_intervals; ++i) {
        double start = lower_bound + i * interval_width;
        double end = lower_bound + (i + 1) * interval_width;

        std::cout << std::fixed << std::setprecision(4)
                  << "[" << start << ", " << end << "] : "
                  << quantized_probs[i] << std::endl;
    }
}

int main() {
    // Define parameters for quantization
    double lower_bound = -5.0;   // Lower bound of normal distribution range
    double upper_bound = 5.0;    // Upper bound of normal distribution range
    int num_intervals = 20;      // Number of intervals to divide the distribution

    // Perform quantization
    quantizeNormalDistribution(lower_bound, upper_bound, num_intervals);

    return 0;
}
