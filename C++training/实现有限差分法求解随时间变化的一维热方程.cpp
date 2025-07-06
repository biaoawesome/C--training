#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// 设置最大空间网格数
const int MAX_NX = 2048;

class HeatEquationSolver {
private:
    int Nx, Nt;              // 空间步数和时间步数
    double L, T;             // 空间长度和时间总长度
    double alpha;            // 热扩散系数
    double dx, dt;           // 空间步长和时间步长

    // 使用静态数组代替 vector
    double u_old[MAX_NX];
    double u_current[MAX_NX];
    double u_new[MAX_NX];

    // 初始条件 f(x)
    double f(double x) {
        return sin(M_PI * x / L);  // 正弦波初始条件
    }

    // 边界条件处理
    void applyBoundaryConditions() {
        u_current[0] = 0.0;               // 左边界
        u_current[Nx - 1] = 0.0;          // 右边界
        u_old[0] = 0.0;
        u_old[Nx - 1] = 0.0;
    }

public:
    // 构造函数
    HeatEquationSolver(double L_val, double T_val, int Nx_val, int Nt_val, double alpha_val)
        : L(L_val), T(T_val), Nx(Nx_val), Nt(Nt_val), alpha(alpha_val) {

        if (Nx > MAX_NX) {
            cerr << "Error: Nx exceeds MAX_NX." << endl;
            exit(1);
        }

        dx = L / (Nx - 1);
        dt = T / (Nt - 1);

        // 初始化 u_old 和 u_current
        for (int i = 0; i < Nx; ++i) {
            double x = i * dx;
            u_old[i] = f(x);
            u_current[i] = f(x);
        }
    }

    // 显式有限差分法求解热方程
    void solve() {
        applyBoundaryConditions();

        // 时间推进
        for (int n = 0; n < Nt - 1; ++n) {
            for (int i = 1; i < Nx - 1; ++i) {
                u_new[i] = u_current[i]
                    + alpha * dt / (dx * dx)
                    * (u_current[i + 1] - 2 * u_current[i] + u_current[i - 1]);
            }

            applyBoundaryConditions();

            // 更新解
            for (int i = 0; i < Nx; ++i) {
                u_old[i] = u_current[i];
                u_current[i] = u_new[i];
            }

            // 输出结果（每50步一次）
            if (n % 50 == 0) {
                cout.precision(6);
                cout << "Time step " << n << " temperature distribution:" << endl;
                for (int i = 0; i < Nx; ++i) {
                    cout << setw(10) << u_current[i];
                }
                cout << endl;
            }
        }
    }
};

int main() {
    // 输入参数
    double L = 10.0;      // 空间长度
    double T = 2.0;       // 时间区间
    int Nx = 100;         // 空间网格数
    int Nt = 500;         // 时间步数
    double alpha = 0.01;  // 热扩散系数

    // 创建求解器对象
    HeatEquationSolver solver(L, T, Nx, Nt, alpha);

    // 求解并输出结果
    solver.solve();

    return 0;
}
