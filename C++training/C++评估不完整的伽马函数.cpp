#include <iostream>
#include <cmath>
#include <functional>
 
// 定义伽马函数的下不完全函数
double incompleteGamma(double a, double x) {
    // 数值积分的精度
    const int numIntervals = 1000000; // 分区数
    double step = x / numIntervals;
    double sum = 0.0;
 
    // 梯形法则进行数值积分
    for (int i = 0; i < numIntervals; ++i) {
        double t1 = i * step;
        double t2 = (i + 1) * step;
        
        // 计算梯形法则中的两个端点值
        double f_t1 = pow(t1, a - 1) * exp(-t1);
        double f_t2 = pow(t2, a - 1) * exp(-t2);
 
        // 累加梯形法则的贡献
        sum += (f_t1 + f_t2) * step / 2.0;
    }
 
    return sum;
}
 
int main() {
    // 获取用户输入
    double a, x;
    std::cout << "Enter a and x for the incomplete gamma function (a > 0, x >= 0):" << std::endl;
    std::cin >> a >> x;
 
    if (a <= 0 || x < 0) {
        std::cout << "Invalid input! a must be greater than 0, and x must be non-negative." << std::endl;
        return 1;
    }
 
    // 计算下不完全伽马函数
    double result = incompleteGamma(a, x);
 
    // 输出结果
    std::cout << "Incomplete Gamma Function γ(" << a << ", " << x << ") = " << result << std::endl;
 
    return 0;
}
