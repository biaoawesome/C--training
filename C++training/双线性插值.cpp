#include <stdio.h>
 
// ˫���Բ�ֵ����
double bilinear_interpolation(double x, double y, 
                               double x1, double y1, double f11, 
                               double x2, double y2, double f12, 
                               double x3, double y3, double f21, 
                               double x4, double y4, double f22) {
    // ������x����Ĳ�ֵ
    double f1 = f11 + (x - x1) * (f12 - f11) / (x2 - x1);
    double f2 = f21 + (x - x1) * (f22 - f21) / (x2 - x1);
 
    // ������y����Ĳ�ֵ
    double result = f1 + (y - y1) * (f2 - f1) / (y2 - y1);
 
    return result;
}
 
int main() {
    // �����ĸ���֪��
    double x1 = 1, y1 = 1, f11 = 10;
    double x2 = 2, y2 = 1, f12 = 20;
    double x3 = 1, y3 = 2, f21 = 30;
    double x4 = 2, y4 = 2, f22 = 40;
 
    // Ŀ���
    double x = 1.5, y = 1.5;
 
    // ����˫���Բ�ֵ����
    double result = bilinear_interpolation(x, y, x1, y1, f11, x2, y2, f12, x3, y3, f21, x4, y4, f22);
 
    // �����ֵ���
    printf("��ֵ��� f(%.2f, %.2f) = %.2f\n", x, y, result);
 
    return 0;
}
