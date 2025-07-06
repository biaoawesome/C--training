#include <iostream>
#include <cmath>
 
// 定义方程 F(x) = 0, 例如 F(x) = x^3 - x - 2
double F(double x) {
    return x * x * x - x - 2;
}
 
// 平分法求解方程 F(x) = 0
double bisectionMethod(double a, double b, double epsilon) {
    // 检查初始区间是否满足 F(a) * F(b) < 0
    if (F(a) * F(b) > 0) {
        std::cerr << "Initial interval does not satisfy the condition F(a) * F(b) < 0." << std::endl;
        return NAN;
    }
 
    double c = a; // 中点
    while ((b - a) / 2.0 > epsilon) {
        c = (a + b) / 2.0; // 计算中点
        if (F(c) == 0.0) {
            break; // 找到精确的根
        }
        // 根据符号选择新的区间
        else if (F(a) * F(c) < 0) {
            b = c;
        } else {
            a = c;
        }
    }
    return c;
}
 
int main() {
    // 设定初始区间和容忍度
    double a = 1.0, b = 2.0;
    double epsilon = 0.0001;
 
    // 调用平分法函数求解根
    double root = bisectionMethod(a, b, epsilon);
 
    // 输出结果
    if (!std::isnan(root)) {
        std::cout << "The root of the equation is approximately: " << root << std::endl;
    }
 
    return 0;
}
