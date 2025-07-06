#include <iostream>
#include <cmath>
 
// 定义需要积分的函数 y = x^2
double f(double x) {
    return x * x;
}
 
// 梯形法则进行数值积分
double trapezoidal_rule(double (*func)(double), double a, double b, int n) {
    double h = (b - a) / n;  // 每个小区间的宽度
    double sum = (func(a) + func(b)) / 2.0;  // 初始值：两端点的贡献
    
    // 累加中间部分的梯形面积
    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += func(x);
    }
    
    // 计算最终的积分值
    return sum * h;
}
 
int main() {
    double a, b;
    int n;
 
    // 输入积分的区间 [a, b] 和分割数 n
    std::cout << "请输入积分的下限 a: ";
    std::cin >> a;
    std::cout << "请输入积分的上限 b: ";
    std::cin >> b;
    std::cout << "请输入划分区间的数量 n: ";
    std::cin >> n;
 
    // 调用梯形法则进行积分
    double result = trapezoidal_rule(f, a, b, n);
    
    // 输出结果
    std::cout << "积分结果是: " << result << std::endl;
    
    return 0;
}
