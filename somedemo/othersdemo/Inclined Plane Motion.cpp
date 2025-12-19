#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double mass = 10.0;         // kg
    double angle = 30.0;        // degrees
    double frictionCoeff = 0.2; // Friction coefficient
    double g = 9.81;            // m/s2
    
    double angleRad = angle * M_PI / 180.0;
    double normalForce = mass * g * cos(angleRad);
    double frictionForce = frictionCoeff * normalForce;
    double gravityForce = mass * g * sin(angleRad);
    double netForce = gravityForce - frictionForce;
    double acceleration = netForce / mass;
    
    cout << "Time(s)\tVelocity(m/s)\tDistance(m)" << endl;
    
    // Simulate motion for 5 seconds
    for (double t = 0; t <= 5.0; t += 0.5) {
        double velocity = acceleration * t;
        double distance = 0.5 * acceleration * t * t;
        cout << t << "\t" << velocity << "\t\t" << distance << endl;
    }
    return 0;
}
