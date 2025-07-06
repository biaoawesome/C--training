#include <stdio.h>
#include <math.h>
 
// ������Ҫ���ֵĺ��� y = x^2
double f(double x) {
    return x * x;
}
 
// ��˹�������2���˹��
double gaussian_quadrature(double (*func)(double), double a, double b) {
    // ��˹-���õ� 2 ��ڵ��Ȩ��
    double x[2] = {-1.0 / sqrt(3), 1.0 / sqrt(3)};  // �ڵ�
    double w[2] = {1.0, 1.0};  // Ȩ��
 
    // ������ [a, b] ӳ�䵽 [-1, 1]
    double sum = 0.0;
    for (int i = 0; i < 2; i++) {
        double xi = 0.5 * (b - a) * x[i] + 0.5 * (a + b);  // ӳ�䵽 [a, b]
        sum += w[i] * func(xi);  // �ۼ�Ȩ�غͺ���ֵ�ĳ˻�
    }
 
    // ���ػ��ֽ��
    return 0.5 * (b - a) * sum;  // �������䳤�ȵİ�
}
 
int main() {
    double a, b;
 
    // ������ֵ����� [a, b]
    printf("��������ֵ����� a: ");
    scanf("%lf", &a);
    printf("��������ֵ����� b: ");
    scanf("%lf", &b);
 
    // ���ø�˹��������л���
    double result = gaussian_quadrature(f, a, b);
    
    // ������
    printf("���ֽ����: %.6f\n", result);
    
    return 0;
}
