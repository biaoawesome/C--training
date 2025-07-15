#include <iostream>
#include <cmath>

using namespace std;

// Maximum number of data points
const int MAX_POINTS = 100;

// Structure to store spline coefficients
typedef struct {
    double x[MAX_POINTS];     // x values (knots)
    double y[MAX_POINTS];     // y values (function values)
    double a[MAX_POINTS];     // a_i = y[i]
    double b[MAX_POINTS];     // linear coefficient
    double c[MAX_POINTS];     // quadratic coefficient
    double d[MAX_POINTS];     // cubic coefficient
    int n;                    // number of data points
} Spline;

// Function: Compute cubic spline interpolation
void cubicSplineInterpolation(double x[], double y[], int n, Spline* spline) {
    double h[MAX_POINTS - 1];   // interval lengths
    double alpha[MAX_POINTS - 1];
    double l[MAX_POINTS];       // tridiagonal matrix parameters
    double mu[MAX_POINTS];      // tridiagonal matrix parameters
    double z[MAX_POINTS];       // second derivatives

    // Step 1: Compute intervals and initial values
    for (int i = 0; i < n - 1; ++i) {
        h[i] = x[i + 1] - x[i];
    }

    l[0] = 1.0;
    mu[0] = 0.0;
    z[0] = 0.0;

    // Step 2: Construct the tridiagonal system
    for (int i = 1; i < n - 1; ++i) {
        l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        alpha[i] = 3 * ((y[i + 1] - y[i]) / h[i] - (y[i] - y[i - 1]) / h[i - 1]);
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n - 1] = 1.0;
    z[n - 1] = 0.0;
    spline->c[n - 1] = 0.0;

    // Step 3: Back substitution to compute c[i]
    for (int i = n - 2; i >= 0; --i) {
        spline->c[i] = z[i] - mu[i] * spline->c[i + 1];
        spline->b[i] = (y[i + 1] - y[i]) / h[i] - h[i] * (spline->c[i + 1] + 2 * spline->c[i]) / 3;
        spline->d[i] = (spline->c[i + 1] - spline->c[i]) / (3 * h[i]);
        spline->a[i] = y[i];
    }

    // Copy input points into spline structure
    for (int i = 0; i < n; ++i) {
        spline->x[i] = x[i];
        spline->y[i] = y[i];
    }
    spline->n = n;
}

// Function: Print computed spline coefficients
void printSpline(const Spline* spline) {
    cout << "Spline coefficients:\n";
    for (int i = 0; i < spline->n - 1; ++i) {
        cout << "Interval [" << spline->x[i] << ", " << spline->x[i + 1] << "]:\n";
        cout << "a: " << spline->a[i]
             << ", b: " << spline->b[i]
             << ", c: " << spline->c[i]
             << ", d: " << spline->d[i] << "\n";
    }
}

// Function: Evaluate the interpolated value at a given x
double evaluateSpline(const Spline* spline, double x_val) {
    int i = 0;
    while (i < spline->n - 1 && x_val > spline->x[i + 1]) {
        ++i;
    }

    double dx = x_val - spline->x[i];
    return spline->a[i] + spline->b[i] * dx + spline->c[i] * dx * dx + spline->d[i] * dx * dx * dx;
}

// Main function
int main() {
    // Sample input data points
    double x[] = {0, 1, 2, 3, 4};
    double y[] = {1, 2, 0, 2, 1};
    int n = sizeof(x) / sizeof(x[0]);

    // Initialize spline structure
    Spline spline;
    spline.n = n;

    // Compute cubic spline
    cubicSplineInterpolation(x, y, n, &spline);

    // Output coefficients
    printSpline(&spline);

    // Evaluate at a specific point
    double x_val = 2.5;
    double result = evaluateSpline(&spline, x_val);
    cout << "Interpolated value at x = " << x_val << " is " << result << endl;

    return 0;
}
