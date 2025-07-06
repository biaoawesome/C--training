#include <iostream>
#include <cmath>
#include <complex>

using namespace std;

const int MAX_SIZE = 1024; // 最大支持的数据点数（根据需要调整）

// 快速傅里叶变换（FFT）
void fft(complex<double> x[], int n) {
    if (n <= 1) return;

    // 分治：even/odd 子数组
    complex<double> even[MAX_SIZE], odd[MAX_SIZE];
    for (int i = 0; i < n / 2; ++i) {
        even[i] = x[2 * i];
        odd[i] = x[2 * i + 1];
    }

    fft(even, n / 2);
    fft(odd, n / 2);

    // 合并结果
    for (int k = 0; k < n / 2; ++k) {
        double angle = -2.0 * M_PI * k / n;
        complex<double> t = polar(1.0, angle) * odd[k];
        x[k] = even[k] + t;
        x[k + n / 2] = even[k] - t;
    }
}

// 计算切比雪夫系数
void chebyshevCoefficients(double x[], double f[], double coeffs[], int N) {
    // 初始化 FFT 输入
    complex<double> fftInput[MAX_SIZE];
    for (int j = 0; j < N; ++j) {
        fftInput[j] = complex<double>(f[j]);
    }

    // 执行 FFT
    fft(fftInput, N);

    // 提取切比雪夫系数
    for (int k = 0; k < N; ++k) {
        coeffs[k] = 2.0 * fftInput[k].real() / N;
    }
    coeffs[0] /= 2.0; // 第一个系数需要除以 2
}

// 示例函数 f(x) = x^2
double exampleFunction(double x) {
    return x * x;
}

int main() {
    int N;
    cout << "Enter the number of terms (N): ";
    cin >> N;

    if (N > MAX_SIZE || N <= 0) {
        cerr << "Invalid size.\n";
        return 1;
    }

    double x[MAX_SIZE];         // 切比雪夫节点
    double f[MAX_SIZE];         // 函数值
    double coeffs[MAX_SIZE];    // 切比雪夫系数

    // 生成切比雪夫节点
    for (int j = 0; j < N; ++j) {
        x[j] = cos((2 * j + 1) * M_PI / (2 * N));
    }

    // 计算函数在切比雪夫节点上的值
    for (int j = 0; j < N; ++j) {
        f[j] = exampleFunction(x[j]);
    }

    // 计算切比雪夫系数
    chebyshevCoefficients(x, f, coeffs, N);

    // 输出切比雪夫系数
    cout << "Chebyshev coefficients:\n";
    for (int k = 0; k < N; ++k) {
        cout << "c_" << k << " = " << coeffs[k] << "\n";
    }

    return 0;
}
