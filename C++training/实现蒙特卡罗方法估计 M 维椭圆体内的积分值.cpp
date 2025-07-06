#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
#include <chrono>

// �������ά�� M���������������
const int MAX_DIM = 10; // ���֧��ά��

// ���� M ά��Բ��İ��᳤��
const double a[MAX_DIM] = {1.0, 2.0, 3.0}; // ʾ����3 ά��Բ��
const int M = 3; // ʵ��ά�ȣ�ע�ⲻ�ܳ��� MAX_DIM��

// ���屻������ f(x)
double f(const double x[]) {
    double sum = 0.0;
    for (int j = 0; j < M; ++j) {
        sum += x[j] * x[j]; // ʾ��������f(x) = x1^2 + x2^2 + ... + xM^2
    }
    return sum;
}

// ���� M ά��Բ������
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

// �� M ά��Բ�������������
void random_point_in_ellipsoid(double x[], std::mt19937& gen) {
    double normal[MAX_DIM];
    double r_squared = 0.0;

    // ���� M ά��׼��̬�ֲ������
    std::normal_distribution<double> dist(0.0, 1.0);
    for (int j = 0; j < M; ++j) {
        normal[j] = dist(gen);
        r_squared += normal[j] * normal[j];
    }

    double r = sqrt(r_squared);
    double u = pow(std::uniform_real_distribution<double>(0.0, 1.0)(gen), 1.0 / M);

    // ��������㵽��Բ����
    for (int j = 0; j < M; ++j) {
        x[j] = a[j] * normal[j] * u / r;
    }
}

int main() {
    // ��������
    const int N = 1000000; // ��������
    const int seed = std::chrono::system_clock::now().time_since_epoch().count(); // �������
    std::mt19937 gen(seed); // �����������

    // ������Բ�����
    double V = ellipsoid_volume();

    // ���ؿ��޻���
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
    double I = V * mean; // ���ֹ���ֵ
    double variance = (sum_squared / N - mean * mean) / N; // ����
    double error = V * sqrt(variance); // ������

    // ���������ļ�
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
