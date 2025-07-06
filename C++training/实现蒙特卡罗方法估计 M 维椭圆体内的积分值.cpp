#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
#include <chrono>

// 设置最大维度 M（根据需求调整）
const int MAX_DIM = 10; // 最大支持维度

// 定义 M 维椭圆体的半轴长度
const double a[MAX_DIM] = {1.0, 2.0, 3.0}; // 示例：3 维椭圆体
const int M = 3; // 实际维度（注意不能超过 MAX_DIM）

// 定义被积函数 f(x)
double f(const double x[]) {
    double sum = 0.0;
    for (int j = 0; j < M; ++j) {
        sum += x[j] * x[j]; // 示例函数：f(x) = x1^2 + x2^2 + ... + xM^2
    }
    return sum;
}

// 计算 M 维椭圆体的体积
double ellipsoid_volume() {
    double volume = 1.0;
    for (int j = 0; j < M; ++j) {
        volume *= a[j];
    }

    // Gamma(M / 2 + 1)
    double gamma = tgamma(M / 2.0 + 1.0);
    volume *= pow(M_PI, M / 2.0) / gamma;

    return volume;
}

// 在 M 维椭圆体内生成随机点
void random_point_in_ellipsoid(double x[], std::mt19937& gen) {
    double normal[MAX_DIM];
    double r_squared = 0.0;

    // 生成 M 维标准正态分布随机点
    std::normal_distribution<double> dist(0.0, 1.0);
    for (int j = 0; j < M; ++j) {
        normal[j] = dist(gen);
        r_squared += normal[j] * normal[j];
    }

    double r = sqrt(r_squared);
    double u = pow(std::uniform_real_distribution<double>(0.0, 1.0)(gen), 1.0 / M);

    // 缩放随机点到椭圆体内
    for (int j = 0; j < M; ++j) {
        x[j] = a[j] * normal[j] * u / r;
    }
}

int main() {
    // 参数设置
    const int N = 1000000; // 采样点数
    const int seed = std::chrono::system_clock::now().time_since_epoch().count(); // 随机种子
    std::mt19937 gen(seed); // 随机数生成器

    // 计算椭圆体体积
    double V = ellipsoid_volume();

    // 蒙特卡罗积分
    double sum = 0.0;
    double sum_squared = 0.0;

    double x[MAX_DIM];

    for (int i = 0; i < N; ++i) {
        random_point_in_ellipsoid(x, gen);
        double fx = f(x);
        sum += fx;
        sum_squared += fx * fx;
    }

    double mean = sum / N;
    double I = V * mean; // 积分估计值
    double variance = (sum_squared / N - mean * mean) / N; // 方差
    double error = V * sqrt(variance); // 误差估计

    // 输出结果到文件
    std::ofstream output_file("monte_carlo_result.txt");
    if (!output_file.is_open()) {
        std::cerr << "Failed to open output file!" << std::endl;
        return 1;
    }

    output_file.precision(15);
    output_file << "Integral estimate: " << I << std::endl;
    output_file << "Estimated error: " << error << std::endl;
    output_file.close();

    std::cout << "Monte Carlo integration completed! Check the result in monte_carlo_result.txt" << std::endl;

    return 0;
}
