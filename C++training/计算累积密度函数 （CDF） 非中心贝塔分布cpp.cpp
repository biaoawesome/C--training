#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <limits>
#include <cassert>

using namespace std;

// 计算贝塔函数 B(a, b)
double betaFunction(double a, double b) {
    return tgamma(a) * tgamma(b) / tgamma(a + b);
}

// 计算非中心贝塔分布的PDF
double noncentralBetaPDF(double x, double a, double b, double lambda) {
    if (x <= 0 || x >= 1 || a <= 0 || b <= 0) {
        return 0.0;
    }

    double pdf = 0.0;
    const int maxK = 50; // 级数项数上限，可根据需要增加
    double lambda_half = lambda / 2.0;
    double exp_term = exp(-lambda_half); // e^(-λ/2)

    for (int k = 0; k <= maxK; ++k) {
        // 计算 (λ/2)^k / k!
        double poissonTerm = pow(lambda_half, k) / tgamma(k + 1); // Γ(k+1) == k!

        // 计算普通 Beta 分布的 PDF
        double beta_k = betaFunction(a + k, b);
        double term = pow(x, a + k - 1) * pow(1 - x, b - 1) / beta_k;

        pdf += poissonTerm * term;
    }

    return pdf;
}

// 使用梯形规则进行数值积分
double trapezoidalRule(function<double(double)> func, double a, double b, int n) {
    if (n <= 0) return 0.0;

    double h = (b - a) / n;
    double result = 0.0;

    result += func(a) + func(b);
    for (int i = 1; i < n; ++i) {
        result += 2.0 * func(a + i * h);
    }
    result *= h / 2.0;

    return result;
}

// 计算非中心贝塔分布的CDF
double noncentralBetaCDF(double x, double a, double b, double lambda, int numIntervals = 1000) {
    if (x <= 0) return 0.0;
    if (x >= 1) return 1.0;

    return trapezoidalRule(
        [=](double t) { return noncentralBetaPDF(t, a, b, lambda); },
        0.0, x, numIntervals
    );
}

int main() {
    double a, b, lambda, x;

    cout << "Enter the shape parameters a and b: ";
    cin >> a >> b;
    assert(a > 0 && b > 0);

    cout << "Enter the noncentrality parameter lambda: ";
    cin >> lambda;
    assert(lambda >= 0);

    cout << "Enter the value of x (between 0 and 1): ";
    cin >> x;
    assert(x >= 0 && x <= 1);

    double cdfValue = noncentralBetaCDF(x, a, b, lambda);
    cout.precision(8);
    cout << "The CDF of the noncentral Beta distribution at x = " << fixed << x
         << " is: " << scientific << cdfValue << endl;

    return 0;
}
