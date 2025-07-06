#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// �������ռ���������ʱ�䲽����������Ҫ������
const int MAX_NX = 1024;
const int MAX_NT = 10000;

class BurgersSolver {
private:
    int Nx, Nt;               // �ռ��ʱ�䲽��
    double L, T;              // �ռ������ʱ������
    double u0, uL;            // �߽�����
    double (*f)(double);      // ��ʼ��������
    double dx, dt;            // �ռ��ʱ�䲽��

    // ʹ�þ�̬������� vector
    double u_old[MAX_NX];
    double u_current[MAX_NX];
    double u_new[MAX_NX];

    // ��ʼ���� f(x)
    double f_initial(double x) {
        return sin(M_PI * x / L);  // �����ʼ����Ϊ���Һ���
    }

    // �߽���������
    void applyBoundaryConditions() {
        u_current[0] = u0;             // ��߽�����
        u_current[Nx - 1] = uL;        // �ұ߽�����
        u_old[0] = u0;                 // ��߽�����
        u_old[Nx - 1] = uL;            // �ұ߽�����
    }

public:
    // ���캯������ʼ������
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

        // ��ʼ�� u_old �� u_current
        for (int i = 0; i < Nx; ++i) {
            double x = i * dx;
            u_old[i] = f_initial(x);
            u_current[i] = f_initial(x);
        }
    }

    // ʹ�����ܷ�����ճ��ʱ�� Burger ����
    void solve() {
        applyBoundaryConditions();

        // ʱ�䲽��
        for (int n = 1; n < Nt - 1; ++n) {
            // ʹ�����ܷ����½�
            for (int i = 1; i < Nx - 1; ++i) {
                u_new[i] = u_old[i] - (dt / (2 * dx)) * u_current[i] * (u_current[i + 1] - u_current[i - 1]);
            }

            applyBoundaryConditions();

            // ���½⣨������ƣ�
            for (int i = 0; i < Nx; ++i) {
                u_old[i] = u_current[i];
                u_current[i] = u_new[i];
            }

            // �����ǰʱ�䲽�Ľ�
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

// ��ʼ�������� f(x)
double f(double x) {
    return sin(M_PI * x);  // �����ʼ����Ϊ���Һ���
}

int main() {
    double L = 1.0;       // �ռ����䳤��
    double T = 0.5;       // ʱ�����䳤��
    int Nx = 100;         // �ռ�������
    int Nt = 200;         // ʱ�䲽��
    double u0 = 0.0;      // ��߽�����
    double uL = 0.0;      // �ұ߽�����

    // �������������
    BurgersSolver solver(L, T, Nx, Nt, u0, uL, f);

    // ����ճ��ʱ�� Burger ����
    solver.solve();

    return 0;
}
