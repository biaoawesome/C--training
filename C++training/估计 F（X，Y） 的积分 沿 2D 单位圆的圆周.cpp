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

// ʾ������ F(x, y) = x^2 + y^2
double exampleFunction(double x, double y) {
    return x * x + y * y;
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
        double x = cos(theta[k]);
        double y = sin(theta[k]);
        integral += weights[k] * exampleFunction(x, y);
    }

    cout << "Approximate integral of F(x, y) = x^2 + y^2: " << integral << "\n";

    return 0;
}
