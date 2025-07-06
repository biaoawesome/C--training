#include <iostream>
#include <cmath>
#include <vector>
 
// ����׳�
long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}
 
// �������ʽϵ��
long long binomialCoefficient(int n, int k) {
    if (k == 0 || k == n) {
        return 1;
    }
    return factorial(n) / (factorial(k) * factorial(n - k));
}
 
// ���㲮��˹̹����ʽ B_n(x)
double bernsteinPolynomial(int n, double x) {
    double result = 0.0;
    
    for (int k = 0; k <= n; ++k) {
        double binom = binomialCoefficient(n, k); // �������ʽϵ��
        double term = binom * std::pow(x, k) * std::pow(1 - x, n - k); // ����ÿһ��
        result += term; // �ۼӽ��
    }
    
    return result;
}
 
int main() {
    int n;  // ����ʽ�Ľ���
    double x;  // �Ա���ֵ
 
    // ����������Ա���
    std::cout << "Enter the degree of Bernstein polynomial (n): ";
    std::cin >> n;
    std::cout << "Enter the value of x: ";
    std::cin >> x;
 
    // ���㲮��˹̹����ʽ
    double result = bernsteinPolynomial(n, x);
 
    // ������
    std::cout << "Bernstein polynomial B_" << n << "(" << x << ") = " << result << std::endl;
 
    return 0;
}
