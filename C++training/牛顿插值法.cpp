#include <stdio.h>
 
// �������������
void compute_divided_difference(double x[], double y[], int n) {
    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            y[i] = (y[i] - y[i - 1]) / (x[i] - x[i - j]);
        }
    }
}
 
// ����������ţ�ٲ�ֵ����ʽ��ֵ
double newton_interpolation(double x[], double y[], int n, double x_value) {
    double result = y[0];
    double term = 1.0;
 
    for (int i = 1; i < n; i++) {
        term *= (x_value - x[i - 1]);
        result += term * y[i];
    }
 
    return result;
}
 
int main() {
    int n;
    
    // �������ݵ�����
    printf("���������ݵ������ n: ");
    scanf("%d", &n);
 
    double x[n], y[n];
 
    // �������ݵ�
    printf("���������ݵ�� x �� y ֵ:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = ", i);
        scanf("%lf", &x[i]);
        printf("y[%d] = ", i);
        scanf("%lf", &y[i]);
    }
 
    // �������
    compute_divided_difference(x, y, n);
 
    // ������Ҫ��ֵ�ĵ�
    double x_value;
    printf("��������Ҫ��ֵ�� x ֵ: ");
    scanf("%lf", &x_value);
 
    // ���㲢�����ֵ���
    double result = newton_interpolation(x, y, n, x_value);
    printf("��ֵ��� P(%.2f) = %.6f\n", x_value, result);
 
    return 0;
}
