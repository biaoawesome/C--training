#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define IMAGE_WIDTH  5
#define IMAGE_HEIGHT 5
 
// ��˹�˲�����
void gaussian_filter(double *image, double *output, int width, int height, double sigma) {
    int kernel_size = (int)(6 * sigma + 1);
    if (kernel_size % 2 == 0) {
        kernel_size++;  // ȷ���˵Ĵ�С������
    }
 
    // �����˹��
    double *kernel = (double *)malloc(kernel_size * kernel_size * sizeof(double));
    double sum = 0.0;
    int half_kernel_size = kernel_size / 2;
 
    // ���ɸ�˹��
    for (int i = -half_kernel_size; i <= half_kernel_size; i++) {
        for (int j = -half_kernel_size; j <= half_kernel_size; j++) {
            kernel[(i + half_kernel_size) * kernel_size + (j + half_kernel_size)] =
                exp(-(i * i + j * j) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            sum += kernel[(i + half_kernel_size) * kernel_size + (j + half_kernel_size)];
        }
    }
 
    // ��һ����˹��
    for (int i = 0; i < kernel_size; i++) {
        for (int j = 0; j < kernel_size; j++) {
            kernel[i * kernel_size + j] /= sum;
        }
    }
 
    // �������
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
 
    // �ͷŸ�˹���ڴ�
    free(kernel);
}
 
// ��ӡͼ�񣨶�ά���飩
void print_image(double *image, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%0.2f ", image[y * width + x]);
        }
        printf("\n");
    }
}
 
int main() {
    // ����һ��5x5��ͼ������ֵ��
    double image[IMAGE_HEIGHT][IMAGE_WIDTH] = {
        {255, 255, 255, 255, 255},
        {255, 100, 100, 100, 255},
        {255, 100, 50, 100, 255},
        {255, 100, 100, 100, 255},
        {255, 255, 255, 255, 255}
    };
 
    double output[IMAGE_HEIGHT][IMAGE_WIDTH];
 
    // �����˹�˲��ı�׼�sigmaֵ��
    double sigma = 1.0;
 
    // Ӧ�ø�˹�˲�
    gaussian_filter(&image[0][0], &output[0][0], IMAGE_WIDTH, IMAGE_HEIGHT, sigma);
 
    // ��ӡ���ͼ��
    printf("Original Image:\n");
    print_image(&image[0][0], IMAGE_WIDTH, IMAGE_HEIGHT);
 
    printf("\nFiltered Image:\n");
    print_image(&output[0][0], IMAGE_WIDTH, IMAGE_HEIGHT);
 
    return 0;
}
