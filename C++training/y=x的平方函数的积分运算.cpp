#include <iostream>
#include <cmath>
 
// ������Ҫ���ֵĺ��� y = x^2
double f(double x) {
    return x * x;
}
 
// ���η��������ֵ����
double trapezoidal_rule(double (*func)(double), double a, double b, int n) {
    double h = (b - a) / n;  // ÿ��С����Ŀ��
    double sum = (func(a) + func(b)) / 2.0;  // ��ʼֵ�����˵�Ĺ���
    
    // �ۼ��м䲿�ֵ��������
    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += func(x);
    }
    
    // �������յĻ���ֵ
    return sum * h;
}
 
int main() {
    double a, b;
    int n;
 
    // ������ֵ����� [a, b] �ͷָ��� n
    std::cout << "��������ֵ����� a: ";
    std::cin >> a;
    std::cout << "��������ֵ����� b: ";
    std::cin >> b;
    std::cout << "�����뻮����������� n: ";
    std::cin >> n;
 
    // �������η�����л���
    double result = trapezoidal_rule(f, a, b, n);
    
    // ������
    std::cout << "���ֽ����: " << result << std::endl;
    
    return 0;
}
