#include <iostream>
#include <cmath>
#include <random>
#include <cassert>

#define MAX_SIZE 10000

class GSRModel {
public:
    // Constructor
    GSRModel(int p) : p(p) {}

    // Train the GSR model
    void train(const double* data, int n) {
        assert(n > p);  // Number of data points must be greater than AR order

        // Build auto-regressive matrix X and target vector y
        double X[MAX_SIZE * p];
        double y[MAX_SIZE];

        for (int t = p; t < n; ++t) {
            for (int i = 0; i < p; ++i) {
                X[(t - p) * p + i] = data[t - i - 1];
            }
            y[t - p] = data[t];
        }

        // Compute transpose(X)
        double Xt[p * (n - p)];
        transpose(X, Xt, n - p, p);

        // Compute XtX = Xt * X
        double XtX[p * p];
        multiplyMatrix(Xt, X, XtX, p, n - p, p);

        // Compute XtX_inv = inverse of XtX (only support 2x2 matrix here)
        double XtX_inv[p * p];
        invert(XtX, XtX_inv, p);

        // Compute Xt_y = Xt * y
        double Xt_y[p];
        multiplyMatrixVector(Xt, y, Xt_y, p, n - p);

        // Compute coefficients = XtX_inv * Xt_y
        multiplyMatrixVector(XtX_inv, Xt_y, coefficients, p, p);

        this->coefficientsCount = p;
    }

    // Predict based on fitted model
    double predict(const double* data) {
        double prediction = 0.0;
        for (int i = 0; i < p; ++i) {
            prediction += coefficients[i] * data[p - i - 1];
        }
        return prediction;
    }

    // Get fitted coefficients
    const double* getCoefficients() const {
        return coefficients;
    }

    int getCoefficientCount() const {
        return coefficientsCount;
    }

private:
    int p;  // Order of autoregressive process
    double coefficients[2];  // Model coefficients
    int coefficientsCount;

    // Matrix transpose
    void transpose(const double* A, double* AT, int rows, int cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                AT[j * rows + i] = A[i * cols + j];
            }
        }
    }

    // Multiply two matrices: A [rowsA x colsA], B [colsA x colsB] => result [rowsA x colsB]
    void multiplyMatrix(const double* A, const double* B, double* result, int rowsA, int colsA, int colsB) {
        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsB; ++j) {
                result[i * colsB + j] = 0.0;
                for (int k = 0; k < colsA; ++k) {
                    result[i * colsB + j] += A[i * colsA + k] * B[k * colsB + j];
                }
            }
        }
    }

    // Multiply matrix A [rowsA x colsA] with vector v [colsA] => result [rowsA]
    void multiplyMatrixVector(const double* A, const double* v, double* result, int rowsA, int colsA) {
        for (int i = 0; i < rowsA; ++i) {
            result[i] = 0.0;
            for (int j = 0; j < colsA; ++j) {
                result[i] += A[i * colsA + j] * v[j];
            }
        }
    }

    // Invert a 2x2 matrix
    void invert(const double* mat, double* invMat, int p) {
        assert(p == 2);  // Only support 2x2 matrix inversion
        double det = mat[0] * mat[3] - mat[1] * mat[2];
        assert(det != 0.0);  // Determinant must not be zero

        invMat[0] = mat[3] / det;
        invMat[1] = -mat[1] / det;
        invMat[2] = -mat[2] / det;
        invMat[3] = mat[0] / det;
    }
};

// Generate simulated AR data
void generateARData(double* data, int n, int p, const double* trueCoefficients, double noiseStdDev) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dis(0.0, noiseStdDev);

    for (int i = 0; i < p; ++i) {
        data[i] = dis(gen);  // Initialize first few values randomly
    }

    for (int t = p; t < n; ++t) {
        double noise = dis(gen);
        data[t] = 0.0;
        for (int i = 0; i < p; ++i) {
            data[t] += trueCoefficients[i] * data[t - i - 1];
        }
        data[t] += noise;
    }
}

int main() {
    const int n = 1000;  // Number of data points
    const int p = 2;     // Autoregressive order
    double trueCoefficients[] = {0.5, -0.3};  // True coefficients
    double noiseStdDev = 0.1;  // Noise standard deviation

    double data[n];  // Simulated AR data

    // Generate AR data
    generateARData(data, n, p, trueCoefficients, noiseStdDev);

    // Create and train the GSR model
    GSRModel model(p);
    model.train(data, n);

    // Output fitted coefficients
    const double* coefficients = model.getCoefficients();
    int coeffCount = model.getCoefficientCount();

    std::cout << "Fitted coefficients: ";
    for (int i = 0; i < coeffCount; ++i) {
        std::cout << coefficients[i] << " ";
    }
    std::cout << std::endl;

    // Make prediction using last 2 data points
    double testData[2] = {data[n - 2], data[n - 1]};
    double prediction = model.predict(testData);
    std::cout << "Predicted next value: " << prediction << std::endl;

    return 0;
}
