#include <iostream>
#include <cmath>

using namespace std;

// 使用结构体表示稀疏向量
struct SparseVector {
    int length;         // 非零元素个数
    int indices[100];   // 最多支持100个非零元素
    double values[100];
};

// 查找某个索引是否存在于稀疏向量中，返回对应的值（若不存在则返回0）
double getValue(const SparseVector& vec, int index) {
    for (int i = 0; i < vec.length; ++i) {
        if (vec.indices[i] == index) {
            return vec.values[i];
        }
    }
    return 0.0;
}

// 计算稀疏向量的余弦相似度
double cosine_similarity(const SparseVector& vec1, const SparseVector& vec2) {
    double dot_product = 0.0;
    double norm_vec1 = 0.0;
    double norm_vec2 = 0.0;

    // 遍历第一个向量的所有非零元素
    for (int i = 0; i < vec1.length; ++i) {
        int index = vec1.indices[i];
        double value1 = vec1.values[i];

        double value2 = getValue(vec2, index);
        if (value2 != 0.0) {
            dot_product += value1 * value2;
        }

        norm_vec1 += value1 * value1;
    }

    // 遍历第二个向量的所有非零元素
    for (int i = 0; i < vec2.length; ++i) {
        double value2 = vec2.values[i];
        norm_vec2 += value2 * value2;
    }

    // 计算余弦相似度
    double denominator = sqrt(norm_vec1) * sqrt(norm_vec2);
    if (denominator == 0.0) {
        return 0.0;  // 如果范数为0，则相似度为0
    }
    return dot_product / denominator;
}

int main() {
    // 示例：vec1 = {(0, 1.0), (2, 2.0), (5, 3.0)}
    SparseVector vec1;
    vec1.length = 3;
    vec1.indices[0] = 0; vec1.values[0] = 1.0;
    vec1.indices[1] = 2; vec1.values[1] = 2.0;
    vec1.indices[2] = 5; vec1.values[2] = 3.0;

    // 示例：vec2 = {(0, 1.0), (1, 2.0), (5, 1.0)}
    SparseVector vec2;
    vec2.length = 3;
    vec2.indices[0] = 0; vec2.values[0] = 1.0;
    vec2.indices[1] = 1; vec2.values[1] = 2.0;
    vec2.indices[2] = 5; vec2.values[2] = 1.0;

    // 计算余弦相似度
    double similarity = cosine_similarity(vec1, vec2);

    // 输出结果
    cout << "Cosine Similarity: " << similarity << endl;

    return 0;
}
