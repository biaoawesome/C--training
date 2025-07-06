#include <stdio.h>
#include <math.h>
 
// 定义需要积分的函数 y = x^2
double f(double x) {
    return x * x;
}
 
// 高斯求积法，2点高斯法
double gaussian_quadrature(double (*func)(double), double a, double b) {
    // 高斯-勒让德 2 点节点和权重
    double x[2] = {-1.0 / sqrt(3), 1.0 / sqrt(3)};  // 节点
    double w[2] = {1.0, 1.0};  // 权重
 
    // 将区间 [a, b] 映射到 [-1, 1]
    double sum = 0.0;
    for (int i = 0; i < 2; i++) {
        double xi = 0.5 * (b - a) * x[i] + 0.5 * (a + b);  // 映射到 [a, b]
        sum += w[i] * func(xi);  // 累加权重和函数值的乘积
    }
 
    // 返回积分结果
    return 0.5 * (b - a) * sum;  // 乘以区间长度的半
}
 
int main() {
    double a, b;
 
    // 输入积分的区间 [a, b]
    printf("请输入积分的下限 a: ");
    scanf("%lf", &a);
    printf("请输入积分的上限 b: ");
    scanf("%lf", &b);
 
    // 调用高斯求积法进行积分
    double result = gaussian_quadrature(f, a, b);
    
    // 输出结果
    printf("积分结果是: %.6f\n", result);
    
    return 0;
}
