#include <iostream>
#include <cmath>

using namespace std;

const int MAX_NNZ = 100; // 最大非零元素数
const int MAX_SIZE = 100; // 最大矩阵维数

// 压缩稀疏行（CSR）格式的稀疏矩阵
struct SparseMatrixCSR {
    double values[MAX_NNZ];   // 非零元素
    int colIndices[MAX_NNZ];  // 列索引
    int rowPtr[MAX_SIZE + 1]; // 行指针
    int n;                    // 矩阵大小 n x n
};

// 矩阵-向量乘法：A * x
void matVecMult(const SparseMatrixCSR& A, const double x[], double result[]) {
    for (int i = 0; i < A.n; ++i) {
        result[i] = 0.0;
        for (int j = A.rowPtr[i]; j < A.rowPtr[i + 1]; ++j) {
            result[i] += A.values[j] * x[A.colIndices[j]];
        }
    }
}

// 向量点积
double dotProduct(const double a[], const double b[], int size) {
    double result = 0.0;
    for (int i = 0; i < size; ++i) {
        result += a[i] * b[i];
    }
    return result;
}

// 向量范数
double vectorNorm(const double v[], int size) {
    double norm = 0.0;
    for (int i = 0; i < size; ++i) {
        norm += v[i] * v[i];
    }
    return sqrt(norm);
}

// 共轭梯度法求解 A * x = b
void conjugateGradient(const SparseMatrixCSR& A, const double b[], double x[],
                       double tol = 1e-6, int maxIter = 1000) {

    double r[MAX_SIZE]; // 残差
    double p[MAX_SIZE]; // 搜索方向
    double Ap[MAX_SIZE]; // A * p
    double tmp[MAX_SIZE]; // 临时向量

    // 初始化 x = 0
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
    // 示例：对称正定稀疏矩阵 A 和向量 b
    SparseMatrixCSR A = {
        {4.0, 1.0, 1.0, 4.0, 1.0, 4.0}, // 非零元素
        {0, 1, 0, 1, 2, 2},             // 列索引
        {0, 2, 4, 6},                   // 行指针
        3                               // 矩阵大小
    };

    double b[MAX_SIZE] = {1.0, 2.0, 3.0};
    double x[MAX_SIZE]; // 解向量

    // 使用共轭梯度法求解 A * x = b
    conjugateGradient(A, b, x);

    // 输出解
    cout << "Solution x:\n";
    for (int i = 0; i < A.n; ++i) {
        cout << x[i] << "\n";
    }

    return 0;
}
