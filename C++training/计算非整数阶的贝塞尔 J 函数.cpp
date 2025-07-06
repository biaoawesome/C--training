#include <iostream>
#include <cmath>
#include <limits>
 
using namespace std;
 
// 计算阶乘函数
double factorial(int n) {
    double result = 1.0;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}
 
// 计算Gamma函数
double gamma(double x) {
    if (x == 0.5) return sqrt(M_PI);
    double result = 1.0;
    for (int i = 1; i < 100; ++i) {
        result *= (x + i - 1);
    }
    return result;
}
 
// 计算贝塞尔函数的级数展开
double besselJ(double nu, double x) {
    double sum = 0.0;
    double term;
    int k = 0;
    do {
        term = pow(-1, k) * pow(x / 2, 2 * k + nu) / (factorial(k) * gamma(nu + k + 1));
        sum += term;
        k++;
    } while (fabs(term) > 1e-10);  // 精度阈值控制
    return sum;
}
 
// 使用递推公式计算贝塞尔函数
double besselJ_recursive(double nu, double x) {
    if (nu == 0) {
        return sin(x) / x;
    }
    double j0 = sin(x) / x;
    double j1 = (sin(x) - x * cos(x)) / (x * x);
    double jnu_minus1 = j0;
    double jnu = j1;
    
    for (int n = 2; n <= static_cast<int>(nu); ++n) {
        double jnu_plus1 = (2 * n - 1) / x * jnu - jnu_minus1;
        jnu_minus1 = jnu;
        jnu = jnu_plus1;
    }
    return jnu;
}
 
int main() {
    double nu, x;
    cout << "Enter the order of Bessel function (nu): ";
    cin >> nu;
    cout << "Enter the value of x: ";
    cin >> x;
 
    // 计算贝塞尔函数值
    double result = besselJ(nu, x);
    cout << "Bessel J(" << nu << ", " << x << ") = " << result << endl;
 
    return 0;
}
