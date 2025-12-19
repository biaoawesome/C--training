#include <iostream>
#include <cmath>
#define PI 3.141592653589793
using namespace std;

int main() {
    double amplitude = 0.1;         // Meters
    double frequency = 2.0;         // Hz
    double phase = 0.0;             // Radians
    
    cout << "Time(s)\tPosition(m)\tVelocity(m/s)" << endl;
    
    // Simulate 5 seconds of motion
    for (double t = 0; t <= 5.0; t += 0.1) {
        double omega = 2 * PI * frequency;
        double position = amplitude * cos(omega * t + phase);
        double velocity = -amplitude * omega * sin(omega * t + phase);
        cout << t << "\t" << position << "\t\t" << velocity << endl;
    }
    return 0;
}
