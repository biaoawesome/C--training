#include <stdio.h>
 
// 定义函数用于计算一元二次方程的定积分
double calculate_integral(double a, double b, double c, double x1, double x2) {
    // 计算各部分的积分
    double integral_ax2 = a * (x2 * x2 * x2 / 3.0 - x1 * x1 * x1 / 3.0);
    double integral_bx = b * (x2 * x2 / 2.0 - x1 * x1 / 2.0);
    double integral_c = c * (x2 - x1);
 
    // 总积分结果
    return integral_ax2 + integral_bx + integral_c;
}
 
int main() {
    double a, b, c, x1, x2;
 
    // 输入一元二次方程的系数a, b, c，以及积分区间[x1, x2]
    printf("请输入方程的系数 a, b, c:\n");
    scanf("%lf %lf %lf", &a, &b, &c);
 
    printf("请输入积分区间 [x1, x2]:\n");
    scanf("%lf %lf", &x1, &x2);
 
    // 计算定积分
    double result = calculate_integral(a, b, c, x1, x2);
 
    // 输出结果
    printf("在区间 [%.2f, %.2f] 上，方程 %.2fx^2 + %.2fx + %.2f 的定积分结果为：%.2f\n", 
           x1, x2, a, b, c, result);
 
    return 0;
}
