#include <iostream>
#include <cmath>

using namespace std;

const int MAX_SIZE = 1024; // 最大支持的节点数（根据需要调整）

// 生成高斯-切比雪夫 1 型正交规则的积分点和权重
void gaussChebyshevType1(int N, double points[], double weights[]) {
    double weightFactor = M_PI / N; // 权重因子

    for (int k = 0; k < N; ++k) {
        double theta = (2 * k + 1) * M_PI / (2 * N); // 极角
        points[k] = cos(theta);                      // 积分点
        weights[k] = weightFactor * sin(theta);       // 权重
    }
}

// 示例函数 f(x) = x^2
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

    double points[MAX_SIZE];   // 存储积分点
    double weights[MAX_SIZE];  // 存储权重

    // 生成积分点和权重
    gaussChebyshevType1(N, points, weights);

    // 输出积分点和权重
    cout << "Gauss-Chebyshev Type 1 points and weights:\n";
    for (int k = 0; k < N; ++k) {
        cout.precision(10);
        cout << "Point " << k << ": " << fixed << points[k]
             << ", Weight: " << weights[k] << "\n";
    }

    // 计算积分近似值
    double integral = 0.0;
    for (int k = 0; k < N; ++k) {
        integral += weights[k] * exampleFunction(points[k]);
    }

    cout << "Approximate integral of f(x) = x^2: " << integral << "\n";

    return 0;
}
