#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double initialMass = 100.0;     // Initial mass (g)
    double halfLife = 5730.0;       // Half-life in years (Carbon-14)
    double lambda = log(2) / halfLife; // Decay constant
    
    cout << "Years\tMass(g)\t\tActivity(%/year)" << endl;
    
    // Simulate decay over 50000 years
    for (double years = 0; years <= 50000; years += 1000) {
        double mass = initialMass * exp(-lambda * years);
        double activity = mass * lambda * 100; // Percentage
        cout << years << "\t" << mass << "\t\t" << activity << endl;
    }
    return 0;
}
