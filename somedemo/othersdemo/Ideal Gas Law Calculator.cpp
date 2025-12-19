#include <iostream>
using namespace std;

int main() {
    const double R = 8.314;     // Gas constant (J/(mol¡¤K))
    double n = 2.0;             // Moles of gas
    double T = 300.0;           // Temperature (K)
    double V0 = 0.5;            // Initial volume (m3)
    
    cout << "Volume(m3)\tPressure(Pa)" << endl;
    
    // Vary volume and calculate pressure
    for (double V = V0; V <= 2.0; V += 0.1) {
        double P = n * R * T / V;
        cout << V << "\t\t" << P << endl;
    }
    return 0;
}
