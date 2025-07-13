#include <iostream>
#include <cmath>

#define MAX_DATA_SIZE 1000  // Maximum allowed size for the time series data

// Class to compute auto-covariance of a time series
class AutoCovariance {
public:
    // Constructor: takes raw time series data and its size
    AutoCovariance(const double* data, int size) : size_(size) {
        // Copy data into internal array
        for (int i = 0; i < size_; ++i) {
            data_[i] = data[i];
        }
        mean_ = computeMean();  // Compute the mean of the time series
    }

    // Calculate auto-covariance for a given lag value
    double calculateAutoCovariance(int lag) {
        double cov = 0.0;

        // Sum over all valid pairs (t, t+lag)
        for (int t = 0; t < size_ - lag; ++t) {
            double term1 = data_[t] - mean_;
            double term2 = data_[t + lag] - mean_;
            cov += term1 * term2;
        }

        return cov / size_;  // Normalize by total number of data points
    }

    // Print auto-covariance values for all possible lags
    void printAllAutoCovariances() {
        for (int lag = 0; lag < size_; ++lag) {
            double autoCov = calculateAutoCovariance(lag);
            std::cout.precision(6);
            std::cout << "Lag " << lag << ": " << std::fixed << autoCov << std::endl;
        }
    }

private:
    double data_[MAX_DATA_SIZE];  // Time series data stored in a static array
    int size_;                     // Number of elements in the time series
    double mean_;                  // Mean of the time series

    // Compute the mean of the time series
    double computeMean() {
        double sum = 0.0;
        for (int i = 0; i < size_; ++i) {
            sum += data_[i];
        }
        return sum / size_;
    }
};

// Test function for the AutoCovariance class
void testAutoCovariance() {
    // Simulated time series data
    double data[] = {2.0, 3.0, 5.0, 7.0, 9.0, 6.0, 4.0, 2.0, 5.0, 8.0};
    int size = sizeof(data) / sizeof(data[0]);  // Compute the array size

    // Create an AutoCovariance object
    AutoCovariance ac(data, size);

    // Print auto-covariance values for all lags
    ac.printAllAutoCovariances();
}

int main() {
    // Run the auto-covariance calculation test
    testAutoCovariance();

    return 0;
}
