#include <iostream>
#include <cmath>

using namespace std;

// ʹ�ýṹ���ʾϡ������
struct SparseVector {
    int length;         // ����Ԫ�ظ���
    int indices[100];   // ���֧��100������Ԫ��
    double values[100];
};

// ����ĳ�������Ƿ������ϡ�������У����ض�Ӧ��ֵ�����������򷵻�0��
double getValue(const SparseVector& vec, int index) {
    for (int i = 0; i < vec.length; ++i) {
        if (vec.indices[i] == index) {
            return vec.values[i];
        }
    }
    return 0.0;
}

// ����ϡ���������������ƶ�
double cosine_similarity(const SparseVector& vec1, const SparseVector& vec2) {
    double dot_product = 0.0;
    double norm_vec1 = 0.0;
    double norm_vec2 = 0.0;

    // ������һ�����������з���Ԫ��
    for (int i = 0; i < vec1.length; ++i) {
        int index = vec1.indices[i];
        double value1 = vec1.values[i];

        double value2 = getValue(vec2, index);
        if (value2 != 0.0) {
            dot_product += value1 * value2;
        }

        norm_vec1 += value1 * value1;
    }

    // �����ڶ������������з���Ԫ��
    for (int i = 0; i < vec2.length; ++i) {
        double value2 = vec2.values[i];
        norm_vec2 += value2 * value2;
    }

    // �����������ƶ�
    double denominator = sqrt(norm_vec1) * sqrt(norm_vec2);
    if (denominator == 0.0) {
        return 0.0;  // �������Ϊ0�������ƶ�Ϊ0
    }
    return dot_product / denominator;
}

int main() {
    // ʾ����vec1 = {(0, 1.0), (2, 2.0), (5, 3.0)}
    SparseVector vec1;
    vec1.length = 3;
    vec1.indices[0] = 0; vec1.values[0] = 1.0;
    vec1.indices[1] = 2; vec1.values[1] = 2.0;
    vec1.indices[2] = 5; vec1.values[2] = 3.0;

    // ʾ����vec2 = {(0, 1.0), (1, 2.0), (5, 1.0)}
    SparseVector vec2;
    vec2.length = 3;
    vec2.indices[0] = 0; vec2.values[0] = 1.0;
    vec2.indices[1] = 1; vec2.values[1] = 2.0;
    vec2.indices[2] = 5; vec2.values[2] = 1.0;

    // �����������ƶ�
    double similarity = cosine_similarity(vec1, vec2);

    // ������
    cout << "Cosine Similarity: " << similarity << endl;

    return 0;
}
