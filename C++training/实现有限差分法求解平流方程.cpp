#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;

// �������ռ���������ʱ�䲽�����������������
const int MAX_N = 2048; // ���ռ��������
const int MAX_M = 10000; // ���ʱ�䲽��

int main() {
    // ��������
    const double L = 1.0;          // �ռ����䳤��
    const double T = 1.0;          // ʱ�����䳤��
    const int N = 100;             // �ռ�������
    const int M = 1000;            // ʱ�䲽��
    const double c = 1.0;          // ƽ���ٶ�
    const double dx = L / (N - 1); // �ռ䲽��
    const double dt = T / M;       // ʱ�䲽��

    if (N > MAX_N || M > MAX_M) {
        cerr << "Error: N or M exceeds MAX_N or MAX_M." << endl;
        return 1;
    }

    // ��ʼ�����þ�̬������� vector��
    double u[MAX_N];     // ��ǰʱ�䲽�Ľ�
    double u_new[MAX_N]; // ��һʱ�䲽�Ľ�

    // ��ʼ����
    for (int i = 0; i < N; ++i) {
        double x = i * dx;
        u[i] = sin(2 * M_PI * x); // ���Ҳ���ʼ����
    }

    // ʱ���ƽ�
    for (int n = 0; n < M; ++n) {
        // �߽����������ڱ߽磩
        u_new[0] = u[0] - c * dt / (2 * dx) * (u[1] - u[N - 1]);
        u_new[N - 1] = u[N - 1] - c * dt / (2 * dx) * (u[0] - u[N - 2]);

        // �ڲ���
        for (int i = 1; i < N - 1; ++i) {
            u_new[i] = u[i] - c * dt / (2 * dx) * (u[i + 1] - u[i - 1]);
        }

        // ���½⣨�����ֵ���� vector ��ֵ��
        for (int i = 0; i < N; ++i) {
            u[i] = u_new[i];
        }

        // ��������ÿ100��һ�Σ�
        if (n % 100 == 0) {
            string filename = "u_" + to_string(n) + ".txt";
            ofstream outfile(filename.c_str());
            if (!outfile.is_open()) {
                cerr << "Failed to open file: " << filename << endl;
                continue;
            }
            for (int i = 0; i < N; ++i) {
                outfile << i * dx << " " << u[i] << endl;
            }
            outfile.close();
        }
    }

    cout << "Simulation completed! Check output files for results." << endl;

    return 0;
}
