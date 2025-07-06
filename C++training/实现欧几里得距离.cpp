#include <iostream>
#include <cmath>

using namespace std;

// 计算欧几里得距离的函数
double euclideanDistance(const double* point1, const double* point2, int dim) {
    // 确保维度合法
    if (dim <= 0) {
        cerr << "Error: Dimension must be positive!" << endl;
        return -1;
    }

    double sum = 0.0;
    for (int i = 0; i < dim; ++i) {
        double diff = point2[i] - point1[i];
        sum += diff * diff;  // 每个维度差的平方累加
    }

    return sqrt(sum);  // 返回最终的欧几里得距离
}

int main() {
    // 示例：二维空间中的点
    const int dim2 = 2;
    double point1[dim2] = {1.0, 2.0};
    double point2[dim2] = {4.0, 6.0};

    double distance = euclideanDistance(point1, point2, dim2);
    cout << "Euclidean distance between point1 and point2: " << distance << endl;

    // 示例：三维空间中的点
    const int dim3 = 3;
    double point3[dim3] = {1.0, 2.0, 3.0};
    double point4[dim3] = {4.0, 6.0, 8.0};

    distance = euclideanDistance(point3, point4, dim3);
    cout << "Euclidean distance between point3 and point4: " << distance << endl;

    return 0;
}
