#include <iostream>
using namespace std;

int main() {
    double L0 = 10.0;           // Initial length (m)
    double alpha = 12e-6;       // Coefficient of thermal expansion (1/°„C)
    double T0 = 20.0;           // Initial temperature (°„C)
    
    cout << "Temperature(°„C)\tLength(m)\tExpansion(m)" << endl;
    
    // Calculate expansion from 20°„C to 100°„C
    for (double T = T0; T <= 100; T += 10) {
        double deltaT = T - T0;
        double L = L0 * (1 + alpha * deltaT);
        double expansion = L - L0;
        cout << T << "\t\t" << L << "\t" << expansion << endl;
    }
    return 0;
}
