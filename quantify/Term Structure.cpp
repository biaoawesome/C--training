#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Structure to represent a bond
struct Bond {
    double faceValue;     // Face value of the bond
    double couponRate;    // Annual coupon rate (e.g., 0.05 for 5%)
    double maturity;      // Time to maturity in years
    double marketPrice;   // Market price of the bond
};

// Calculate present value of a bond using a given discount rate
double getPresentValue(const Bond& bond, double discountRate) {
    double presentValue = 0.0;
    double couponPayment = bond.faceValue * bond.couponRate;

    for (int t = 1; t <= bond.maturity; ++t) {
        presentValue += couponPayment / pow(1 + discountRate, t);
    }

    // Add final principal repayment
    presentValue += bond.faceValue / pow(1 + discountRate, bond.maturity);

    return presentValue;
}

// Linear fitting function: y = a * x + b
double linearFit(double t, double a, double b) {
    return a * t + b;
}

// Polynomial fitting function: y = a * x^2 + b * x + c
double polynomialFit(double t, double a, double b, double c) {
    return a * t * t + b * t + c;
}

// Placeholder for spline fit
double splineFit(double t) {
    return 0.0; // Placeholder
}

// Least squares fitting model (linear assumption here)
double leastSquaresFit(double t, double a, double b) {
    return a * t + b;
}

// For functions with signature: f(t, a, b)
double calculateTotalError_LinearLike(const Bond bonds[], int size, double (*fitFunc)(double, double, double)) {
    double totalError = 0.0;
    double a = 0.03, b = 0.02; // Example parameters

    for (int i = 0; i < size; ++i) {
        double t = bonds[i].maturity;
        double discountRate = fitFunc(t, a, b);
        double theoreticalPrice = getPresentValue(bonds[i], discountRate);
        double error = theoreticalPrice - bonds[i].marketPrice;
        totalError += error * error;
    }

    return totalError;
}

// For functions with signature: f(t, a, b, c)
double calculateTotalError_Polynomial(const Bond bonds[], int size, double a, double b, double c) {
    double totalError = 0.0;

    for (int i = 0; i < size; ++i) {
        double t = bonds[i].maturity;
        double discountRate = a * t * t + b * t + c;
        double theoreticalPrice = getPresentValue(bonds[i], discountRate);
        double error = theoreticalPrice - bonds[i].marketPrice;
        totalError += error * error;
    }

    return totalError;
}

// For functions with signature: f(t)
double calculateTotalError_Spline(const Bond bonds[], int size, double (*fitFunc)(double)) {
    double totalError = 0.0;
    double a = 0.03, b = 0.02; // Dummy values if needed

    for (int i = 0; i < size; ++i) {
        double t = bonds[i].maturity;
        double discountRate = fitFunc(t); // Spline only takes one parameter
        double theoreticalPrice = getPresentValue(bonds[i], discountRate);
        double error = theoreticalPrice - bonds[i].marketPrice;
        totalError += error * error;
    }

    return totalError;
}

int main() {
    const int numBonds = 5;

    // Initialize bonds manually
    Bond bonds[numBonds] = {
        {1000, 0.05, 1, 1050},
        {1000, 0.05, 2, 1100},
        {1000, 0.05, 3, 1150},
        {1000, 0.05, 4, 1200},
        {1000, 0.05, 5, 1250}
    };

    // Linear fit error
    double linearError = calculateTotalError_LinearLike(bonds, numBonds, linearFit);
    cout << fixed << setprecision(4);
    cout << "Linear Fit Error: " << linearError << endl;

    // Polynomial fit error
    double polyError = calculateTotalError_Polynomial(bonds, numBonds, 0.02, 0.01, 0.03);
    cout << "Polynomial Fit Error: " << polyError << endl;

    // Spline fit error (placeholder)
    double splineError = calculateTotalError_Spline(bonds, numBonds, splineFit);
    cout << "Spline Fit Error: " << splineError << endl;

    // Least Squares Fit (same as linear in this case)
    double lsqError = calculateTotalError_LinearLike(bonds, numBonds, leastSquaresFit);
    cout << "Least Squares Fit Error: " << lsqError << endl;

    return 0;
}
