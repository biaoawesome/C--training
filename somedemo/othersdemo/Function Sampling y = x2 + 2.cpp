#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double start = -4.0;     // Start of interval
    double end = 4.0;        // End of interval
    double step = 0.5;       // Sampling step
    double coefficient = 2.0; // Function coefficient
    
    cout << "Function: y = x*x + " << coefficient << endl;
    cout << "x\t\ty" << endl;
    
    // Sample function values
    for (double x = start; x <= end + 0.001; x += step) {
        double y = x * x + coefficient;
        cout << x << "\t" << y << endl;
    }
    return 0;
}
