#include <iostream>
#include <cmath>

using namespace std;

const int MAX_SIZE = 100; // ����������ȣ��ɸ�����Ҫ����

// �����ӷ���y = x + y
void vectorAdd(const double x[], double y[], int size) {
    for (int i = 0; i < size; ++i) {
        y[i] += x[i];
    }
}

// �������ţ�x = alpha * x
void vectorScale(double alpha, double x[], int size) {
    for (int i = 0; i < size; ++i) {
        x[i] *= alpha;
    }
}

// �����alpha = x^T y
double dotProduct(const double x[], const double y[], int size) {
    double result = 0.0;
    for (int i = 0; i < size; ++i) {
        result += x[i] * y[i];
    }
    return result;
}

// �������ƣ�y = x
void vectorCopy(const double x[], double y[], int size) {
    for (int i = 0; i < size; ++i) {
        y[i] = x[i];
    }
}

// ����������alpha = ||x||_2
double vectorNorm(const double x[], int size) {
    double result = 0.0;
    for (int i = 0; i < size; ++i) {
        result += x[i] * x[i];
    }
    return sqrt(result);
}

int main() {
    // ��ʼ����������
    const int size = 3;
    double x[MAX_SIZE] = {1.0, 2.0, 3.0};
    double y[MAX_SIZE] = {4.0, 5.0, 6.0};
    double z[MAX_SIZE];

    // �����ӷ�: y = x + y
    vectorAdd(x, y, size);
    cout << "Vector Addition (y = x + y): ";
    for (int i = 0; i < size; ++i) {
        cout << y[i] << " ";
    }
    cout << endl;

    // ��������: x = 2.0 * x
    double alpha = 2.0;
    vectorScale(alpha, x, size);
    cout << "Vector Scaling (x = alpha * x): ";
    for (int i = 0; i < size; ++i) {
        cout << x[i] << " ";
    }
    cout << endl;

    // ���: x^T y
    double dp = dotProduct(x, y, size);
    cout << "Dot Product (x^T y): " << dp << endl;

    // ��������: z = x
    vectorCopy(x, z, size);
    cout << "Vector Copy (z = x): ";
    for (int i = 0; i < size; ++i) {
        cout << z[i] << " ";
    }
    cout << endl;

    // ��������: ||x||
    double norm = vectorNorm(x, size);
    cout << "Vector Norm (||x||_2): " << norm << endl;

    return 0;
}
