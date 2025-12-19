#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double T0 = 100.0;          // Initial temperature (°„C)
    double Tenv = 20.0;         // Environment temperature (°„C)
    double k = 0.05;            // Cooling constant
    
    cout << "Time(min)\tTemperature(°„C)" << endl;
    
    // Simulate cooling for 60 minutes
    for (int t = 0; t <= 60; t += 5) {
        double T = Tenv + (T0 - Tenv) * exp(-k * t);
        cout << t << "\t\t" << T << endl;
    }
    return 0;
}
