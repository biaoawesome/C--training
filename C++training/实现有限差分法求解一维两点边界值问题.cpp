#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// ��������������
const int MAX_N = 1024;

class FiniteDifferenceSolver {
private:
    int N;                // �������
    double L;             // ���䳤��
    double u0, uL;        // �߽�����
    double (*f)(double);  // �Ҷ����
    double dx;            // ���񲽳�

    // ʹ�þ�̬������� vector
    double A[MAX_N];      // ϵ������Խ���Ԫ��
    double b[MAX_N];      // �Ҷ���
    double u[MAX_N];      // ������

public:
    // ���캯������ʼ������
    FiniteDifferenceSolver(int N_val, double L_val, double u0_val, double uL_val, double (*f_val)(double))
        : N(N_val), L(L_val), u0(u0_val), uL(uL_val), f(f_val) {

        if (N > MAX_N) {
            cerr << "Error: N exceeds MAX_N." << endl;
            exit(1);
        }

        dx = L / (N + 1);  // ���㲽��

        // ��ʼ������
        for (int i = 0; i < N; ++i) {
            A[i] = 0.0;
            b[i] = 0.0;
            u[i] = 0.0;
        }
    }

    // ������Է����� Ax = b
    void solve() {
        // ��ɢ��������ϵ������A���Ҷ���b
        for (int i = 0; i < N; ++i) {
            double x = (i + 1) * dx;
            b[i] = -f(x) * dx * dx;  // �Ҷ��� b_i = -f(x_i) * dx^2
            A[i] = -2.0;             // ���жԽ���Ԫ�ض��� -2
        }

        // Ӧ�ñ߽�����
        b[0] -= u0 * dx * dx;
        b[N - 1] -= uL * dx * dx;

        // �����Է����飨����ֻ�Ǽ򵥳�����ʵ��Ӧʹ�����ԽǾ����������
        for (int i = 0; i < N; ++i) {
            u[i] = b[i] / A[i];
        }

        // �����
        cout.precision(6);
        cout << "�����ֵ�����" << endl;
        for (int i = 0; i < N; ++i) {
            double x = (i + 1) * dx;
            cout << "u(" << x << ") = " << setw(10) << u[i] << endl;
        }
    }
};

// �Ҷ���� f(x)
double f(double x) {
    return 100.0 * exp(-10.0 * x);
}

int main() {
    int N = 10;          // �������
    double L = 1.0;      // ���䳤��
    double u0 = 0.0;     // ��߽�����
    double uL = 0.0;     // �ұ߽�����

    // �������������
    FiniteDifferenceSolver solver(N, L, u0, uL, f);

    // ��Ⲣ������
    solver.solve();

    return 0;
}
