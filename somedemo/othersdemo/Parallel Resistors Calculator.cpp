#include <iostream>
using namespace std;

int main() {
    double r1 = 100.0;          // First resistor (ohms)
    double r2 = 250.0;          // Second resistor (ohms)
    double r3 = 500.0;          // Third resistor (ohms)
    
    // Calculate equivalent resistance
    double invR = 1.0/r1 + 1.0/r2 + 1.0/r3;
    double equivalentR = 1.0 / invR;
    
    // Calculate current distribution at 12V
    double voltage = 12.0;
    double totalCurrent = voltage / equivalentR;
    
    cout << "Equivalent Resistance: " << equivalentR << " ¦¸" << endl;
    cout << "Total Current at 12V: " << totalCurrent << " A" << endl;
    cout << "Power Dissipation: " << voltage * totalCurrent << " W" << endl;
    return 0;
}
