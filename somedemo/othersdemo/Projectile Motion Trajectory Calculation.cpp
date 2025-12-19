#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // Initialize projectile motion parameters
    double initialVelocity = 50.0;  // m/s
    double angle = 45.0;            // degrees
    double gravity = 9.81;          // m/s2
    
    // Convert angle to radians
    double angleRad = angle * M_PI / 180.0;
    double vx = initialVelocity * cos(angleRad);
    double vy = initialVelocity * sin(angleRad);
    
    // Calculate trajectory points
    double timeStep = 0.1;
    double totalTime = 2.0 * vy / gravity;
    
    for (double t = 0; t <= totalTime; t += timeStep) {
        double x = vx * t;
        double y = vy * t - 0.5 * gravity * t * t;
        cout << "Time: " << t << "s, Position: (" << x << ", " << y << ")m" << endl;
    }
    return 0;
}
