#include <iostream>
#include <cmath>

using namespace std;

const int MAX_GAUSS_POINTS = 3; // ���֧�ֵĻ��ֵ���

// ��˹-���õ���������Ļ��ֵ��Ȩ��
void gaussLegendre(int n, double points[], double weights[]) {
    switch (n) {
        case 1:
            if (n > MAX_GAUSS_POINTS) return;
            points[0] = 0.0;
            weights[0] = 2.0;
            break;
        case 2:
            if (n > MAX_GAUSS_POINTS) return;
            points[0] = -0.5773502691896257;
            points[1] = 0.5773502691896257;
            weights[0] = 1.0;
            weights[1] = 1.0;
            break;
        case 3:
            if (n > MAX_GAUSS_POINTS) return;
            points[0] = -0.7745966692414834;
            points[1] = 0.0;
            points[2] = 0.7745966692414834;
            weights[0] = 0.5555555555555556;
            weights[1] = 0.8888888888888888;
            weights[2] = 0.5555555555555556;
            break;
        default:
            cerr << "Unsupported number of points for Gauss-Legendre quadrature.\n";
            exit(1);
    }
}

// ������ֵ����
double cauchyPrincipalValue(double a, double b, double c,
                            const double points[], const double weights[], int n,
                            double (*f)(double)) {
    double integral = 0.0;

    // ӳ�亯���������� [a, b] ӳ�䵽 [-1, 1]
    auto mapToUnitInterval = [a, b](double x) {
        return 0.5 * (b - a) * x + 0.5 * (a + b);
    };

    // �������
    for (int k = 0; k < n; ++k) {
        double x = mapToUnitInterval(points[k]);
        if (fabs(x - c) > 1e-10) { // �������
            integral += weights[k] * f(x) / (x - c);
        }
    }

    // ����ӳ����ſɱ�����ʽ
    integral *= 0.5 * (b - a);

    return integral;
}

// ʾ������ f(x) = x^2
double exampleFunction(double x) {
    return x * x;
}

int main() {
    // ���������������
    double a, b, c;
    cout << "Enter the interval [a, b]: ";
    cin >> a >> b;
    cout << "Enter the singularity point c: ";
    cin >> c;

    // ���ɸ�˹-���õ���������Ļ��ֵ��Ȩ��
    int n = 3; // ʹ�� 3 ����
    double points[MAX_GAUSS_POINTS];
    double weights[MAX_GAUSS_POINTS];

    gaussLegendre(n, points, weights);

    // ���������ֵ����
    double cpv = cauchyPrincipalValue(a, b, c, points, weights, n, exampleFunction);

    // ������
    cout << "Cauchy Principal Value: " << cpv << "\n";

    return 0;
}
