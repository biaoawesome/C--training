#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

// First derivative using forward difference method
double firstDerivative(function<double(double)> f, double x, double h = 1e-5) {
    return (f(x + h) - f(x)) / h;
}

// Second derivative using central difference method
double secondDerivative(function<double(double)> f, double x, double h = 1e-5) {
    return (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
}

// Compute the nth derivative recursively
double nthDerivative(function<double(double)> f, double x, int n, double h = 1e-5) {
    if (n == 1) {
        return firstDerivative(f, x, h); // First derivative
    } else if (n == 2) {
        return secondDerivative(f, x, h); // Second derivative
    } else {
        // For higher-order derivatives, use recursion
        function<double(double)> g = [f, n, h](double x_val) {
            return nthDerivative(f, x_val, n - 1, h);
        };
        return firstDerivative(g, x, h); // Recursive call to compute higher derivative
    }
}

// Example function: f(x) = x^3
double func(double x) {
    return pow(x, 3);
}

int main() {
    double x = 2.0;  // Point at which to evaluate the derivative
    int n = 3;       // Order of the derivative

    // Compute and print the result
    double result = nthDerivative(func, x, n);
    cout << "The " << n << "rd derivative of x^3 at x = " << x << " is: " << result << endl;

    return 0;
}
