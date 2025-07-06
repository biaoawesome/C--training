#include <iostream>
#include <cmath>

using namespace std;

const int MAX_SIZE = 1024; // 最大支持的节点数/系数数（根据需要调整）

// 生成高斯-切比雪夫 1 型正交规则的积分点和权重
void gaussChebyshevType1(int N, double points[], double weights[]) {
    double weightFactor = M_PI / N; // 权重因子

    for (int k = 0; k < N; ++k) {
        double theta = (2 * k + 1) * M_PI / (2 * N); // 极角
        points[k] = cos(theta);                      // 积分点
        weights[k] = weightFactor * sin(theta);       // 权重
    }
}

// 计算多项式的值
double polynomial(const double coeffs[], double x, int degree) {
    double result = 0.0;
    double x_power = 1.0;

    for (int i = 0; i <= degree; ++i) {
        result += coeffs[i] * x_power;
        x_power *= x;
    }

    return result;
}

// 计算多项式的精确积分值
double exactIntegral(const double coeffs[], int degree) {
    double integral = 0.0;

    for (int i = 0; i <= degree; ++i) {
        if (i % 2 == 0) {
            integral += coeffs[i] * 2.0 / (i + 1); // 奇数幂在 [-1, 1] 上积分为 0
        }
    }

    return integral;
}

int main() {
    // 定义多项式系数 P(x) = 1 + 2x + 3x^2
    const int degree = 2;
    double coeffs[MAX_SIZE] = {1.0, 2.0, 3.0};

    // 输入节点数量 N
    int N;
    cout << "Enter the number of nodes (N): ";
    cin >> N;

    if (N > MAX_SIZE || N <= 0) {
        cerr << "Invalid node count.\n";
        return 1;
    }

    // 生成积分点和权重
    double points[MAX_SIZE];
    double weights[MAX_SIZE];
    gaussChebyshevType1(N, points, weights);

    // 计算多项式的积分近似值
    double approxIntegral = 0.0;
    for (int k = 0; k < N; ++k) {
        approxIntegral += weights[k] * polynomial(coeffs, points[k], degree);
    }

    // 计算多项式的精确积分值
    double exactIntegralValue = exactIntegral(coeffs, degree);

    // 输出结果
    cout.precision(10);
    cout << "Approximate integral: " << fixed << approxIntegral << "\n";
    cout << "Exact integral: " << fixed << exactIntegralValue << "\n";
    cout << "Error: " << abs(approxIntegral - exactIntegralValue) << "\n";

    return 0;
}
