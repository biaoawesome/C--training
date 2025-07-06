#include <stdio.h>
 
// ���庯�����ڼ���һԪ���η��̵Ķ�����
double calculate_integral(double a, double b, double c, double x1, double x2) {
    // ��������ֵĻ���
    double integral_ax2 = a * (x2 * x2 * x2 / 3.0 - x1 * x1 * x1 / 3.0);
    double integral_bx = b * (x2 * x2 / 2.0 - x1 * x1 / 2.0);
    double integral_c = c * (x2 - x1);
 
    // �ܻ��ֽ��
    return integral_ax2 + integral_bx + integral_c;
}
 
int main() {
    double a, b, c, x1, x2;
 
    // ����һԪ���η��̵�ϵ��a, b, c���Լ���������[x1, x2]
    printf("�����뷽�̵�ϵ�� a, b, c:\n");
    scanf("%lf %lf %lf", &a, &b, &c);
 
    printf("������������� [x1, x2]:\n");
    scanf("%lf %lf", &x1, &x2);
 
    // ���㶨����
    double result = calculate_integral(a, b, c, x1, x2);
 
    // ������
    printf("������ [%.2f, %.2f] �ϣ����� %.2fx^2 + %.2fx + %.2f �Ķ����ֽ��Ϊ��%.2f\n", 
           x1, x2, a, b, c, result);
 
    return 0;
}
