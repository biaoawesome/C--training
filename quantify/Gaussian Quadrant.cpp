#include <iostream>
#include <random>
#include <cmath>

// Class for generating Gaussian random pairs and analyzing quadrants
class GaussianQuadrant {
public:
    // Generate a pair of standard normal random numbers using Box-Muller transform
    static void generateGaussianPair(double& z0, double& z1) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(0.0, 1.0);

        double u1 = dis(gen);
        double u2 = dis(gen);

        z0 = std::sqrt(-2.0 * std::log(u1)) * std::cos(2.0 * M_PI * u2);  // First Gaussian
        z1 = std::sqrt(-2.0 * std::log(u1)) * std::sin(2.0 * M_PI * u2);  // Second Gaussian
    }

    // Simulate points and count how many fall into each quadrant
    static void simulate(int numSimulations) {
        // Static array to store quadrant counts
        const int NUM_QUADRANTS = 4;
        int quadrantCount[NUM_QUADRANTS] = {0};

        for (int i = 0; i < numSimulations; ++i) {
            double x, y;
            generateGaussianPair(x, y);

            if (x > 0 && y > 0) {
                ++quadrantCount[0];  // Quadrant I
            } else if (x < 0 && y > 0) {
                ++quadrantCount[1];  // Quadrant II
            } else if (x < 0 && y < 0) {
                ++quadrantCount[2];  // Quadrant III
            } else if (x > 0 && y < 0) {
                ++quadrantCount[3];  // Quadrant IV
            }
        }

        // Print counts
        std::cout << "Quadrant I (x > 0, y > 0): " << quadrantCount[0] << " points\n";
        std::cout << "Quadrant II (x < 0, y > 0): " << quadrantCount[1] << " points\n";
        std::cout << "Quadrant III (x < 0, y < 0): " << quadrantCount[2] << " points\n";
        std::cout << "Quadrant IV (x > 0, y < 0): " << quadrantCount[3] << " points\n";

        // Calculate and print percentages
        double total = numSimulations;
        std::cout.precision(2);
        std::cout << "Percentage in Quadrant I: " << (quadrantCount[0] / total) * 100 << "%\n";
        std::cout << "Percentage in Quadrant II: " << (quadrantCount[1] / total) * 100 << "%\n";
        std::cout << "Percentage in Quadrant III: " << (quadrantCount[2] / total) * 100 << "%\n";
        std::cout << "Percentage in Quadrant IV: " << (quadrantCount[3] / total) * 100 << "%\n";
    }
};

int main() {
    int numSimulations = 1000000;  // Number of simulations
    GaussianQuadrant::simulate(numSimulations);
    return 0;
}
