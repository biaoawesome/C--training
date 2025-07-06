#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
 
using namespace std;
 
// ===================== 辅助函数 =====================
// 系数函数
double p(double x) {
    return 1.0; // 可根据需求修改
}
 
double q(double x) {
    return 0.0; // 可根据需求修改
}
 
double f(double x) {
    return sin(M_PI * x); // 可根据需求修改
}
 
// ===================== FEM 实现 =====================
class FEMSolver {
private:
    int n;                         // 单元数
    double a, b;                   // 区间 [a, b]
    double ua, ub;                 // 边界条件 u(a), u(b)
    vector<double> nodes;          // 网格节点
    vector<vector<double>> K;      // 刚度矩阵
    vector<double> F;              // 右端项向量
    vector<double> u;              // 数值解
 
    // 生成网格节点
    void generateNodes() {
        nodes.resize(n + 1);
        double h = (b - a) / n;
        for (int i = 0; i <= n; ++i) {
            nodes[i] = a + i * h;
        }
    }
 
    // 计算单元刚度矩阵和载荷向量
    void assembleMatrix() {
        double h = (b - a) / n;
        K.assign(n + 1, vector<double>(n + 1, 0.0));
        F.assign(n + 1, 0.0);
 
        for (int i = 0; i < n; ++i) {
            double xL = nodes[i], xR = nodes[i + 1];
            double mid = (xL + xR) / 2.0;
 
            // 单元刚度矩阵 (梯度项)
            double ke[2][2] = {
                { p(mid) / h, -p(mid) / h },
                { -p(mid) / h, p(mid) / h }
            };
 
            // 单元载荷向量 (源项)
            double fe[2] = {
                f(mid) * h / 2.0,
                f(mid) * h / 2.0
            };
 
            // 组装到全局矩阵和向量
            K[i][i] += ke[0][0];
            K[i][i + 1] += ke[0][1];
            K[i + 1][i] += ke[1][0];
            K[i + 1][i + 1] += ke[1][1];
 
            F[i] += fe[0];
            F[i + 1] += fe[1];
        }
    }
 
    // 应用边界条件
    void applyBoundaryConditions() {
        // 修改矩阵和右端项以引入边界条件
        K[0].assign(n + 1, 0.0);
        K[n].assign(n + 1, 0.0);
        K[0][0] = 1.0;
        K[n][n] = 1.0;
        F[0] = ua;
        F[n] = ub;
    }
 
    // 线性方程求解器
    void solveSystem() {
        u.assign(n + 1, 0.0);
        for (int i = 0; i <= n; ++i) {
            u[i] = F[i] / K[i][i]; // 简单解法 (假设对角线元素非零)
        }
    }
 
public:
    // 构造函数
    FEMSolver(int numElements, double left, double right, double uLeft, double uRight)
        : n(numElements), a(left), b(right), ua(uLeft), ub(uRight) {}
 
    // 求解
    void solve() {
        generateNodes();
        assembleMatrix();
        applyBoundaryConditions();
        solveSystem();
    }
 
    // 输出结果
    void printSolution() const {
        cout << "\nFEM 解的结果:" << endl;
        cout << setw(10) << "x" << setw(15) << "u(x)" << endl;
        for (int i = 0; i <= n; ++i) {
            cout << setw(10) << nodes[i] << setw(15) << u[i] << endl;
        }
    }
};
 
int main() {
    // 输入参数
    double a = 0.0, b = 1.0; // 定义区间 [a, b]
    double ua = 0.0, ub = 0.0; // 边界条件
    int n = 10; // 网格划分数量
 
    // 创建 FEM 求解器
    FEMSolver femSolver(n, a, b, ua, ub);
 
    // 求解问题
    femSolver.solve();
 
    // 输出结果
    femSolver.printSolution();
 
    return 0;
}
