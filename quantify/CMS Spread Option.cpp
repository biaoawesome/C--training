#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

// Trapezoidal rule for numerical integration
double trapezoidalRule(function<double(double)> f, double a, double b, int n) {
    double h = (b - a) / n;
    double sum = (f(a) + f(b)) / 2.0;
    for (int i = 1; i < n; ++i) {
        sum += f(a + i * h);
    }
    return sum * h;
}

// Simpson's rule for numerical integration
double simpsonRule(function<double(double)> f, double a, double b, int n) {
    if (n % 2 != 0) {
        cout << "Warning: Simpson's rule requires an even number of intervals. Adjusting to nearest even number." << endl;
        n += 1;
    }
    double h = (b - a) / n;
    double sum = f(a) + f(b);

    // Odd indices
    for (int i = 1; i < n; i += 2) {
        sum += 4 * f(a + i * h);
    }

    // Even indices
    for (int i = 2; i < n - 1; i += 2) {
        sum += 2 * f(a + i * h);
    }

    return sum * h / 3.0;
}

// Example function: f(x) = x^2
double func(double x) {
    return x * x;
}

int main() {
    double a = 0.0;   // Lower limit of integration
    double b = 1.0;   // Upper limit of integration
    int n = 1000;     // Number of intervals

    // Compute integral using trapezoidal rule
    double result_trapezoidal = trapezoidalRule(func, a, b, n);
    cout << "Trapezoidal Rule Result: " << result_trapezoidal << endl;

    // Compute integral using Simpson's rule
    double result_simpson = simpsonRule(func, a, b, n);
    cout << "Simpson's Rule Result: " << result_simpson << endl;

    return 0;
}
