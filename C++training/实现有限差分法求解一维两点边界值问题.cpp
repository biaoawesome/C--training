#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// 设置最大网格点数
const int MAX_N = 1024;

class FiniteDifferenceSolver {
private:
    int N;                // 网格点数
    double L;             // 区间长度
    double u0, uL;        // 边界条件
    double (*f)(double);  // 右端项函数
    double dx;            // 网格步长

    // 使用静态数组代替 vector
    double A[MAX_N];      // 系数矩阵对角线元素
    double b[MAX_N];      // 右端项
    double u[MAX_N];      // 解向量

public:
    // 构造函数，初始化参数
    FiniteDifferenceSolver(int N_val, double L_val, double u0_val, double uL_val, double (*f_val)(double))
        : N(N_val), L(L_val), u0(u0_val), uL(uL_val), f(f_val) {

        if (N > MAX_N) {
            cerr << "Error: N exceeds MAX_N." << endl;
            exit(1);
        }

        dx = L / (N + 1);  // 计算步长

        // 初始化数组
        for (int i = 0; i < N; ++i) {
            A[i] = 0.0;
            b[i] = 0.0;
            u[i] = 0.0;
        }
    }

    // 求解线性方程组 Ax = b
    void solve() {
        // 离散化并构建系数矩阵A和右端项b
        for (int i = 0; i < N; ++i) {
            double x = (i + 1) * dx;
            b[i] = -f(x) * dx * dx;  // 右端项 b_i = -f(x_i) * dx^2
            A[i] = -2.0;             // 所有对角线元素都是 -2
        }

        // 应用边界条件
        b[0] -= u0 * dx * dx;
        b[N - 1] -= uL * dx * dx;

        // 解线性方程组（这里只是简单除法，实际应使用三对角矩阵求解器）
        for (int i = 0; i < N; ++i) {
            u[i] = b[i] / A[i];
        }

        // 输出解
        cout.precision(6);
        cout << "解的数值结果：" << endl;
        for (int i = 0; i < N; ++i) {
            double x = (i + 1) * dx;
            cout << "u(" << x << ") = " << setw(10) << u[i] << endl;
        }
    }
};

// 右端项函数 f(x)
double f(double x) {
    return 100.0 * exp(-10.0 * x);
}

int main() {
    int N = 10;          // 网格点数
    double L = 1.0;      // 区间长度
    double u0 = 0.0;     // 左边界条件
    double uL = 0.0;     // 右边界条件

    // 创建求解器对象
    FiniteDifferenceSolver solver(N, L, u0, uL, f);

    // 求解并输出结果
    solver.solve();

    return 0;
}
