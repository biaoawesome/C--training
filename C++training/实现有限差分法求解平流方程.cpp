#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;

// 设置最大空间网格数和时间步数（根据需求调整）
const int MAX_N = 2048; // 最大空间网格点数
const int MAX_M = 10000; // 最大时间步数

int main() {
    // 参数设置
    const double L = 1.0;          // 空间区间长度
    const double T = 1.0;          // 时间区间长度
    const int N = 100;             // 空间网格数
    const int M = 1000;            // 时间步数
    const double c = 1.0;          // 平流速度
    const double dx = L / (N - 1); // 空间步长
    const double dt = T / M;       // 时间步长

    if (N > MAX_N || M > MAX_M) {
        cerr << "Error: N or M exceeds MAX_N or MAX_M." << endl;
        return 1;
    }

    // 初始化（用静态数组代替 vector）
    double u[MAX_N];     // 当前时间步的解
    double u_new[MAX_N]; // 下一时间步的解

    // 初始条件
    for (int i = 0; i < N; ++i) {
        double x = i * dx;
        u[i] = sin(2 * M_PI * x); // 正弦波初始条件
    }

    // 时间推进
    for (int n = 0; n < M; ++n) {
        // 边界条件（周期边界）
        u_new[0] = u[0] - c * dt / (2 * dx) * (u[1] - u[N - 1]);
        u_new[N - 1] = u[N - 1] - c * dt / (2 * dx) * (u[0] - u[N - 2]);

        // 内部点
        for (int i = 1; i < N - 1; ++i) {
            u_new[i] = u[i] - c * dt / (2 * dx) * (u[i + 1] - u[i - 1]);
        }

        // 更新解（逐个赋值代替 vector 赋值）
        for (int i = 0; i < N; ++i) {
            u[i] = u_new[i];
        }

        // 输出结果（每100步一次）
        if (n % 100 == 0) {
            string filename = "u_" + to_string(n) + ".txt";
            ofstream outfile(filename.c_str());
            if (!outfile.is_open()) {
                cerr << "Failed to open file: " << filename << endl;
                continue;
            }
            for (int i = 0; i < N; ++i) {
                outfile << i * dx << " " << u[i] << endl;
            }
            outfile.close();
        }
    }

    cout << "Simulation completed! Check output files for results." << endl;

    return 0;
}
