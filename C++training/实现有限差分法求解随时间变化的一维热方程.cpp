#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// �������ռ�������
const int MAX_NX = 2048;

class HeatEquationSolver {
private:
    int Nx, Nt;              // �ռ䲽����ʱ�䲽��
    double L, T;             // �ռ䳤�Ⱥ�ʱ���ܳ���
    double alpha;            // ����ɢϵ��
    double dx, dt;           // �ռ䲽����ʱ�䲽��

    // ʹ�þ�̬������� vector
    double u_old[MAX_NX];
    double u_current[MAX_NX];
    double u_new[MAX_NX];

    // ��ʼ���� f(x)
    double f(double x) {
        return sin(M_PI * x / L);  // ���Ҳ���ʼ����
    }

    // �߽���������
    void applyBoundaryConditions() {
        u_current[0] = 0.0;               // ��߽�
        u_current[Nx - 1] = 0.0;          // �ұ߽�
        u_old[0] = 0.0;
        u_old[Nx - 1] = 0.0;
    }

public:
    // ���캯��
    HeatEquationSolver(double L_val, double T_val, int Nx_val, int Nt_val, double alpha_val)
        : L(L_val), T(T_val), Nx(Nx_val), Nt(Nt_val), alpha(alpha_val) {

        if (Nx > MAX_NX) {
            cerr << "Error: Nx exceeds MAX_NX." << endl;
            exit(1);
        }

        dx = L / (Nx - 1);
        dt = T / (Nt - 1);

        // ��ʼ�� u_old �� u_current
        for (int i = 0; i < Nx; ++i) {
            double x = i * dx;
            u_old[i] = f(x);
            u_current[i] = f(x);
        }
    }

    // ��ʽ���޲�ַ�����ȷ���
    void solve() {
        applyBoundaryConditions();

        // ʱ���ƽ�
        for (int n = 0; n < Nt - 1; ++n) {
            for (int i = 1; i < Nx - 1; ++i) {
                u_new[i] = u_current[i]
                    + alpha * dt / (dx * dx)
                    * (u_current[i + 1] - 2 * u_current[i] + u_current[i - 1]);
            }

            applyBoundaryConditions();

            // ���½�
            for (int i = 0; i < Nx; ++i) {
                u_old[i] = u_current[i];
                u_current[i] = u_new[i];
            }

            // ��������ÿ50��һ�Σ�
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
    // �������
    double L = 10.0;      // �ռ䳤��
    double T = 2.0;       // ʱ������
    int Nx = 100;         // �ռ�������
    int Nt = 500;         // ʱ�䲽��
    double alpha = 0.01;  // ����ɢϵ��

    // �������������
    HeatEquationSolver solver(L, T, Nx, Nt, alpha);

    // ��Ⲣ������
    solver.solve();

    return 0;
}
