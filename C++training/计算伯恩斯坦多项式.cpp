#include <iostream>
#include <cmath>
#include <vector>
 
// 计算阶乘
long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}
 
// 计算二项式系数
long long binomialCoefficient(int n, int k) {
    if (k == 0 || k == n) {
        return 1;
    }
    return factorial(n) / (factorial(k) * factorial(n - k));
}
 
// 计算伯恩斯坦多项式 B_n(x)
double bernsteinPolynomial(int n, double x) {
    double result = 0.0;
    
    for (int k = 0; k <= n; ++k) {
        double binom = binomialCoefficient(n, k); // 计算二项式系数
        double term = binom * std::pow(x, k) * std::pow(1 - x, n - k); // 计算每一项
        result += term; // 累加结果
    }
    
    return result;
}
 
int main() {
    int n;  // 多项式的阶数
    double x;  // 自变量值
 
    // 输入阶数和自变量
    std::cout << "Enter the degree of Bernstein polynomial (n): ";
    std::cin >> n;
    std::cout << "Enter the value of x: ";
    std::cin >> x;
 
    // 计算伯恩斯坦多项式
    double result = bernsteinPolynomial(n, x);
 
    // 输出结果
    std::cout << "Bernstein polynomial B_" << n << "(" << x << ") = " << result << std::endl;
 
    return 0;
}
