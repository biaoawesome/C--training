#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// 设置最大网格尺寸
const int MAX_NX = 1024;
const int MAX_NY = 1024;

class HeatEquationSolver {
private:
    int nx, ny;               // 网格点数
    double Lx, Ly;            // 区域尺寸
    double T1, T2, T3, T4;    // 边界条件
    double dx, dy;            // 网格间距
    double tolerance;         // 迭代容忍度
    int maxIter;              // 最大迭代次数

    // 使用静态二维数组代替 vector<vector<double>>
    double T[MAX_NX][MAX_NY]; // 温度矩阵

    // 初始化温度矩阵
    void initializeTemperature() {
        // 初始化所有点为 0.0
        for (int i = 0; i < nx; ++i) {
            for (int j = 0; j < ny; ++j) {
                T[i][j] = 0.0;
            }
        }

        // 设置边界条件
        for (int i = 0; i < nx; ++i) {
            T[i][0] = T3;         // 左边界
            T[i][ny - 1] = T4;    // 右边界
        }
        for (int j = 0; j < ny; ++j) {
            T[0][j] = T1;         // 下边界
            T[nx - 1][j] = T2;    // 上边界
        }
    }

    // 打印温度分布
    void printTemperature() {
        cout << "\n温度分布：" << endl;
        cout.precision(6);
        for (int i = 0; i < nx; ++i) {
            for (int j = 0; j < ny; ++j) {
                cout << setw(8) << T[i][j];
            }
            cout << endl;
        }
    }

public:
    // 构造函数
    HeatEquationSolver(double Lx_val, double Ly_val,
                       int nx_val, int ny_val,
                       double T1_val, double T2_val,
                       double T3_val, double T4_val,
                       double tolerance_val = 1e-6,
                       int maxIter_val = 10000)
        : Lx(Lx_val), Ly(Ly_val), nx(nx_val), ny(ny_val),
          T1(T1_val), T2(T2_val), T3(T3_val), T4(T4_val),
          tolerance(tolerance_val), maxIter(maxIter_val) {

        if (nx > MAX_NX || ny > MAX_NY) {
            cerr << "Error: Grid size exceeds MAX_NX or MAX_NY." << endl;
            exit(1);
        }

        dx = Lx / (nx - 1);
        dy = Ly / (ny - 1);
    }

    // 使用 Jacobi 迭代法求解热方程
    void solve() {
        initializeTemperature();

        int iter = 0;
        double maxError;

        do {
            maxError = 0.0;

            // 更新内部网格点的温度
            for (int i = 1; i < nx - 1; ++i) {
                for (int j = 1; j < ny - 1; ++j) {
                    double newT = 0.5 * (T[i + 1][j] + T[i - 1][j]) * dy * dy +
                                  0.5 * (T[i][j + 1] + T[i][j - 1]) * dx * dx;
                    newT /= (dx * dx + dy * dy);

                    double error = fabs(newT - T[i][j]);
                    if (error > maxError) {
                        maxError = error;
                    }
                    T[i][j] = newT;
                }
            }

            ++iter;
            if (iter % 1000 == 0) {
                cout << "迭代次数: " << iter << ", 最大误差: " << maxError << endl;
            }
        } while (maxError > tolerance && iter < maxIter);

        // 打印最终结果
        if (iter >= maxIter) {
            cout << "未达到所需的精度，达到最大迭代次数。" << endl;
        }
        printTemperature();
    }
};

int main() {
    // 输入参数
    double Lx = 10.0, Ly = 10.0;   // 区域大小
    int nx = 20, ny = 20;          // 网格划分数量
    double T1 = 100.0, T2 = 0.0;   // 下边和上边
    double T3 = 0.0, T4 = 50.0;    // 左边和右边

    // 创建求解器对象
    HeatEquationSolver solver(Lx, Ly, nx, ny, T1, T2, T3, T4);

    // 求解并输出结果
    solver.solve();

    return 0;
}
