#include <iostream>
#include <cmath>
#define PI 3.141592653589793
using namespace std;

int main() {
    double g = 9.81;            // Gravity (m/s2)
    double L = 1.0;             // Pendulum length (m)
    double theta0 = 0.1;        // Initial angle (rad)
    
    double T = 2 * PI * sqrt(L / g);
    
    // Show angle vs time for one period
    cout << "Time(s)\tAngle(rad)\tAngular Velocity(rad/s)" << endl;
    
    for (double t = 0; t <= T; t += T/20) {
        double theta = theta0 * cos(2 * PI * t / T);
        double omega = -theta0 * (2 * PI / T) * sin(2 * PI * t / T);
        cout << t << "\t" << theta << "\t\t" << omega << endl;
    }
    return 0;
}
