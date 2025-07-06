#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// 设置最大空间网格数
const int MAX_NX = 2048;

class WaveEquationSolver {
private:
    int Nx, Nt;             // 空间步数和时间步数
    double L, T;            // 空间长度和时间总长
    double c;               // 波速
    double dx, dt;          // 网格间距和时间步长

    // 使用静态数组代替 vector
    double u_old[MAX_NX];
    double u_current[MAX_NX];
    double u_new[MAX_NX];

    // 初始位移函数 f(x)
    double f(double x) {
        return sin(M_PI * x / L);  // 初始位移：正弦波
    }

    // 初始速度函数 g(x)
    double g(double x) {
        return 0.0;  // 零初始速度
    }

    // 边界条件处理
    void applyBoundaryConditions() {
        u_current[0] = 0.0;         // 左边界
        u_current[Nx - 1] = 0.0;    // 右边界
        u_old[0] = 0.0;
        u_old[Nx - 1] = 0.0;
    }

public:
    // 构造函数
    WaveEquationSolver(double L_val, double T_val, int Nx_val, int Nt_val, double c_val)
        : L(L_val), T(T_val), Nx(Nx_val), Nt(Nt_val), c(c_val) {

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
            u_current[i] = f(x) + dt * g(x);
        }
    }

    // 使用有限差分法求解波动方程
    void solve() {
        applyBoundaryConditions();

        // 时间推进
        for (int n = 1; n < Nt - 1; ++n) {
            for (int i = 1; i < Nx - 1; ++i) {
                double laplacian = u_current[i + 1] - 2 * u_current[i] + u_current[i - 1];
                u_new[i] = 2 * u_current[i] - u_old[i] + (c * c * dt * dt / (dx * dx)) * laplacian;
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
                cout << "Time step " << n << " wave distribution:" << endl;
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
    double T = 2.0;       // 时间总长
    int Nx = 100;         // 空间网格数
    int Nt = 500;         // 时间步数
    double c = 1.0;       // 波速

    // 创建求解器对象
    WaveEquationSolver solver(L, T, Nx, Nt, c);

    // 求解并输出结果
    solver.solve();

    return 0;
}
