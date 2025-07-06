#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// 设置最大空间网格数和时间步数（根据需要调整）
const int MAX_NX = 1024;
const int MAX_NT = 10000;

class BurgersSolver {
private:
    int Nx, Nt;               // 空间和时间步数
    double L, T;              // 空间区间和时间区间
    double u0, uL;            // 边界条件
    double (*f)(double);      // 初始条件函数
    double dx, dt;            // 空间和时间步长

    // 使用静态数组代替 vector
    double u_old[MAX_NX];
    double u_current[MAX_NX];
    double u_new[MAX_NX];

    // 初始条件 f(x)
    double f_initial(double x) {
        return sin(M_PI * x / L);  // 假设初始条件为正弦函数
    }

    // 边界条件处理
    void applyBoundaryConditions() {
        u_current[0] = u0;             // 左边界条件
        u_current[Nx - 1] = uL;        // 右边界条件
        u_old[0] = u0;                 // 左边界条件
        u_old[Nx - 1] = uL;            // 右边界条件
    }

public:
    // 构造函数，初始化变量
    BurgersSolver(double L_val, double T_val, int Nx_val, int Nt_val,
                  double u0_val, double uL_val, double (*f_val)(double))
        : L(L_val), T(T_val), Nx(Nx_val), Nt(Nt_val),
          u0(u0_val), uL(uL_val), f(f_val) {

        if (Nx > MAX_NX || Nt > MAX_NT) {
            cerr << "Error: Nx or Nt exceeds MAX_NX or MAX_NT." << endl;
            exit(1);
        }

        dx = L / (Nx - 1);
        dt = T / (Nt - 1);

        // 初始化 u_old 和 u_current
        for (int i = 0; i < Nx; ++i) {
            double x = i * dx;
            u_old[i] = f_initial(x);
            u_current[i] = f_initial(x);
        }
    }

    // 使用跳蛙法求解非粘性时变 Burger 方程
    void solve() {
        applyBoundaryConditions();

        // 时间步进
        for (int n = 1; n < Nt - 1; ++n) {
            // 使用跳蛙法更新解
            for (int i = 1; i < Nx - 1; ++i) {
                u_new[i] = u_old[i] - (dt / (2 * dx)) * u_current[i] * (u_current[i + 1] - u_current[i - 1]);
            }

            applyBoundaryConditions();

            // 更新解（逐个复制）
            for (int i = 0; i < Nx; ++i) {
                u_old[i] = u_current[i];
                u_current[i] = u_new[i];
            }

            // 输出当前时间步的解
            if (n % 50 == 0) {
                cout.precision(6);
                cout << "Time step " << n << " solution:" << endl;
                for (int i = 0; i < Nx; ++i) {
                    cout << setw(10) << u_current[i];
                }
                cout << endl;
            }
        }
    }
};

// 初始条件函数 f(x)
double f(double x) {
    return sin(M_PI * x);  // 假设初始条件为正弦函数
}

int main() {
    double L = 1.0;       // 空间区间长度
    double T = 0.5;       // 时间区间长度
    int Nx = 100;         // 空间网格数
    int Nt = 200;         // 时间步数
    double u0 = 0.0;      // 左边界条件
    double uL = 0.0;      // 右边界条件

    // 创建求解器对象
    BurgersSolver solver(L, T, Nx, Nt, u0, uL, f);

    // 求解非粘性时变 Burger 方程
    solver.solve();

    return 0;
}
