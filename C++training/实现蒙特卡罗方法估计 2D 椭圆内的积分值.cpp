#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include <chrono>
 
// ������Բ�ĳ�����Ͷ̰���
const double a = 2.0; // ������
const double b = 1.0; // �̰���
 
// ���屻������ f(x, y)
double f(double x, double y) {
    return x * x + y * y; // ʾ��������f(x, y) = x^2 + y^2
}
 
// ������Բ�����
double ellipse_area() {
    return M_PI * a * b;
}
 
// ����Բ�����������
std::pair<double, double> random_point_in_ellipse(std::mt19937& gen) {
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
 
    double x, y;
    do {
        x = dist(gen);
        y = dist(gen);
    } while ((x * x) / (a * a) + (y * y) / (b * b) > 1.0); // �ܾ�������
 
    return {x, y};
}
 
int main() {
    // ��������
    const int N = 1000000; // ��������
    const int seed = std::chrono::system_clock::now().time_since_epoch().count(); // �������
    std::mt19937 gen(seed); // �����������
 
    // ������Բ���
    double V = ellipse_area();
 
    // ���ؿ��޻���
    double sum = 0.0;
    double sum_squared = 0.0;
 
    for (int i = 0; i < N; ++i) {
        auto [x, y] = random_point_in_ellipse(gen);
        double fx = f(x, y);
        sum += fx;
        sum_squared += fx * fx;
    }
 
    double I = V * sum / N; // ���ֹ���ֵ
    double variance = (sum_squared / N - std::pow(sum / N, 2)) / N; // ����
    double error = V * std::sqrt(variance); // ������
 
    // ������
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
