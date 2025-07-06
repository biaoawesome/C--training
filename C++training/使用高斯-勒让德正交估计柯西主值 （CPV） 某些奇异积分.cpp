#include <iostream>
#include <cmath>

using namespace std;

const int MAX_GAUSS_POINTS = 3; // 最大支持的积分点数

// 高斯-勒让德正交规则的积分点和权重
void gaussLegendre(int n, double points[], double weights[]) {
    switch (n) {
        case 1:
            if (n > MAX_GAUSS_POINTS) return;
            points[0] = 0.0;
            weights[0] = 2.0;
            break;
        case 2:
            if (n > MAX_GAUSS_POINTS) return;
            points[0] = -0.5773502691896257;
            points[1] = 0.5773502691896257;
            weights[0] = 1.0;
            weights[1] = 1.0;
            break;
        case 3:
            if (n > MAX_GAUSS_POINTS) return;
            points[0] = -0.7745966692414834;
            points[1] = 0.0;
            points[2] = 0.7745966692414834;
            weights[0] = 0.5555555555555556;
            weights[1] = 0.8888888888888888;
            weights[2] = 0.5555555555555556;
            break;
        default:
            cerr << "Unsupported number of points for Gauss-Legendre quadrature.\n";
            exit(1);
    }
}

// 柯西主值积分
double cauchyPrincipalValue(double a, double b, double c,
                            const double points[], const double weights[], int n,
                            double (*f)(double)) {
    double integral = 0.0;

    // 映射函数：将区间 [a, b] 映射到 [-1, 1]
    auto mapToUnitInterval = [a, b](double x) {
        return 0.5 * (b - a) * x + 0.5 * (a + b);
    };

    // 计算积分
    for (int k = 0; k < n; ++k) {
        double x = mapToUnitInterval(points[k]);
        if (fabs(x - c) > 1e-10) { // 避免奇点
            integral += weights[k] * f(x) / (x - c);
        }
    }

    // 乘以映射的雅可比行列式
    integral *= 0.5 * (b - a);

    return integral;
}

// 示例函数 f(x) = x^2
double exampleFunction(double x) {
    return x * x;
}

int main() {
    // 输入积分区间和奇点
    double a, b, c;
    cout << "Enter the interval [a, b]: ";
    cin >> a >> b;
    cout << "Enter the singularity point c: ";
    cin >> c;

    // 生成高斯-勒让德正交规则的积分点和权重
    int n = 3; // 使用 3 个点
    double points[MAX_GAUSS_POINTS];
    double weights[MAX_GAUSS_POINTS];

    gaussLegendre(n, points, weights);

    // 计算柯西主值积分
    double cpv = cauchyPrincipalValue(a, b, c, points, weights, n, exampleFunction);

    // 输出结果
    cout << "Cauchy Principal Value: " << cpv << "\n";

    return 0;
}
