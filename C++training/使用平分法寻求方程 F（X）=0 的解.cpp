#include <iostream>
#include <cmath>
 
// ���巽�� F(x) = 0, ���� F(x) = x^3 - x - 2
double F(double x) {
    return x * x * x - x - 2;
}
 
// ƽ�ַ���ⷽ�� F(x) = 0
double bisectionMethod(double a, double b, double epsilon) {
    // ����ʼ�����Ƿ����� F(a) * F(b) < 0
    if (F(a) * F(b) > 0) {
        std::cerr << "Initial interval does not satisfy the condition F(a) * F(b) < 0." << std::endl;
        return NAN;
    }
 
    double c = a; // �е�
    while ((b - a) / 2.0 > epsilon) {
        c = (a + b) / 2.0; // �����е�
        if (F(c) == 0.0) {
            break; // �ҵ���ȷ�ĸ�
        }
        // ���ݷ���ѡ���µ�����
        else if (F(a) * F(c) < 0) {
            b = c;
        } else {
            a = c;
        }
    }
    return c;
}
 
int main() {
    // �趨��ʼ��������̶�
    double a = 1.0, b = 2.0;
    double epsilon = 0.0001;
 
    // ����ƽ�ַ���������
    double root = bisectionMethod(a, b, epsilon);
 
    // ������
    if (!std::isnan(root)) {
        std::cout << "The root of the equation is approximately: " << root << std::endl;
    }
 
    return 0;
}
