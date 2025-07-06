#include <iostream>
#include <cmath>

using namespace std;

const int MAX_POINTS = 1024; // ���֧�ֵĵ�����������Ҫ������

// �����Ľṹ��
struct Point {
    double x, y;
};

// ����Բ���ϵĵ�����
void generateArcPoints(double cx, double cy, double r, double theta1, double theta2, int N,
                       Point points[]) {
    if (N <= 0 || N > MAX_POINTS) return;

    double deltaTheta = theta2 - theta1; // �ܽǶ�
    double dTheta = deltaTheta / (N - 1); // �Ƕȼ��

    for (int k = 0; k < N; ++k) {
        double theta = theta1 + k * dTheta; // ��ǰ����
        points[k].x = cx + r * cos(theta);  // ת��Ϊ�ѿ�������
        points[k].y = cy + r * sin(theta);
    }
}

int main() {
    // ����Բ������
    double cx, cy, r, theta1, theta2;
    int N;

    cout << "Enter the center (cx, cy): ";
    cin >> cx >> cy;
    cout << "Enter the radius (r): ";
    cin >> r;
    cout << "Enter the start angle (theta1, in radians): ";
    cin >> theta1;
    cout << "Enter the end angle (theta2, in radians): ";
    cin >> theta2;
    cout << "Enter the number of points (N): ";
    cin >> N;

    if (N <= 0 || N > MAX_POINTS) {
        cerr << "Invalid number of points.\n";
        return 1;
    }

    // ������̬����
    Point points[MAX_POINTS];

    // ���ɵ�����
    generateArcPoints(cx, cy, r, theta1, theta2, N, points);

    // ���������
    cout << "Generated points on the arc:\n";
    for (int i = 0; i < N; ++i) {
        cout << "(" << points[i].x << ", " << points[i].y << ")\n";
    }

    return 0;
}
