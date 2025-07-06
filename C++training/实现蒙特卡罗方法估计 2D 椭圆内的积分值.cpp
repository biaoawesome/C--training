#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include <chrono>
 
// 定义椭圆的长半轴和短半轴
const double a = 2.0; // 长半轴
const double b = 1.0; // 短半轴
 
// 定义被积函数 f(x, y)
double f(double x, double y) {
    return x * x + y * y; // 示例函数：f(x, y) = x^2 + y^2
}
 
// 计算椭圆的面积
double ellipse_area() {
    return M_PI * a * b;
}
 
// 在椭圆内生成随机点
std::pair<double, double> random_point_in_ellipse(std::mt19937& gen) {
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
 
    double x, y;
    do {
        x = dist(gen);
        y = dist(gen);
    } while ((x * x) / (a * a) + (y * y) / (b * b) > 1.0); // 拒绝采样法
 
    return {x, y};
}
 
int main() {
    // 参数设置
    const int N = 1000000; // 采样点数
    const int seed = std::chrono::system_clock::now().time_since_epoch().count(); // 随机种子
    std::mt19937 gen(seed); // 随机数生成器
 
    // 计算椭圆面积
    double V = ellipse_area();
 
    // 蒙特卡罗积分
    double sum = 0.0;
    double sum_squared = 0.0;
 
    for (int i = 0; i < N; ++i) {
        auto [x, y] = random_point_in_ellipse(gen);
        double fx = f(x, y);
        sum += fx;
        sum_squared += fx * fx;
    }
 
    double I = V * sum / N; // 积分估计值
    double variance = (sum_squared / N - std::pow(sum / N, 2)) / N; // 方差
    double error = V * std::sqrt(variance); // 误差估计
 
    // 输出结果
    std::ofstream output_file("monte_carlo_result.txt");
    if (!output_file.is_open()) {
        std::cerr << "Failed to open output file!" << std::endl;
        return 1;
    }
 
    output_file << "Integral estimate: " << I << std::endl;
    output_file << "Estimated error: " << error << std::endl;
    output_file.close();
 
    std::cout << "Monte Carlo integration completed! Check the result in monte_carlo_result.txt" << std::endl;
 
    return 0;
}
