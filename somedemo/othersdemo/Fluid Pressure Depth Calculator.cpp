#include <iostream>
using namespace std;

int main() {
    double density = 1000.0;    // Water density (kg/m3)
    double gravity = 9.81;      // Gravity (m/s2)
    double maxDepth = 100.0;    // Maximum depth (m)
    
    cout << "Depth(m)\tPressure(Pa)\tAtmospheres" << endl;
    
    // Calculate pressure at various depths
    for (double depth = 0; depth <= maxDepth; depth += 5) {
        double pressure = density * gravity * depth;
        double atmospheres = pressure / 101325.0;
        cout << depth << "\t\t" << pressure << "\t\t" << atmospheres << endl;
    }
    return 0;
}
