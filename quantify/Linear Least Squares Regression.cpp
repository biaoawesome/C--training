#include <iostream>
#include <numeric>

using namespace std;

// Maximum allowed data size for static arrays
const size_t MAX_DATA_SIZE = 100;

// Linear Regression Class
class LinearRegression {
private:
    double beta0; // Intercept
    double beta1; // Slope

public:
    // Constructor is not needed anymore since we pass data in fit()

    // Fit regression coefficients using ordinary least squares (OLS)
    void fit(const double x[], const double y[], int n) {
        if (n == 0 || n > MAX_DATA_SIZE) {
            cerr << "Error: Invalid data size." << endl;
            return;
        }

        double sumX = 0.0;
        double sumY = 0.0;
        double sumXY = 0.0;
        double sumX2 = 0.0;

        for (int i = 0; i < n; ++i) {
            sumX += x[i];
            sumY += y[i];
            sumXY += x[i] * y[i];
            sumX2 += x[i] * x[i];
        }

        // Compute slope and intercept
        beta1 = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
        beta0 = (sumY - beta1 * sumX) / n;
    }

    // Get intercept
    double getBeta0() const {
        return beta0;
    }

    // Get slope
    double getBeta1() const {
        return beta1;
    }

    // Predict y value based on given x value
    double predict(double xVal) const {
        return beta0 + beta1 * xVal;
    }
};

int main() {
    // Input dataset (independent variable x and dependent variable y)
    double xData[] = {1, 2, 3, 4, 5};             // Independent variable
    double yData[] = {1, 2, 2.8, 4.1, 5};         // Dependent variable

    // Calculate data size
    int dataSize = sizeof(xData) / sizeof(xData[0]);

    // Create linear regression object
    LinearRegression lr;

    // Fit the model to the data
    lr.fit(xData, yData, dataSize);

    // Output regression equation
    cout << "Regression Equation: y = " << lr.getBeta0() << " + " << lr.getBeta1() << " * x" << endl;

    // Test prediction
    double testX = 6;
    double predictedY = lr.predict(testX);
    cout << "Predicted value at x = " << testX << " is: " << predictedY << endl;

    return 0;
}
