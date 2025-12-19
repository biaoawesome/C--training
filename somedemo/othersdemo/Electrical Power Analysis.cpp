#include <iostream>
using namespace std;

int main() {
    double resistance = 50.0;    // Ohms
    double voltageMin = 10.0;    // Volts
    double voltageMax = 100.0;   // Volts
    double steps = 10.0;
    
    cout << "Voltage(V)\tCurrent(A)\tPower(W)" << endl;
    
    // Analyze power dissipation across voltage range
    for (double V = voltageMin; V <= voltageMax; V += (voltageMax-voltageMin)/steps) {
        double I = V / resistance;
        double P = V * I;
        cout << V << "\t\t" << I << "\t\t" << P << endl;
    }
    return 0;
}
