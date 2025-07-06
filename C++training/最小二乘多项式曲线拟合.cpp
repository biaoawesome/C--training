#include <stdio.h>
#include <math.h>
 
#define MAX_POINTS 100  // ���ݵ���������
 
// ����˷�������C = A * B
void matmul(double A[][MAX_POINTS], double B[], double C[], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        C[i] = 0;
        for (int j = 0; j < cols; j++) {
            C[i] += A[i][j] * B[j];
        }
    }
}
 
// ����ת�ú�����B = A^T
void transpose(double A[][MAX_POINTS], double B[][MAX_POINTS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            B[j][i] = A[i][j];
        }
    }
}
 
// �������溯�������ø�˹��Ԫ�����������
int gauss_jordan(double A[][MAX_POINTS], double B[], int n) {
    double augmented[MAX_POINTS][MAX_POINTS + 1];
 
    // �����������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = A[i][j];
        }
        augmented[i][n] = B[i];
    }
 
    // ��˹-�ǵ���Ԫ��
    for (int i = 0; i < n; i++) {
        if (augmented[i][i] == 0) {
            return 0;  // ������Խ���Ԫ��Ϊ0������󲻿���
        }
 
        // ��һ��
        double pivot = augmented[i][i];
        for (int j = 0; j < n + 1; j++) {
            augmented[i][j] /= pivot;
        }
 
        // ��ȥ��
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double factor = augmented[j][i];
                for (int k = 0; k < n + 1; k++) {
                    augmented[j][k] -= factor * augmented[i][k];
                }
            }
        }
    }
 
    // ����洢�� B ��
    for (int i = 0; i < n; i++) {
        B[i] = augmented[i][n];
    }
 
    return 1;
}
 
// ��С���˷�����ʽ���
void polynomial_fit(double x[], double y[], int n, int degree, double coeffs[]) {
    double A[MAX_POINTS][MAX_POINTS] = {0};
    double b[MAX_POINTS] = {0};
    double AT[MAX_POINTS][MAX_POINTS] = {0};
    double ATA[MAX_POINTS][MAX_POINTS] = {0};
 
    // �������� A ������ b
    for (int i = 0; i < n; i++) {
        double xi = 1;
        for (int j = 0; j <= degree; j++) {
            A[i][j] = xi;
            xi *= x[i];  // ���� x^j
        }
        b[i] = y[i];
    }
 
    // ���� A^T
    transpose(A, AT, n, degree + 1);
    // ���� A^T * A
    matmul(AT, A, ATA, degree + 1, n);  // ��ȷ������������ A
    // ���� A^T * b
    matmul(AT, b, b, degree + 1, n);    // ��ȷ�������� b
 
 
    // ��� (A^T * A)^{-1} * (A^T * b) �õ�ϵ��
    if (!gauss_jordan(ATA, b, degree + 1)) {
        printf("Error: Matrix inversion failed.\n");
        return;
    }
 
    // �����Ͻ��
    for (int i = 0; i <= degree; i++) {
        coeffs[i] = b[i];
    }
}
 
// ��ӡ��ϵĶ���ʽϵ��
void print_coeffs(double coeffs[], int degree) {
    printf("��ϵĶ���ʽϵ����\n");
    for (int i = 0; i <= degree; i++) {
        printf("a[%d] = %lf\n", i, coeffs[i]);
    }
}
 
int main() {
    int n, degree;
 
    // �������ݵ�������Ͷ���ʽ�Ľ���
    printf("���������ݵ��������");
    scanf("%d", &n);
    printf("��������ϵĶ���ʽ������");
    scanf("%d", &degree);
 
    double x[MAX_POINTS], y[MAX_POINTS], coeffs[MAX_POINTS];
 
    // �������ݵ�
    printf("���������ݵ� (x, y)��\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = ", i);
        scanf("%lf", &x[i]);
        printf("y[%d] = ", i);
        scanf("%lf", &y[i]);
    }
 
    // ִ�ж���ʽ���
    polynomial_fit(x, y, n, degree, coeffs);
 
    // ��ӡ���
    print_coeffs(coeffs, degree);
 
    return 0;
}
