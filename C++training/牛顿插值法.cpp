#include <stdio.h>
 
// 函数：计算差商
void compute_divided_difference(double x[], double y[], int n) {
    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            y[i] = (y[i] - y[i - 1]) / (x[i] - x[i - j]);
        }
    }
}
 
// 函数：计算牛顿插值多项式的值
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
    
    // 输入数据点数量
    printf("请输入数据点的数量 n: ");
    scanf("%d", &n);
 
    double x[n], y[n];
 
    // 输入数据点
    printf("请输入数据点的 x 和 y 值:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = ", i);
        scanf("%lf", &x[i]);
        printf("y[%d] = ", i);
        scanf("%lf", &y[i]);
    }
 
    // 计算差商
    compute_divided_difference(x, y, n);
 
    // 输入需要插值的点
    double x_value;
    printf("请输入需要插值的 x 值: ");
    scanf("%lf", &x_value);
 
    // 计算并输出插值结果
    double result = newton_interpolation(x, y, n, x_value);
    printf("插值结果 P(%.2f) = %.6f\n", x_value, result);
 
    return 0;
}
