#include <iostream>
#include <cmath>

using namespace std;

// �������֧�ֵĻ��ֵ���
const int MAX_POINTS = 1024;

// ����� n �����õ¶���ʽ P_n(x)
double legendre(int n, double x) {
    if (n == 0) {
        return 1.0;
    } else if (n == 1) {
        return x;
    } else {
        return ((2 * n - 1) * x * legendre(n - 1, x) - (n - 1) * legendre(n - 2, x)) / n;
    }
}

// ����� n �����õ¶���ʽ�ĵ��� P'_n(x)
double legendre_derivative(int n, double x) {
    if (n == 0) {
        return 0.0;
    } else if (n == 1) {
        return 1.0;
    } else {
        return (n * (legendre(n - 1, x) - x * legendre(n, x))) / (1 - x * x);
    }
}

// ���� N ���˹-���õ»��ֵ��Ȩ��
void gauss_legendre(int N, double x[], double w[]) {
    const double eps = 1e-15;
    const int max_iter = 100;

    for (int i = 0; i < N; ++i) {
        double z = cos(M_PI * (i + 0.75) / (N + 0.5));
        double z1;

        for (int iter = 0; iter < max_iter; ++iter) {
            double p1 = 1.0;
            double p2 = 0.0;

            for (int j = 0; j < N; ++j) {
                double p3 = p2;
                p2 = p1;
                p1 = ((2 * j + 1) * z * p2 - j * p3) / (j + 1);
            }

            double pp = N * (z * p1 - p2) / (z * z - 1);
            z1 = z;
            z = z1 - p1 / pp;

            if (fabs(z - z1) < eps) {
                break;
            }
        }

        x[i] = z;
        w[i] = 2.0 / ((1.0 - z * z) * pow(legendre_derivative(N, z), 2));
    }
}

// ʾ���������� f(x)
double f(double x) {
    return sin(x); // ʾ������������ [-1, 1]
}

// �����ֽ���ֵ
double integrate(int N, const double x[], const double w[], double (*func)(double)) {
    double sum = 0.0;
    for (int i = 0; i < N; ++i) {
        sum += w[i] * func(x[i]);
    }
    return sum;
}

// ������
int main() {
    int N;
    cout << "Enter number of Gauss-Legendre quadrature points (N): ";
    cin >> N;

    if (N <= 0 || N > MAX_POINTS) {
        cerr << "Invalid number of points. Must be between 1 and " << MAX_POINTS << endl;
        return 1;
    }

    double x[MAX_POINTS]; // ���ֵ�
    double w[MAX_POINTS]; // Ȩ��

    // ���ɻ��ֵ��Ȩ��
    gauss_legendre(N, x, w);

    // �������
    double result = integrate(N, x, w, f);

    // ������
    cout.precision(15);
    cout << fixed;
    cout << "Integral value: " << result << endl;

    return 0;
}
