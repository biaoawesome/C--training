#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// 定义常数
const int NX = 100;         // 空间网格点数
const int NT = 1000;        // 时间步数
const double LX = 1.0;      // 空间长度
const double TMAX = 1.0;    // 最大时间
const double NU = 0.01;     // 粘性系数

// 初始化速度场
void initialize(double u[], int nx, double lx) {
    double dx = lx / (nx - 1);
    for (int i = 0; i < nx; ++i) {
        double x = i * dx;
        u[i] = sin(2 * M_PI * x); // 初始条件
    }
}

// 更新速度场
void update(double u[], double dt, double dx, int nx) {
    double u_new[nx]; // 局部临时数组保存新时间步的值

    for (int i = 1; i < nx - 1; ++i) {
        double du_dx = (u[i + 1] - u[i - 1]) / (2 * dx);
        double d2u_dx2 = (u[i + 1] - 2 * u[i] + u[i - 1]) / (dx * dx);
        u_new[i] = u[i] + dt * (-u[i] * du_dx + NU * d2u_dx2);
    }

    // 应用边界条件（周期性边界条件）
    u_new[0] = u_new[nx - 2];
    u_new[nx - 1] = u_new[1];

    // 将结果复制回 u 数组
    for (int i = 0; i < nx; ++i) {
        u[i] = u_new[i];
    }
}

int main() {
    double u[NX];             // 定义速度场数组
    double dx = LX / (NX - 1);
    double dt = TMAX / NT;

    // 初始化速度场
    initialize(u, NX, LX);

    // 输出初始速度场
    ofstream outFile("burgers_solution.csv");
    for (int i = 0; i < NX; ++i) {
        outFile << i * dx << "," << u[i] << "\n";
    }

    // 时间迭代
    for (int n = 0; n < NT; ++n) {
        update(u, dt, dx, NX);

        // 每隔 100 步输出一次
        if (n % 100 == 0) {
            for (int i = 0; i < NX; ++i) {
                outFile << i * dx << "," << u[i] << "\n";
            }
        }
    }

    outFile.close();
    cout << "Solution saved to burgers_solution.csv\n";

    return 0;
}
