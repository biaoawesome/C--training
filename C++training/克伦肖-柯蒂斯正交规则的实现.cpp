#include <iostream>
#include <cmath>
#include <complex>

using namespace std;

// 最大支持的节点数（可根据需要调整）
const int MAX_SIZE = 1024;

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

// 生成克伦肖-柯蒂斯正交规则的节点和权重
void clenshawCurtis(int N, double nodes[], double weights[]) {
    // 生成切比雪夫节点
    for (int k = 0; k <= N; ++k) {
        nodes[k] = cos(k * M_PI / N);
    }

    // 初始化 FFT 输入
    complex<double> f[MAX_SIZE];
    for (int k = 0; k <= N; ++k) {
        f[k] = (k == 0 || k == N) ? 0.5 : 1.0;
    }

    // 执行 FFT
    fft(f, N + 1);

    // 计算权重
    for (int k = 0; k <= N; ++k) {
        double sum = 0.0;
        for (int j = 0; j <= N; ++j) {
            sum += real(f[j]) * cos(j * k * M_PI / N);
        }
        weights[k] = (2.0 / N) * sum;
    }
}

// 示例函数 f(x) = x^2
double exampleFunction(double x) {
    return x * x;
}

// 主函数
int main() {
    int N;
    cout << "Enter the number of nodes (N): ";
    cin >> N;

    if (N <= 0 || N > MAX_SIZE) {
        cerr << "Invalid node count.\n";
        return 1;
    }

    // 声明静态数组
    double nodes[MAX_SIZE + 1];     // 节点数为 N+1
    double weights[MAX_SIZE + 1];   // 权重数为 N+1

    // 生成节点和权重
    clenshawCurtis(N, nodes, weights);

    // 输出节点和权重
    cout.precision(10);
    cout << fixed;
    cout << "Clenshaw-Curtis nodes and weights:\n";
    for (int k = 0; k <= N; ++k) {
        cout << "Node " << k << ": " << nodes[k] << ", Weight: " << weights[k] << "\n";
    }

    // 计算积分近似值
    double integral = 0.0;
    for (int k = 0; k <= N; ++k) {
        integral += weights[k] * exampleFunction(nodes[k]);
    }

    cout << "Approximate integral of f(x) = x^2: " << integral << "\n";

    return 0;
}
