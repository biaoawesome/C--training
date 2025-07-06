#include <iostream>
#include <cmath>

using namespace std;

const int MAX_POINTS = 1024; // 最大支持的点数（根据需要调整）

// 生成单位圆圆周上的正交规则点和权重
void generateCircleQuadrature(int N, double theta[], double weights[]) {
    if (N <= 0 || N > MAX_POINTS) return;

    double dTheta = 2.0 * M_PI / N; // 角度间隔
    double weight = dTheta;         // 权重

    for (int k = 0; k < N; ++k) {
        theta[k] = k * dTheta;   // 极角
        weights[k] = weight;     // 权重
    }
}

// 示例函数 f(theta) = sin(theta)
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

    // 声明静态数组
    double theta[MAX_POINTS];
    double weights[MAX_POINTS];

    // 生成正交规则点和权重
    generateCircleQuadrature(N, theta, weights);

    // 输出点和权重
    cout << "Quadrature points and weights on the unit circle:\n";
    for (int k = 0; k < N; ++k) {
        double x = cos(theta[k]);
        double y = sin(theta[k]);
        cout.precision(10);
        cout << "Point " << k << ": (" << fixed << x << ", " << y << "), "
             << "Theta: " << theta[k] << ", Weight: " << weights[k] << "\n";
    }

    // 计算积分近似值
    double integral = 0.0;
    for (int k = 0; k < N; ++k) {
        integral += weights[k] * exampleFunction(theta[k]);
    }

    cout << "Approximate integral of f(theta) = sin(theta): " << integral << "\n";

    return 0;
}
