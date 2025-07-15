#include <iostream>

using namespace std;

// Maximum size of the matrix
const int MAX_SIZE = 100;

// Structure to represent a tridiagonal matrix
struct TridiagonalMatrix {
    int n;                    // Matrix size
    double lower[MAX_SIZE];   // Lower diagonal (size n-1)
    double diag[MAX_SIZE];    // Main diagonal (size n)
    double upper[MAX_SIZE];   // Upper diagonal (size n-1)
};

// Initialize matrix with given size
void initMatrix(TridiagonalMatrix* matrix, int size) {
    matrix->n = size;
}

// Set main diagonal
void setDiagonal(TridiagonalMatrix* matrix, double diag[], int size) {
    if (size != matrix->n) return;
    for (int i = 0; i < size; ++i) {
        matrix->diag[i] = diag[i];
    }
}

// Set lower diagonal
void setLower(TridiagonalMatrix* matrix, double lower[], int size) {
    if (size != matrix->n - 1) return;
    for (int i = 0; i < size; ++i) {
        matrix->lower[i] = lower[i];
    }
}

// Set upper diagonal
void setUpper(TridiagonalMatrix* matrix, double upper[], int size) {
    if (size != matrix->n - 1) return;
    for (int i = 0; i < size; ++i) {
        matrix->upper[i] = upper[i];
    }
}

// Solve tridiagonal system using Thomas algorithm
void thomasSolve(const TridiagonalMatrix* matrix, double b[], double x[], int n) {
    double y[MAX_SIZE];
    double temp;

    // Forward elimination
    y[0] = b[0] / matrix->diag[0];
    for (int i = 1; i < n; ++i) {
        temp = matrix->diag[i] - matrix->lower[i - 1] * matrix->upper[i - 1] / matrix->diag[i - 1];
        y[i] = (b[i] - matrix->lower[i - 1] * y[i - 1] / matrix->diag[i - 1]) / temp;
    }

    // Back substitution
    x[n - 1] = y[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        x[i] = y[i] - matrix->upper[i] * x[i + 1] / matrix->diag[i];
    }
}

// Main function
int main() {
    const int n = 5;
    TridiagonalMatrix matrix;
    initMatrix(&matrix, n);

    // Set diagonals
    double diag[] = {4.0, 4.0, 4.0, 4.0, 4.0};
    double lower[] = {-1.0, -1.0, -1.0, -1.0};
    double upper[] = {-1.0, -1.0, -1.0, -1.0};
    double b[] = {5.0, 5.0, 5.0, 5.0, 5.0};

    setDiagonal(&matrix, diag, n);
    setLower(&matrix, lower, n - 1);
    setUpper(&matrix, upper, n - 1);

    // Solve the system
    double x[MAX_SIZE];
    thomasSolve(&matrix, b, x, n);

    // Output the solution
    cout.precision(4);
    cout << "Solution vector x:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << x[i] << " ";
    }
    cout << endl;

    return 0;
}
