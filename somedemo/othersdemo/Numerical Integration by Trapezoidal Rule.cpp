#include <iostream>
#include <cmath>
using namespace std;

double f(double x) {
    return x * x + 2 * x + 1;  // Function to integrate
}

int main() {
    double a = 0.0;         // Lower bound
    double b = 2.0;         // Upper bound
    double n = 1000.0;      // Number of trapezoids
    
    double h = (b - a) / n; // Step size
    double sum = (f(a) + f(b)) / 2.0;
    
    // Apply trapezoidal rule
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }
    
    double integral = sum * h;
    cout << "Integral from " << a << " to " << b << ": " << integral << endl;
    return 0;
}
