#include <iostream>
#include <cmath>

using namespace std;

const int MAX_SIZE = 1024; // ���֧�ֵĽڵ�����������Ҫ������

// ���ɸ�˹-�б�ѩ�� 1 ����������Ļ��ֵ��Ȩ��
void gaussChebyshevType1(int N, double points[], double weights[]) {
    double weightFactor = M_PI / N; // Ȩ������

    for (int k = 0; k < N; ++k) {
        double theta = (2 * k + 1) * M_PI / (2 * N); // ����
        points[k] = cos(theta);                      // ���ֵ�
        weights[k] = weightFactor * sin(theta);       // Ȩ��
    }
}

// ʾ������ f(x) = x^2
double exampleFunction(double x) {
    return x * x;
}

int main() {
    int N;
    cout << "Enter the number of nodes (N): ";
    cin >> N;

    if (N <= 0 || N > MAX_SIZE) {
        cerr << "Invalid node count.\n";
        return 1;
    }

    double points[MAX_SIZE];   // �洢���ֵ�
    double weights[MAX_SIZE];  // �洢Ȩ��

    // ���ɻ��ֵ��Ȩ��
    gaussChebyshevType1(N, points, weights);

    // ������ֵ��Ȩ��
    cout << "Gauss-Chebyshev Type 1 points and weights:\n";
    for (int k = 0; k < N; ++k) {
        cout.precision(10);
        cout << "Point " << k << ": " << fixed << points[k]
             << ", Weight: " << weights[k] << "\n";
    }

    // ������ֽ���ֵ
    double integral = 0.0;
    for (int k = 0; k < N; ++k) {
        integral += weights[k] * exampleFunction(points[k]);
    }

    cout << "Approximate integral of f(x) = x^2: " << integral << "\n";

    return 0;
}
