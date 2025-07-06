#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// ���峣��
const int NX = 100;         // �ռ��������
const int NT = 1000;        // ʱ�䲽��
const double LX = 1.0;      // �ռ䳤��
const double TMAX = 1.0;    // ���ʱ��
const double NU = 0.01;     // ճ��ϵ��

// ��ʼ���ٶȳ�
void initialize(double u[], int nx, double lx) {
    double dx = lx / (nx - 1);
    for (int i = 0; i < nx; ++i) {
        double x = i * dx;
        u[i] = sin(2 * M_PI * x); // ��ʼ����
    }
}

// �����ٶȳ�
void update(double u[], double dt, double dx, int nx) {
    double u_new[nx]; // �ֲ���ʱ���鱣����ʱ�䲽��ֵ

    for (int i = 1; i < nx - 1; ++i) {
        double du_dx = (u[i + 1] - u[i - 1]) / (2 * dx);
        double d2u_dx2 = (u[i + 1] - 2 * u[i] + u[i - 1]) / (dx * dx);
        u_new[i] = u[i] + dt * (-u[i] * du_dx + NU * d2u_dx2);
    }

    // Ӧ�ñ߽������������Ա߽�������
    u_new[0] = u_new[nx - 2];
    u_new[nx - 1] = u_new[1];

    // ��������ƻ� u ����
    for (int i = 0; i < nx; ++i) {
        u[i] = u_new[i];
    }
}

int main() {
    double u[NX];             // �����ٶȳ�����
    double dx = LX / (NX - 1);
    double dt = TMAX / NT;

    // ��ʼ���ٶȳ�
    initialize(u, NX, LX);

    // �����ʼ�ٶȳ�
    ofstream outFile("burgers_solution.csv");
    for (int i = 0; i < NX; ++i) {
        outFile << i * dx << "," << u[i] << "\n";
    }

    // ʱ�����
    for (int n = 0; n < NT; ++n) {
        update(u, dt, dx, NX);

        // ÿ�� 100 �����һ��
        if (n % 100 == 0) {
            for (int i = 0; i < NX; ++i) {
                outFile << i * dx << "," << u[i] << "\n";
            }
        }
    }

    outFile.close();
    cout << "Solution saved to burgers_solution.csv\n";

    return 0;
}
