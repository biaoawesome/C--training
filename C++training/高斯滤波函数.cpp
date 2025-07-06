#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define IMAGE_WIDTH  5
#define IMAGE_HEIGHT 5
 
// 高斯滤波函数
void gaussian_filter(double *image, double *output, int width, int height, double sigma) {
    int kernel_size = (int)(6 * sigma + 1);
    if (kernel_size % 2 == 0) {
        kernel_size++;  // 确保核的大小是奇数
    }
 
    // 计算高斯核
    double *kernel = (double *)malloc(kernel_size * kernel_size * sizeof(double));
    double sum = 0.0;
    int half_kernel_size = kernel_size / 2;
 
    // 生成高斯核
    for (int i = -half_kernel_size; i <= half_kernel_size; i++) {
        for (int j = -half_kernel_size; j <= half_kernel_size; j++) {
            kernel[(i + half_kernel_size) * kernel_size + (j + half_kernel_size)] =
                exp(-(i * i + j * j) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            sum += kernel[(i + half_kernel_size) * kernel_size + (j + half_kernel_size)];
        }
    }
 
    // 归一化高斯核
    for (int i = 0; i < kernel_size; i++) {
        for (int j = 0; j < kernel_size; j++) {
            kernel[i * kernel_size + j] /= sum;
        }
    }
 
    // 卷积操作
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double value = 0.0;
            for (int ky = -half_kernel_size; ky <= half_kernel_size; ky++) {
                for (int kx = -half_kernel_size; kx <= half_kernel_size; kx++) {
                    int iy = y + ky;
                    int ix = x + kx;
                    if (iy >= 0 && iy < height && ix >= 0 && ix < width) {
                        value += image[iy * width + ix] * kernel[(ky + half_kernel_size) * kernel_size + (kx + half_kernel_size)];
                    }
                }
            }
            output[y * width + x] = value;
        }
    }
 
    // 释放高斯核内存
    free(kernel);
}
 
// 打印图像（二维数组）
void print_image(double *image, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%0.2f ", image[y * width + x]);
        }
        printf("\n");
    }
}
 
int main() {
    // 定义一个5x5的图像（像素值）
    double image[IMAGE_HEIGHT][IMAGE_WIDTH] = {
        {255, 255, 255, 255, 255},
        {255, 100, 100, 100, 255},
        {255, 100, 50, 100, 255},
        {255, 100, 100, 100, 255},
        {255, 255, 255, 255, 255}
    };
 
    double output[IMAGE_HEIGHT][IMAGE_WIDTH];
 
    // 定义高斯滤波的标准差（sigma值）
    double sigma = 1.0;
 
    // 应用高斯滤波
    gaussian_filter(&image[0][0], &output[0][0], IMAGE_WIDTH, IMAGE_HEIGHT, sigma);
 
    // 打印输出图像
    printf("Original Image:\n");
    print_image(&image[0][0], IMAGE_WIDTH, IMAGE_HEIGHT);
 
    printf("\nFiltered Image:\n");
    print_image(&output[0][0], IMAGE_WIDTH, IMAGE_HEIGHT);
 
    return 0;
}
