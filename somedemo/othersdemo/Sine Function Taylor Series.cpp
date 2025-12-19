#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x = 1.0;             // Angle in radians
    double sin_x = 0.0;         // Sine approximation
    double term = x;            // First term
    double sign = 1.0;          // Alternating sign
    int k = 1;                  // Term counter
    int maxTerms = 15;
    
    cout << "Term\tApproximation\tError" << endl;
    
    // Taylor series: sin(x) = x - x3/3! + x?/5! - ...
    for (int i = 1; i <= maxTerms; i++) {
        sin_x += term;
        double error = fabs(sin_x - sin(x));
        cout << i << "\t" << sin_x << "\t\t" << error << endl;
        
        k += 2;
        sign *= -1;
        term *= x * x / (k * (k-1));
    }
    return 0;
}
