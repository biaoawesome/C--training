#include <iostream>
#include <cmath>

using namespace std;

// Step size for numerical differentiation
const double h = 0.001;

// Function type definition
typedef double (*Function)(double);

// Forward difference
double forwardDifference(Function f, double x) {
    return (f(x + h) - f(x)) / h;
}

// Backward difference
double backwardDifference(Function f, double x) {
    return (f(x) - f(x - h)) / h;
}

// Central difference
double centralDifference(Function f, double x) {
    return (f(x + h) - f(x - h)) / (2 * h);
}

// Test function 1: f(x) = x^2
double f1(double x) {
    return x * x;
}

// Analytical derivative of f1: f'(x) = 2x
double df1(double x) {
    return 2 * x;
}

// Test function 2: f(x) = sin(x)
double f2(double x) {
    return sin(x);
}

// Analytical derivative of f2: f'(x) = cos(x)
double df2(double x) {
    return cos(x);
}

// Main function
int main() {
    // Test 1: f(x) = x^2
    double x1 = 2.0;
    double numD1_central = centralDifference(f1, x1);
    double numD1_forward = forwardDifference(f1, x1);
    double numD1_backward = backwardDifference(f1, x1);
    double anaD1 = df1(x1);

    cout.precision(6);
    cout << "Test Function 1: f(x) = x^2" << endl;
    cout << "Central Difference: " << numD1_central << ", Error: " << fabs(numD1_central - anaD1) << endl;
    cout << "Forward Difference: " << numD1_forward << ", Error: " << fabs(numD1_forward - anaD1) << endl;
    cout << "Backward Difference: " << numD1_backward << ", Error: " << fabs(numD1_backward - anaD1) << endl;
    cout << endl;

    // Test 2: f(x) = sin(x)
    double x2 = M_PI / 4;
    double numD2_central = centralDifference(f2, x2);
    double numD2_forward = forwardDifference(f2, x2);
    double numD2_backward = backwardDifference(f2, x2);
    double anaD2 = df2(x2);

    cout << "Test Function 2: f(x) = sin(x)" << endl;
    cout << "Central Difference: " << numD2_central << ", Error: " << fabs(numD2_central - anaD2) << endl;
    cout << "Forward Difference: " << numD2_forward << ", Error: " << fabs(numD2_forward - anaD2) << endl;
    cout << "Backward Difference: " << numD2_backward << ", Error: " << fabs(numD2_backward - anaD2) << endl;
    cout << endl;

    return 0;
}
