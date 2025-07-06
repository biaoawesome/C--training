#include <stdio.h>
#include <math.h>
 
// ������Ҫ���ֵĺ��� f(x) = x^2
double f(double x) {
    return x * x;
}
 
// ����ɭ���������ֵ����
double simpsons_rule(double (*func)(double), double a, double b, int n) {
    if (n % 2 != 0) {
        n++;  // n ����Ϊż��
    }
    
    double h = (b - a) / n;  // ÿ��С����Ŀ��
    double sum = func(a) + func(b);  // ��ʼֵ�����˵�Ĺ���
    
    // �ۼ�����������Ȩ��Ϊ 4��
    for (int i = 1; i < n; i += 2) {
        sum += 4 * func(a + i * h);
    }
    
    // �ۼ�ż��������Ȩ��Ϊ 2��
    for (int i = 2; i < n - 1; i += 2) {
        sum += 2 * func(a + i * h);
    }
    
    // �������յĻ���ֵ
    return sum * h / 3;
}
 
int main() {
    double a, b;
    int n;
 
    // ������ֵ����� [a, b] �ͷָ��� n��Ҫ�� n Ϊż����
    printf("��������ֵ����� a: ");
    scanf("%lf", &a);
    printf("��������ֵ����� b: ");
    scanf("%lf", &b);
    printf("�����뻮����������� n������Ϊż����: ");
    scanf("%d", &n);
 
    // ��������ɭ������л���
    double result = simpsons_rule(f, a, b, n);
    
    // ������
    printf("���ֽ����: %.6f\n", result);
    
    return 0;
}
