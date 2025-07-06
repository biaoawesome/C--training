#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

const int MAX_POINTS = 100; // 假设最多处理 100 个点

struct Point {
    double x, y;
    int cluster; // 所属簇编号
};

// 计算两点之间的欧几里得距离
double euclideanDistance(const Point& p1, const Point& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// K均值聚类算法
void kMeans(Point points[], int n, int K) {
    Point centroids[10];      // 最多支持 10 个簇
    Point newCentroids[10];   // 用于更新簇中心
    int pointCounts[10];      // 每个簇的点数

    // 随机初始化K个簇中心
    std::srand(std::time(0));
    for (int i = 0; i < K; ++i) {
        centroids[i] = points[std::rand() % n];
    }

    bool converged = false;
    while (!converged) {
        // 步骤1：为每个数据点分配簇
        for (int i = 0; i < n; ++i) {
            double minDistance = std::numeric_limits<double>::max();
            int closestCluster = -1;
            for (int k = 0; k < K; ++k) {
                double dist = euclideanDistance(points[i], centroids[k]);
                if (dist < minDistance) {
                    minDistance = dist;
                    closestCluster = k;
                }
            }
            points[i].cluster = closestCluster;
        }

        // 步骤2：重置新簇中心与计数器
        for (int k = 0; k < K; ++k) {
            newCentroids[k].x = 0.0;
            newCentroids[k].y = 0.0;
            pointCounts[k] = 0;
        }

        // 累加坐标，统计每簇点数
        for (int i = 0; i < n; ++i) {
            int cluster = points[i].cluster;
            newCentroids[cluster].x += points[i].x;
            newCentroids[cluster].y += points[i].y;
            pointCounts[cluster]++;
        }

        // 取平均得到新的簇中心
        for (int k = 0; k < K; ++k) {
            if (pointCounts[k] > 0) {
                newCentroids[k].x /= pointCounts[k];
                newCentroids[k].y /= pointCounts[k];
            }
        }

        // 判断是否收敛
        converged = true;
        for (int k = 0; k < K; ++k) {
            if (euclideanDistance(centroids[k], newCentroids[k]) > 1e-6) {
                converged = false;
                break;
            }
        }

        // 更新簇中心
        for (int k = 0; k < K; ++k) {
            centroids[k] = newCentroids[k];
        }
    }
}

void printClusters(const Point points[], int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << "Point (" << points[i].x << ", " << points[i].y 
                  << ") is in cluster " << points[i].cluster << std::endl;
    }
}

int main() {
    // 测试数据：一组二维点
    Point points[] = {
        {1.0, 2.0, -1}, {1.5, 1.8, -1}, {5.0, 8.0, -1}, {8.0, 8.0, -1},
        {1.0, 0.6, -1}, {9.0, 11.0, -1}, {8.0, 2.0, -1}, {10.0, 2.0, -1},
        {9.0, 3.0, -1}, {7.0, 5.0, -1}
    };
    int n = sizeof(points) / sizeof(points[0]); // 自动计算点的数量
    int K = 3; // 设置簇的数量

    // 执行K均值聚类
    kMeans(points, n, K);

    // 输出聚类结果
    printClusters(points, n);

    return 0;
}
