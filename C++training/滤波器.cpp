#include <stdio.h>
#include <stdlib.h>
 
// һά��ͨ�˲���ʵ��
void low_pass_filter(double *input, double *output, int length, int kernel_size) {
    int half_kernel = kernel_size / 2;
    
    // ��ÿ�������źŵ�����˲�
    for (int i = 0; i < length; i++) {
        double sum = 0.0;
        int count = 0;
 
        // �Ե�ǰ�źŵ���о��������������Χ���ڵ�ƽ��ֵ
        for (int j = -half_kernel; j <= half_kernel; j++) {
            int index = i + j;
            
            // ����߽�������������Խ��
            if (index >= 0 && index < length) {
                sum += input[index];
                count++;
            }
        }
        
        // ����������Χ���ڵ�ƽ��ֵ
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
    // ʾ�������ź�
    double input[] = {2.0, 3.0, 4.0, 3.0, 5.0, 6.0, 4.0, 3.0, 2.0};
    int length = sizeof(input) / sizeof(input[0]);
 
    // �������
    double output[length];
 
    // �˲����ĺ˴�С�����ڴ�С��
    int kernel_size = 3;  // ����Ե������ֵ�������˲�����ƽ���̶�
 
    // Ӧ�õ�ͨ�˲���
    low_pass_filter(input, output, length, kernel_size);
 
    // ��ӡ��������
    printf("ԭʼ�ź�: ");
    print_array(input, length);
    printf("�˲�����ź�: ");
    print_array(output, length);
 
    return 0;
}
