#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // Orbital mechanics simulation
    double gravitationalConstant = 6.67430e-11;  // N¡¤m2/kg2
    double sunMass = 1.989e30;                  // kg
    double earthMass = 5.972e24;                // kg
    double orbitalRadius = 1.496e11;            // m
    
    // Simulate one orbital period
    double period = 2 * M_PI * sqrt(pow(orbitalRadius, 3) / (gravitationalConstant * sunMass));
    double timeStep = 86400; // One day in seconds
    
    for (double t = 0; t <= period; t += timeStep) {
        double angle = 2 * M_PI * t / period;
        double x = orbitalRadius * cos(angle);
        double y = orbitalRadius * sin(angle);
        cout << "Day " << t/86400 << ": (" << x/1e9 << "e9, " << y/1e9 << "e9)m" << endl;
    }
    return 0;
}
