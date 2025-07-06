#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// �������ռ�������
const int MAX_NX = 2048;

class WaveEquationSolver {
private:
    int Nx, Nt;             // �ռ䲽����ʱ�䲽��
    double L, T;            // �ռ䳤�Ⱥ�ʱ���ܳ�
    double c;               // ����
    double dx, dt;          // �������ʱ�䲽��

    // ʹ�þ�̬������� vector
    double u_old[MAX_NX];
    double u_current[MAX_NX];
    double u_new[MAX_NX];

    // ��ʼλ�ƺ��� f(x)
    double f(double x) {
        return sin(M_PI * x / L);  // ��ʼλ�ƣ����Ҳ�
    }

    // ��ʼ�ٶȺ��� g(x)
    double g(double x) {
        return 0.0;  // ���ʼ�ٶ�
    }

    // �߽���������
    void applyBoundaryConditions() {
        u_current[0] = 0.0;         // ��߽�
        u_current[Nx - 1] = 0.0;    // �ұ߽�
        u_old[0] = 0.0;
        u_old[Nx - 1] = 0.0;
    }

public:
    // ���캯��
    WaveEquationSolver(double L_val, double T_val, int Nx_val, int Nt_val, double c_val)
        : L(L_val), T(T_val), Nx(Nx_val), Nt(Nt_val), c(c_val) {

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
            u_current[i] = f(x) + dt * g(x);
        }
    }

    // ʹ�����޲�ַ���Ⲩ������
    void solve() {
        applyBoundaryConditions();

        // ʱ���ƽ�
        for (int n = 1; n < Nt - 1; ++n) {
            for (int i = 1; i < Nx - 1; ++i) {
                double laplacian = u_current[i + 1] - 2 * u_current[i] + u_current[i - 1];
                u_new[i] = 2 * u_current[i] - u_old[i] + (c * c * dt * dt / (dx * dx)) * laplacian;
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
    // �������
    double L = 10.0;      // �ռ䳤��
    double T = 2.0;       // ʱ���ܳ�
    int Nx = 100;         // �ռ�������
    int Nt = 500;         // ʱ�䲽��
    double c = 1.0;       // ����

    // �������������
    WaveEquationSolver solver(L, T, Nx, Nt, c);

    // ��Ⲣ������
    solver.solve();

    return 0;
}
