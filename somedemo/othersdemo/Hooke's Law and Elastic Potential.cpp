#include <iostream>
using namespace std;

int main() {
    double k = 1000.0;          // Spring constant (N/m)
    double x0 = 0.0;            // Natural length (m)
    double xMax = 0.5;          // Maximum extension (m)
    double steps = 50.0;
    
    cout << "Extension(m)\tForce(N)\tPotential(J)" << endl;
    
    // Calculate force and potential energy
    for (int i = 0; i <= steps; i++) {
        double x = x0 + (xMax - x0) * i / steps;
        double force = k * x;
        double potential = 0.5 * k * x * x;
        cout << x << "\t\t" << force << "\t\t" << potential << endl;
    }
    return 0;
}
