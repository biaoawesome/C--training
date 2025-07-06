#include <iostream>
#include <cmath>

using namespace std;

const int MAX_POINTS = 1024; // ���֧�ֵĵ�����������Ҫ������

// ���ɵ�λԲԲ���ϵ�����������Ȩ��
void generateCircleQuadrature(int N, double theta[], double weights[]) {
    if (N <= 0 || N > MAX_POINTS) return;

    double dTheta = 2.0 * M_PI / N; // �Ƕȼ��
    double weight = dTheta;         // Ȩ��

    for (int k = 0; k < N; ++k) {
        theta[k] = k * dTheta;   // ����
        weights[k] = weight;     // Ȩ��
    }
}

// ʾ������ f(theta) = sin(theta)
double exampleFunction(double theta) {
    return sin(theta);
}

int main() {
    int N;
    cout << "Enter the number of points (N): ";
    cin >> N;

    if (N <= 0 || N > MAX_POINTS) {
        cerr << "Invalid number of points.\n";
        return 1;
    }

    // ������̬����
    double theta[MAX_POINTS];
    double weights[MAX_POINTS];

    // ��������������Ȩ��
    generateCircleQuadrature(N, theta, weights);

    // ������Ȩ��
    cout << "Quadrature points and weights on the unit circle:\n";
    for (int k = 0; k < N; ++k) {
        double x = cos(theta[k]);
        double y = sin(theta[k]);
        cout.precision(10);
        cout << "Point " << k << ": (" << fixed << x << ", " << y << "), "
             << "Theta: " << theta[k] << ", Weight: " << weights[k] << "\n";
    }

    // ������ֽ���ֵ
    double integral = 0.0;
    for (int k = 0; k < N; ++k) {
        integral += weights[k] * exampleFunction(theta[k]);
    }

    cout << "Approximate integral of f(theta) = sin(theta): " << integral << "\n";

    return 0;
}
