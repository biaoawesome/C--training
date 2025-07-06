#include <stdio.h>
#include <stdlib.h>
 
// FIR�˲�������
void fir_filter(double *x, double *h, double *y, int x_len, int h_len) {
    for (int n = 0; n < x_len; n++) {
        y[n] = 0.0;
        // �������
        for (int k = 0; k < h_len; k++) {
            if (n - k >= 0) {
                y[n] += h[k] * x[n - k];  // �˲���ϵ���������źŵľ��
            }
        }
    }
}
 
int main() {
    // ʾ�������ź�
    double x[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0}; // �����ź�
    int x_len = sizeof(x) / sizeof(x[0]); // �����źų���
 
    // FIR�˲���ϵ���������ͨ�˲����ļ�ϵ����
    double h[] = {0.2, 0.2, 0.2, 0.2, 0.2};  // �˲���ϵ�����򵥾�ֵ�˲�����
    int h_len = sizeof(h) / sizeof(h[0]); // �˲���ϵ������
 
    double y[x_len]; // ����˲��������ź�
 
    // ����FIR�˲��������˲�
    fir_filter(x, h, y, x_len, h_len);
 
    // ��ӡ����ź�
    printf("Filtered Signal:\n");
    for (int i = 0; i < x_len; i++) {
        printf("%f ", y[i]);
    }
    printf("\n");
 
    return 0;
}
