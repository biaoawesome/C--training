#include <stdio.h>
#include <stdlib.h>
 
// 一维低通滤波器实现
void low_pass_filter(double *input, double *output, int length, int kernel_size) {
    int half_kernel = kernel_size / 2;
    
    // 对每个输入信号点进行滤波
    for (int i = 0; i < length; i++) {
        double sum = 0.0;
        int count = 0;
 
        // 对当前信号点进行卷积操作，计算周围窗口的平均值
        for (int j = -half_kernel; j <= half_kernel; j++) {
            int index = i + j;
            
            // 处理边界情况，避免访问越界
            if (index >= 0 && index < length) {
                sum += input[index];
                count++;
            }
        }
        
        // 输出结果是周围窗口的平均值
        output[i] = sum / count;
    }
}
 
void print_array(double *arr, int length) {
    for (int i = 0; i < length; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}
 
int main() {
    // 示例输入信号
    double input[] = {2.0, 3.0, 4.0, 3.0, 5.0, 6.0, 4.0, 3.0, 2.0};
    int length = sizeof(input) / sizeof(input[0]);
 
    // 输出数组
    double output[length];
 
    // 滤波器的核大小（窗口大小）
    int kernel_size = 3;  // 你可以调整这个值来控制滤波器的平滑程度
 
    // 应用低通滤波器
    low_pass_filter(input, output, length, kernel_size);
 
    // 打印输入和输出
    printf("原始信号: ");
    print_array(input, length);
    printf("滤波后的信号: ");
    print_array(output, length);
 
    return 0;
}
