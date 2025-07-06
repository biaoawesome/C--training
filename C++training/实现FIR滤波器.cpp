#include <stdio.h>
#include <stdlib.h>
 
// FIR滤波器函数
void fir_filter(double *x, double *h, double *y, int x_len, int h_len) {
    for (int n = 0; n < x_len; n++) {
        y[n] = 0.0;
        // 卷积运算
        for (int k = 0; k < h_len; k++) {
            if (n - k >= 0) {
                y[n] += h[k] * x[n - k];  // 滤波器系数与输入信号的卷积
            }
        }
    }
}
 
int main() {
    // 示例输入信号
    double x[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0}; // 输入信号
    int x_len = sizeof(x) / sizeof(x[0]); // 输入信号长度
 
    // FIR滤波器系数（例如低通滤波器的简单系数）
    double h[] = {0.2, 0.2, 0.2, 0.2, 0.2};  // 滤波器系数（简单均值滤波器）
    int h_len = sizeof(h) / sizeof(h[0]); // 滤波器系数长度
 
    double y[x_len]; // 存放滤波后的输出信号
 
    // 调用FIR滤波器进行滤波
    fir_filter(x, h, y, x_len, h_len);
 
    // 打印输出信号
    printf("Filtered Signal:\n");
    for (int i = 0; i < x_len; i++) {
        printf("%f ", y[i]);
    }
    printf("\n");
 
    return 0;
}
