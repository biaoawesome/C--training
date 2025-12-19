#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double initialHeight = 100.0;   // Meters
    double gravity = 9.81;          // m/s2
    double timeStep = 0.1;          // Seconds
    
    cout << "Time(s)\tHeight(m)\tVelocity(m/s)" << endl;
    
    // Simulate free fall until ground impact
    for (double t = 0; t <= sqrt(2*initialHeight/gravity); t += timeStep) {
        double height = initialHeight - 0.5 * gravity * t * t;
        double velocity = gravity * t;
        cout << t << "\t" << height << "\t\t" << velocity << endl;
    }
    return 0;
}
