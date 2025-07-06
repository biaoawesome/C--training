#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

const int MAX_SIZE = 10; // 设置最大行/列数（可根据需要调整）

// 初始化零矩阵
void initializeMatrixZero(double matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}

// 初始化单位矩阵（仅适用于方阵）
void initializeMatrixIdentity(double matrix[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

// 初始化随机矩阵
void initializeMatrixRandom(double matrix[MAX_SIZE][MAX_SIZE], int rows, int cols, double minVal, double maxVal) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(minVal, maxVal);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = dis(gen);
        }
    }
}

// 打印矩阵
void printMatrix(const double matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << setw(10) << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

// 打印向量
void printVector(const double vec[MAX_SIZE], int size) {
    for (int i = 0; i < size; ++i) {
        cout << setw(10) << vec[i] << " ";
    }
    cout << "\n";
}

// 复制矩阵
void copyMatrix(double dest[MAX_SIZE][MAX_SIZE], const double src[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            dest[i][j] = src[i][j];
        }
    }
}

// 复制向量
void copyVector(double dest[MAX_SIZE], const double src[MAX_SIZE], int size) {
    for (int i = 0; i < size; ++i) {
        dest[i] = src[i];
    }
}

int main() {
    const int rows = 3;
    const int cols = 3;
    const int vecSize = 3;

    double zeroMatrix[MAX_SIZE][MAX_SIZE];
    double identityMatrix[MAX_SIZE][MAX_SIZE];
    double randomMatrix[MAX_SIZE][MAX_SIZE];
    double copiedMatrix[MAX_SIZE][MAX_SIZE];

    double vec[MAX_SIZE] = {1.0, 2.0, 3.0};
    double copiedVec[MAX_SIZE];

    // 初始化矩阵
    initializeMatrixZero(zeroMatrix, rows, cols);
    initializeMatrixIdentity(identityMatrix, rows);
    initializeMatrixRandom(randomMatrix, rows, cols, 0.0, 1.0);

    // 打印矩阵和向量
    cout << "Zero Matrix:\n";
    printMatrix(zeroMatrix, rows, cols);

    cout << "Identity Matrix:\n";
    printMatrix(identityMatrix, rows, rows);

    cout << "Random Matrix:\n";
    printMatrix(randomMatrix, rows, cols);

    cout << "Vector:\n";
    printVector(vec, vecSize);
    // 复制矩阵和向量
    copyMatrix(copiedMatrix, randomMatrix, rows, cols);
    copyVector(copiedVec, vec, vecSize);

    cout << "Copied Random Matrix:\n";
    printMatrix(copiedMatrix, rows, cols);

    cout << "Copied Vector:\n";
    printVector(copiedVec, vecSize);

    return 0;
}
