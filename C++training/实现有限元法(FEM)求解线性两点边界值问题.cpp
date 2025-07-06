#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
 
using namespace std;
 
// ===================== �������� =====================
// ϵ������
double p(double x) {
    return 1.0; // �ɸ��������޸�
}
 
double q(double x) {
    return 0.0; // �ɸ��������޸�
}
 
double f(double x) {
    return sin(M_PI * x); // �ɸ��������޸�
}
 
// ===================== FEM ʵ�� =====================
class FEMSolver {
private:
    int n;                         // ��Ԫ��
    double a, b;                   // ���� [a, b]
    double ua, ub;                 // �߽����� u(a), u(b)
    vector<double> nodes;          // ����ڵ�
    vector<vector<double>> K;      // �նȾ���
    vector<double> F;              // �Ҷ�������
    vector<double> u;              // ��ֵ��
 
    // ��������ڵ�
    void generateNodes() {
        nodes.resize(n + 1);
        double h = (b - a) / n;
        for (int i = 0; i <= n; ++i) {
            nodes[i] = a + i * h;
        }
    }
 
    // ���㵥Ԫ�նȾ�����غ�����
    void assembleMatrix() {
        double h = (b - a) / n;
        K.assign(n + 1, vector<double>(n + 1, 0.0));
        F.assign(n + 1, 0.0);
 
        for (int i = 0; i < n; ++i) {
            double xL = nodes[i], xR = nodes[i + 1];
            double mid = (xL + xR) / 2.0;
 
            // ��Ԫ�նȾ��� (�ݶ���)
            double ke[2][2] = {
                { p(mid) / h, -p(mid) / h },
                { -p(mid) / h, p(mid) / h }
            };
 
            // ��Ԫ�غ����� (Դ��)
            double fe[2] = {
                f(mid) * h / 2.0,
                f(mid) * h / 2.0
            };
 
            // ��װ��ȫ�־��������
            K[i][i] += ke[0][0];
            K[i][i + 1] += ke[0][1];
            K[i + 1][i] += ke[1][0];
            K[i + 1][i + 1] += ke[1][1];
 
            F[i] += fe[0];
            F[i + 1] += fe[1];
        }
    }
 
    // Ӧ�ñ߽�����
    void applyBoundaryConditions() {
        // �޸ľ�����Ҷ���������߽�����
        K[0].assign(n + 1, 0.0);
        K[n].assign(n + 1, 0.0);
        K[0][0] = 1.0;
        K[n][n] = 1.0;
        F[0] = ua;
        F[n] = ub;
    }
 
    // ���Է��������
    void solveSystem() {
        u.assign(n + 1, 0.0);
        for (int i = 0; i <= n; ++i) {
            u[i] = F[i] / K[i][i]; // �򵥽ⷨ (����Խ���Ԫ�ط���)
        }
    }
 
public:
    // ���캯��
    FEMSolver(int numElements, double left, double right, double uLeft, double uRight)
        : n(numElements), a(left), b(right), ua(uLeft), ub(uRight) {}
 
    // ���
    void solve() {
        generateNodes();
        assembleMatrix();
        applyBoundaryConditions();
        solveSystem();
    }
 
    // ������
    void printSolution() const {
        cout << "\nFEM ��Ľ��:" << endl;
        cout << setw(10) << "x" << setw(15) << "u(x)" << endl;
        for (int i = 0; i <= n; ++i) {
            cout << setw(10) << nodes[i] << setw(15) << u[i] << endl;
        }
    }
};
 
int main() {
    // �������
    double a = 0.0, b = 1.0; // �������� [a, b]
    double ua = 0.0, ub = 0.0; // �߽�����
    int n = 10; // ���񻮷�����
 
    // ���� FEM �����
    FEMSolver femSolver(n, a, b, ua, ub);
 
    // �������
    femSolver.solve();
 
    // ������
    femSolver.printSolution();
 
    return 0;
}
