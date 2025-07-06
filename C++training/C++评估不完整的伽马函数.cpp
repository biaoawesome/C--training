#include <iostream>
#include <cmath>
#include <functional>
 
// ����٤�������²���ȫ����
double incompleteGamma(double a, double x) {
    // ��ֵ���ֵľ���
    const int numIntervals = 1000000; // ������
    double step = x / numIntervals;
    double sum = 0.0;
 
    // ���η��������ֵ����
    for (int i = 0; i < numIntervals; ++i) {
        double t1 = i * step;
        double t2 = (i + 1) * step;
        
        // �������η����е������˵�ֵ
        double f_t1 = pow(t1, a - 1) * exp(-t1);
        double f_t2 = pow(t2, a - 1) * exp(-t2);
 
        // �ۼ����η���Ĺ���
        sum += (f_t1 + f_t2) * step / 2.0;
    }
 
    return sum;
}
 
int main() {
    // ��ȡ�û�����
    double a, x;
    std::cout << "Enter a and x for the incomplete gamma function (a > 0, x >= 0):" << std::endl;
    std::cin >> a >> x;
 
    if (a <= 0 || x < 0) {
        std::cout << "Invalid input! a must be greater than 0, and x must be non-negative." << std::endl;
        return 1;
    }
 
    // �����²���ȫ٤����
    double result = incompleteGamma(a, x);
 
    // ������
    std::cout << "Incomplete Gamma Function ��(" << a << ", " << x << ") = " << result << std::endl;
 
    return 0;
}
