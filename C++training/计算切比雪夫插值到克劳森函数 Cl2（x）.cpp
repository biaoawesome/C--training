#include <iostream>
#include <cmath>
#include <complex>

using namespace std;

const int MAX_SIZE = 1024; // 最大支持的数据点数

// 快速傅里叶变换（FFT）
void fft(complex<double> x[], int N) {
    if (N <= 1) return;

    complex<double> even[MAX_SIZE], odd[MAX_SIZE];
    for (int i = 0; i < N / 2; ++i) {
        even[i] = x[2 * i];
        odd[i] = x[2 * i + 1];
    }

    fft(even, N / 2);
    fft(odd, N / 2);

    for (int k = 0; k < N / 2; ++k) {
        complex<double> t = polar(1.0, -2.0 * M_PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N / 2] = even[k] - t;
    }
}

// 计算克劳森函数 Cl2(x)
double clausenFunction(double x) {
    const int maxTerms = 1000;
    double result = 0.0;
    for (int k = 1; k <= maxTerms; ++k) {
        result += sin(k * x) / (k * k);
    }
    return result;
}

// 生成切比雪夫节点
void chebyshevNodes(int N, double nodes[]) {
    for (int k = 0; k < N; ++k) {
        nodes[k] = cos((2 * k + 1) * M_PI / (2 * N));
    }
}

// 切比雪夫插值
void chebyshevInterpolation(const double nodes[], const double values[], int N, double coefficients[]) {
    complex<double> f[MAX_SIZE];

    for (int k = 0; k < N; ++k) {
        f[k] = values[k];
    }

    fft(f, N);

    for (int k = 0; k < N; ++k) {
        coefficients[k] = 2.0 * f[k].real() / N;
    }
    coefficients[0] /= 2.0; // 第一个系数需要除以 2
}

// 计算切比雪夫插值结果
double evaluateChebyshevPolynomial(double x, const double coefficients[], int degree) {
    double result = 0.0;
    double T_prev = 1.0; // T_0(x) = 1
    double T_curr = x;   // T_1(x) = x

    result += coefficients[0] * T_prev;

    for (int k = 1; k <= degree; ++k) {
        result += coefficients[k] * T_curr;

        // 递推计算切比雪夫多项式
        double T_next = 2 * x * T_curr - T_prev;
        T_prev = T_curr;
        T_curr = T_next;
    }

    return result;
}

int main() {
    int N;
    cout << "Enter the number of Chebyshev nodes (N): ";
    cin >> N;

    if (N <= 0 || N > MAX_SIZE) {
        cerr << "Invalid node count.\n";
        return 1;
    }

    // 声明静态数组
    double nodes[MAX_SIZE];
    double values[MAX_SIZE];
    double coefficients[MAX_SIZE];

    // 生成切比雪夫节点
    chebyshevNodes(N, nodes);

    // 计算克劳森函数在节点上的值
    for (int k = 0; k < N; ++k) {
        double x = (nodes[k] + 1) * M_PI / 2; // 映射到 [0, pi]
        values[k] = clausenFunction(x);
    }

    // 计算切比雪夫系数
    chebyshevInterpolation(nodes, values, N, coefficients);

    // 测试插值结果
    double testX = 0.5;                         // 测试点
    double mappedX = 2 * testX / M_PI - 1;      // 映射到 [-1, 1]
    double interpolatedValue = evaluateChebyshevPolynomial(mappedX, coefficients, N - 1);
    double exactValue = clausenFunction(testX);

    cout.precision(10);
    cout << fixed;
    cout << "Interpolated value at x = " << testX << ": " << interpolatedValue << "\n";
    cout << "Exact value at x = " << testX << ": " << exactValue << "\n";
    cout << "Error: " << abs(interpolatedValue - exactValue) << "\n";

    return 0;
}
