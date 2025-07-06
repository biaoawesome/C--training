#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// �����������ߴ�
const int MAX_NX = 1024;
const int MAX_NY = 1024;

class HeatEquationSolver {
private:
    int nx, ny;               // �������
    double Lx, Ly;            // ����ߴ�
    double T1, T2, T3, T4;    // �߽�����
    double dx, dy;            // ������
    double tolerance;         // �������̶�
    int maxIter;              // ����������

    // ʹ�þ�̬��ά������� vector<vector<double>>
    double T[MAX_NX][MAX_NY]; // �¶Ⱦ���

    // ��ʼ���¶Ⱦ���
    void initializeTemperature() {
        // ��ʼ�����е�Ϊ 0.0
        for (int i = 0; i < nx; ++i) {
            for (int j = 0; j < ny; ++j) {
                T[i][j] = 0.0;
            }
        }

        // ���ñ߽�����
        for (int i = 0; i < nx; ++i) {
            T[i][0] = T3;         // ��߽�
            T[i][ny - 1] = T4;    // �ұ߽�
        }
        for (int j = 0; j < ny; ++j) {
            T[0][j] = T1;         // �±߽�
            T[nx - 1][j] = T2;    // �ϱ߽�
        }
    }

    // ��ӡ�¶ȷֲ�
    void printTemperature() {
        cout << "\n�¶ȷֲ���" << endl;
        cout.precision(6);
        for (int i = 0; i < nx; ++i) {
            for (int j = 0; j < ny; ++j) {
                cout << setw(8) << T[i][j];
            }
            cout << endl;
        }
    }

public:
    // ���캯��
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

    // ʹ�� Jacobi ����������ȷ���
    void solve() {
        initializeTemperature();

        int iter = 0;
        double maxError;

        do {
            maxError = 0.0;

            // �����ڲ��������¶�
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
                cout << "��������: " << iter << ", ������: " << maxError << endl;
            }
        } while (maxError > tolerance && iter < maxIter);

        // ��ӡ���ս��
        if (iter >= maxIter) {
            cout << "δ�ﵽ����ľ��ȣ��ﵽ������������" << endl;
        }
        printTemperature();
    }
};

int main() {
    // �������
    double Lx = 10.0, Ly = 10.0;   // �����С
    int nx = 20, ny = 20;          // ���񻮷�����
    double T1 = 100.0, T2 = 0.0;   // �±ߺ��ϱ�
    double T3 = 0.0, T4 = 50.0;    // ��ߺ��ұ�

    // �������������
    HeatEquationSolver solver(Lx, Ly, nx, ny, T1, T2, T3, T4);

    // ��Ⲣ������
    solver.solve();

    return 0;
}
