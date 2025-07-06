#include <iostream>
#include <cmath>

using namespace std;

// 设置最大支持的积分点数
const int MAX_POINTS = 1024;

// 计算第 n 阶勒让德多项式 P_n(x)
double legendre(int n, double x) {
    if (n == 0) {
        return 1.0;
    } else if (n == 1) {
        return x;
    } else {
        return ((2 * n - 1) * x * legendre(n - 1, x) - (n - 1) * legendre(n - 2, x)) / n;
    }
}

// 计算第 n 阶勒让德多项式的导数 P'_n(x)
double legendre_derivative(int n, double x) {
    if (n == 0) {
        return 0.0;
    } else if (n == 1) {
        return 1.0;
    } else {
        return (n * (legendre(n - 1, x) - x * legendre(n, x))) / (1 - x * x);
    }
}

// 计算 N 点高斯-勒让德积分点和权重
void gauss_legendre(int N, double x[], double w[]) {
    const double eps = 1e-15;
    const int max_iter = 100;

    for (int i = 0; i < N; ++i) {
        double z = cos(M_PI * (i + 0.75) / (N + 0.5));
        double z1;

        for (int iter = 0; iter < max_iter; ++iter) {
            double p1 = 1.0;
            double p2 = 0.0;

            for (int j = 0; j < N; ++j) {
                double p3 = p2;
                p2 = p1;
                p1 = ((2 * j + 1) * z * p2 - j * p3) / (j + 1);
            }

            double pp = N * (z * p1 - p2) / (z * z - 1);
            z1 = z;
            z = z1 - p1 / pp;

            if (fabs(z - z1) < eps) {
                break;
            }
        }

        x[i] = z;
        w[i] = 2.0 / ((1.0 - z * z) * pow(legendre_derivative(N, z), 2));
    }
}

// 示例被积函数 f(x)
double f(double x) {
    return sin(x); // 示例：积分区间 [-1, 1]
}

// 定积分近似值
double integrate(int N, const double x[], const double w[], double (*func)(double)) {
    double sum = 0.0;
    for (int i = 0; i < N; ++i) {
        sum += w[i] * func(x[i]);
    }
    return sum;
}

// 主函数
int main() {
    int N;
    cout << "Enter number of Gauss-Legendre quadrature points (N): ";
    cin >> N;

    if (N <= 0 || N > MAX_POINTS) {
        cerr << "Invalid number of points. Must be between 1 and " << MAX_POINTS << endl;
        return 1;
    }

    double x[MAX_POINTS]; // 积分点
    double w[MAX_POINTS]; // 权重

    // 生成积分点和权重
    gauss_legendre(N, x, w);

    // 计算积分
    double result = integrate(N, x, w, f);

    // 输出结果
    cout.precision(15);
    cout << fixed;
    cout << "Integral value: " << result << endl;

    return 0;
}
