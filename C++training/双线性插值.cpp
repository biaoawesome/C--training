#include <stdio.h>
 
// 双线性插值函数
double bilinear_interpolation(double x, double y, 
                               double x1, double y1, double f11, 
                               double x2, double y2, double f12, 
                               double x3, double y3, double f21, 
                               double x4, double y4, double f22) {
    // 计算沿x方向的插值
    double f1 = f11 + (x - x1) * (f12 - f11) / (x2 - x1);
    double f2 = f21 + (x - x1) * (f22 - f21) / (x2 - x1);
 
    // 计算沿y方向的插值
    double result = f1 + (y - y1) * (f2 - f1) / (y2 - y1);
 
    return result;
}
 
int main() {
    // 定义四个已知点
    double x1 = 1, y1 = 1, f11 = 10;
    double x2 = 2, y2 = 1, f12 = 20;
    double x3 = 1, y3 = 2, f21 = 30;
    double x4 = 2, y4 = 2, f22 = 40;
 
    // 目标点
    double x = 1.5, y = 1.5;
 
    // 调用双线性插值函数
    double result = bilinear_interpolation(x, y, x1, y1, f11, x2, y2, f12, x3, y3, f21, x4, y4, f22);
 
    // 输出插值结果
    printf("插值结果 f(%.2f, %.2f) = %.2f\n", x, y, result);
 
    return 0;
}
