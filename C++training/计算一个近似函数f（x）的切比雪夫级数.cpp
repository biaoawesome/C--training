#include <iostream>
#include <cmath>
#include <complex>

using namespace std;

const int MAX_SIZE = 1024; // ���֧�ֵ����ݵ�����������Ҫ������

// ���ٸ���Ҷ�任��FFT��
void fft(complex<double> x[], int n) {
    if (n <= 1) return;

    // ���Σ�even/odd ������
    complex<double> even[MAX_SIZE], odd[MAX_SIZE];
    for (int i = 0; i < n / 2; ++i) {
        even[i] = x[2 * i];
        odd[i] = x[2 * i + 1];
    }

    fft(even, n / 2);
    fft(odd, n / 2);

    // �ϲ����
    for (int k = 0; k < n / 2; ++k) {
        double angle = -2.0 * M_PI * k / n;
        complex<double> t = polar(1.0, angle) * odd[k];
        x[k] = even[k] + t;
        x[k + n / 2] = even[k] - t;
    }
}

// �����б�ѩ��ϵ��
void chebyshevCoefficients(double x[], double f[], double coeffs[], int N) {
    // ��ʼ�� FFT ����
    complex<double> fftInput[MAX_SIZE];
    for (int j = 0; j < N; ++j) {
        fftInput[j] = complex<double>(f[j]);
    }

    // ִ�� FFT
    fft(fftInput, N);

    // ��ȡ�б�ѩ��ϵ��
    for (int k = 0; k < N; ++k) {
        coeffs[k] = 2.0 * fftInput[k].real() / N;
    }
    coeffs[0] /= 2.0; // ��һ��ϵ����Ҫ���� 2
}

// ʾ������ f(x) = x^2
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

    double x[MAX_SIZE];         // �б�ѩ��ڵ�
    double f[MAX_SIZE];         // ����ֵ
    double coeffs[MAX_SIZE];    // �б�ѩ��ϵ��

    // �����б�ѩ��ڵ�
    for (int j = 0; j < N; ++j) {
        x[j] = cos((2 * j + 1) * M_PI / (2 * N));
    }

    // ���㺯�����б�ѩ��ڵ��ϵ�ֵ
    for (int j = 0; j < N; ++j) {
        f[j] = exampleFunction(x[j]);
    }

    // �����б�ѩ��ϵ��
    chebyshevCoefficients(x, f, coeffs, N);

    // ����б�ѩ��ϵ��
    cout << "Chebyshev coefficients:\n";
    for (int k = 0; k < N; ++k) {
        cout << "c_" << k << " = " << coeffs[k] << "\n";
    }

    return 0;
}
