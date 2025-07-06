#include <iostream>
#include <cmath>

using namespace std;

const int MAX_SIZE = 1024; // ���֧�ֵĽڵ�����������Ҫ������

// ���ɸ�˹-�б�ѩ�� 2 ����������Ļ��ֵ��Ȩ��
void gaussChebyshevType2(int N, double points[], double weights[]) {
    double weight = M_PI / N; // Ȩ������

    for (int k = 0; k < N; ++k) {
        points[k] = cos((2 * k + 1) * M_PI / (2 * N)); // ���ֵ�
        weights[k] = weight;                           // Ȩ��
    }
}

// �������ʽ��ֵ
double polynomial(const double coeffs[], double x, int degree) {
    double result = 0.0;
    double x_power = 1.0;

    for (int i = 0; i <= degree; ++i) {
        result += coeffs[i] * x_power;
        x_power *= x;
    }

    return result;
}

// �������ʽ�ľ�ȷ����ֵ
double exactIntegral(const double coeffs[], int degree) {
    double integral = 0.0;

    for (int i = 0; i <= degree; ++i) {
        if (i % 2 == 0) {
            integral += coeffs[i] * 2.0 / (i + 1); // �������� [-1, 1] �ϻ���Ϊ 0
        }
    }

    return integral;
}

int main() {
    // �������ʽϵ�� P(x) = 1 + 2x + 3x^2
    const int degree = 2;
    double coeffs[MAX_SIZE] = {1.0, 2.0, 3.0};

    // ����ڵ����� N
    int N;
    cout << "Enter the number of nodes (N): ";
    cin >> N;

    if (N <= 0 || N > MAX_SIZE) {
        cerr << "Invalid node count.\n";
        return 1;
    }

    // ���ɻ��ֵ��Ȩ��
    double points[MAX_SIZE];
    double weights[MAX_SIZE];
    gaussChebyshevType2(N, points, weights);

    // �������ʽ�Ļ��ֽ���ֵ
    double approxIntegral = 0.0;
    for (int k = 0; k < N; ++k) {
        approxIntegral += weights[k] * polynomial(coeffs, points[k], degree);
    }

    // �������ʽ�ľ�ȷ����ֵ
    double exactIntegralValue = exactIntegral(coeffs, degree);

    // ������
    cout.precision(10);
    cout << "Approximate integral: " << fixed << approxIntegral << "\n";
    cout << "Exact integral: " << fixed << exactIntegralValue << "\n";
    cout << "Error: " << abs(approxIntegral - exactIntegralValue) << "\n";

    return 0;
}
