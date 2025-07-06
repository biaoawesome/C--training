#include <iostream>
#include <cmath>

using namespace std;

const int MAX_NNZ = 100; // ������Ԫ����
const int MAX_SIZE = 100; // ������ά��

// ѹ��ϡ���У�CSR����ʽ��ϡ�����
struct SparseMatrixCSR {
    double values[MAX_NNZ];   // ����Ԫ��
    int colIndices[MAX_NNZ];  // ������
    int rowPtr[MAX_SIZE + 1]; // ��ָ��
    int n;                    // �����С n x n
};

// ����-�����˷���A * x
void matVecMult(const SparseMatrixCSR& A, const double x[], double result[]) {
    for (int i = 0; i < A.n; ++i) {
        result[i] = 0.0;
        for (int j = A.rowPtr[i]; j < A.rowPtr[i + 1]; ++j) {
            result[i] += A.values[j] * x[A.colIndices[j]];
        }
    }
}

// �������
double dotProduct(const double a[], const double b[], int size) {
    double result = 0.0;
    for (int i = 0; i < size; ++i) {
        result += a[i] * b[i];
    }
    return result;
}

// ��������
double vectorNorm(const double v[], int size) {
    double norm = 0.0;
    for (int i = 0; i < size; ++i) {
        norm += v[i] * v[i];
    }
    return sqrt(norm);
}

// �����ݶȷ���� A * x = b
void conjugateGradient(const SparseMatrixCSR& A, const double b[], double x[],
                       double tol = 1e-6, int maxIter = 1000) {

    double r[MAX_SIZE]; // �в�
    double p[MAX_SIZE]; // ��������
    double Ap[MAX_SIZE]; // A * p
    double tmp[MAX_SIZE]; // ��ʱ����

    // ��ʼ�� x = 0
    for (int i = 0; i < A.n; ++i) {
        x[i] = 0.0;
        r[i] = b[i];
        p[i] = r[i];
    }

    double rNorm = vectorNorm(r, A.n);
    int k = 0;

    while (k < maxIter && rNorm > tol) {
        matVecMult(A, p, Ap); // Ap = A * p

        double alpha = dotProduct(r, r, A.n) / dotProduct(p, Ap, A.n);

        // x += alpha * p
        // r -= alpha * Ap
        for (int i = 0; i < A.n; ++i) {
            x[i] += alpha * p[i];
            r[i] -= alpha * Ap[i];
        }

        double beta = dotProduct(r, r, A.n) / (rNorm * rNorm);
        rNorm = vectorNorm(r, A.n);

        // p = r + beta * p
        for (int i = 0; i < A.n; ++i) {
            p[i] = r[i] + beta * p[i];
        }

        k++;
    }

    cout << "Conjugate Gradient converged in " << k << " iterations.\n";
}

int main() {
    // ʾ�����Գ�����ϡ����� A ������ b
    SparseMatrixCSR A = {
        {4.0, 1.0, 1.0, 4.0, 1.0, 4.0}, // ����Ԫ��
        {0, 1, 0, 1, 2, 2},             // ������
        {0, 2, 4, 6},                   // ��ָ��
        3                               // �����С
    };

    double b[MAX_SIZE] = {1.0, 2.0, 3.0};
    double x[MAX_SIZE]; // ������

    // ʹ�ù����ݶȷ���� A * x = b
    conjugateGradient(A, b, x);

    // �����
    cout << "Solution x:\n";
    for (int i = 0; i < A.n; ++i) {
        cout << x[i] << "\n";
    }

    return 0;
}
