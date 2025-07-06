#include <stdio.h>
#include <math.h>
 
#define MAX_POINTS 100  // 数据点的最大数量
 
// 矩阵乘法函数：C = A * B
void matmul(double A[][MAX_POINTS], double B[], double C[], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        C[i] = 0;
        for (int j = 0; j < cols; j++) {
            C[i] += A[i][j] * B[j];
        }
    }
}
 
// 矩阵转置函数：B = A^T
void transpose(double A[][MAX_POINTS], double B[][MAX_POINTS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            B[j][i] = A[i][j];
        }
    }
}
 
// 矩阵求逆函数：利用高斯消元法求解矩阵的逆
int gauss_jordan(double A[][MAX_POINTS], double B[], int n) {
    double augmented[MAX_POINTS][MAX_POINTS + 1];
 
    // 创建增广矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = A[i][j];
        }
        augmented[i][n] = B[i];
    }
 
    // 高斯-乔丹消元法
    for (int i = 0; i < n; i++) {
        if (augmented[i][i] == 0) {
            return 0;  // 如果主对角线元素为0，则矩阵不可逆
        }
 
        // 归一化
        double pivot = augmented[i][i];
        for (int j = 0; j < n + 1; j++) {
            augmented[i][j] /= pivot;
        }
 
        // 消去列
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double factor = augmented[j][i];
                for (int k = 0; k < n + 1; k++) {
                    augmented[j][k] -= factor * augmented[i][k];
                }
            }
        }
    }
 
    // 结果存储在 B 中
    for (int i = 0; i < n; i++) {
        B[i] = augmented[i][n];
    }
 
    return 1;
}
 
// 最小二乘法多项式拟合
void polynomial_fit(double x[], double y[], int n, int degree, double coeffs[]) {
    double A[MAX_POINTS][MAX_POINTS] = {0};
    double b[MAX_POINTS] = {0};
    double AT[MAX_POINTS][MAX_POINTS] = {0};
    double ATA[MAX_POINTS][MAX_POINTS] = {0};
 
    // 构建矩阵 A 和向量 b
    for (int i = 0; i < n; i++) {
        double xi = 1;
        for (int j = 0; j <= degree; j++) {
            A[i][j] = xi;
            xi *= x[i];  // 计算 x^j
        }
        b[i] = y[i];
    }
 
    // 计算 A^T
    transpose(A, AT, n, degree + 1);
    // 计算 A^T * A
    matmul(AT, A, ATA, degree + 1, n);  // 正确传递整个矩阵 A
    // 计算 A^T * b
    matmul(AT, b, b, degree + 1, n);    // 正确传递向量 b
 
 
    // 求解 (A^T * A)^{-1} * (A^T * b) 得到系数
    if (!gauss_jordan(ATA, b, degree + 1)) {
        printf("Error: Matrix inversion failed.\n");
        return;
    }
 
    // 输出拟合结果
    for (int i = 0; i <= degree; i++) {
        coeffs[i] = b[i];
    }
}
 
// 打印拟合的多项式系数
void print_coeffs(double coeffs[], int degree) {
    printf("拟合的多项式系数：\n");
    for (int i = 0; i <= degree; i++) {
        printf("a[%d] = %lf\n", i, coeffs[i]);
    }
}
 
int main() {
    int n, degree;
 
    // 输入数据点的数量和多项式的阶数
    printf("请输入数据点的数量：");
    scanf("%d", &n);
    printf("请输入拟合的多项式阶数：");
    scanf("%d", &degree);
 
    double x[MAX_POINTS], y[MAX_POINTS], coeffs[MAX_POINTS];
 
    // 输入数据点
    printf("请输入数据点 (x, y)：\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = ", i);
        scanf("%lf", &x[i]);
        printf("y[%d] = ", i);
        scanf("%lf", &y[i]);
    }
 
    // 执行多项式拟合
    polynomial_fit(x, y, n, degree, coeffs);
 
    // 打印结果
    print_coeffs(coeffs, degree);
 
    return 0;
}
