#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>

// Ziggurat algorithm constants
#define ZIG_NUM 128           // Number of layers in the ziggurat table
#define PI 3.14159265358979323846
#define EXP_MIN -20.0         // Truncate very small probabilities

// Ziggurat tables
float zigguratTableX[ZIG_NUM];     // X values for normal distribution
float zigguratTableY[ZIG_NUM];     // Y values (density) for each X
float zigguratBoundary[ZIG_NUM];   // Upper boundary Y for each layer

// Initialize the ziggurat tables for normal distribution
void initZiggurat() {
    for (int i = 0; i < ZIG_NUM; ++i) {
        float x = static_cast<float>(i) / (ZIG_NUM - 1);  // Linear from 0 to 1
        zigguratTableX[i] = sqrtf(-2.0f * logf(x));        // Inverse of tail integral
        zigguratTableY[i] = expf(-0.5f * zigguratTableX[i] * zigguratTableX[i]);  // PDF(y)
        zigguratBoundary[i] = zigguratTableY[i];           // Initial boundary
    }
}

// Generate a standard normal distributed random number using Ziggurat algorithm
float ziggurat() {
    float x, y;
    int i;

    while (true) {
        // Generate uniform random numbers between [0, 1)
        x = static_cast<float>(rand()) / RAND_MAX;
        y = static_cast<float>(rand()) / RAND_MAX;

        i = static_cast<int>(x * ZIG_NUM);  // Determine which layer we're in

        if (y <= zigguratTableY[i]) {
            return zigguratTableX[i];  // Accept sample
        }

        if (i == 0) {
            // Handle bottom layer: use exponential tail approximation
            x = -logf(y) / 2.0f;
            return x;
        }
    }
}

int main() {
    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Initialize ziggurat tables
    initZiggurat();

    // Number of samples to generate
    const int numSamples = 10;

    std::cout << "Generating " << numSamples << " standard normal random numbers:\n";

    // Generate and print random numbers
    for (int i = 0; i < numSamples; ++i) {
        float value = ziggurat();
        std::cout << "Sample " << i + 1 << ": " << std::fixed << std::setprecision(6) << value << std::endl;
    }

    return 0;
}
