#include <stdio.h>
#include <math.h>
 
// 定义需要积分的函数 f(x) = x^2
double f(double x) {
    return x * x;
}
 
// 辛普森法则进行数值积分
double simpsons_rule(double (*func)(double), double a, double b, int n) {
    if (n % 2 != 0) {
        n++;  // n 必须为偶数
    }
    
    double h = (b - a) / n;  // 每个小区间的宽度
    double sum = func(a) + func(b);  // 初始值：两端点的贡献
    
    // 累加奇数索引（权重为 4）
    for (int i = 1; i < n; i += 2) {
        sum += 4 * func(a + i * h);
    }
    
    // 累加偶数索引（权重为 2）
    for (int i = 2; i < n - 1; i += 2) {
        sum += 2 * func(a + i * h);
    }
    
    // 计算最终的积分值
    return sum * h / 3;
}
 
int main() {
    double a, b;
    int n;
 
    // 输入积分的区间 [a, b] 和分割数 n（要求 n 为偶数）
    printf("请输入积分的下限 a: ");
    scanf("%lf", &a);
    printf("请输入积分的上限 b: ");
    scanf("%lf", &b);
    printf("请输入划分区间的数量 n（必须为偶数）: ");
    scanf("%d", &n);
 
    // 调用辛普森法则进行积分
    double result = simpsons_rule(f, a, b, n);
    
    // 输出结果
    printf("积分结果是: %.6f\n", result);
    
    return 0;
}
