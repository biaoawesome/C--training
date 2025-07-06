#include <iostream>
#include <cmath>
#include <complex>

using namespace std;

// ���֧�ֵĽڵ������ɸ�����Ҫ������
const int MAX_SIZE = 1024;

// ���ٸ���Ҷ�任��FFT��
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

// ���ɿ���Ф-�µ�˹��������Ľڵ��Ȩ��
void clenshawCurtis(int N, double nodes[], double weights[]) {
    // �����б�ѩ��ڵ�
    for (int k = 0; k <= N; ++k) {
        nodes[k] = cos(k * M_PI / N);
    }

    // ��ʼ�� FFT ����
    complex<double> f[MAX_SIZE];
    for (int k = 0; k <= N; ++k) {
        f[k] = (k == 0 || k == N) ? 0.5 : 1.0;
    }

    // ִ�� FFT
    fft(f, N + 1);

    // ����Ȩ��
    for (int k = 0; k <= N; ++k) {
        double sum = 0.0;
        for (int j = 0; j <= N; ++j) {
            sum += real(f[j]) * cos(j * k * M_PI / N);
        }
        weights[k] = (2.0 / N) * sum;
    }
}

// ʾ������ f(x) = x^2
double exampleFunction(double x) {
    return x * x;
}

// ������
int main() {
    int N;
    cout << "Enter the number of nodes (N): ";
    cin >> N;

    if (N <= 0 || N > MAX_SIZE) {
        cerr << "Invalid node count.\n";
        return 1;
    }

    // ������̬����
    double nodes[MAX_SIZE + 1];     // �ڵ���Ϊ N+1
    double weights[MAX_SIZE + 1];   // Ȩ����Ϊ N+1

    // ���ɽڵ��Ȩ��
    clenshawCurtis(N, nodes, weights);

    // ����ڵ��Ȩ��
    cout.precision(10);
    cout << fixed;
    cout << "Clenshaw-Curtis nodes and weights:\n";
    for (int k = 0; k <= N; ++k) {
        cout << "Node " << k << ": " << nodes[k] << ", Weight: " << weights[k] << "\n";
    }

    // ������ֽ���ֵ
    double integral = 0.0;
    for (int k = 0; k <= N; ++k) {
        integral += weights[k] * exampleFunction(nodes[k]);
    }

    cout << "Approximate integral of f(x) = x^2: " << integral << "\n";

    return 0;
}
