#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

const int MAX_POINTS = 100; // ������ദ�� 100 ����

struct Point {
    double x, y;
    int cluster; // �����ر��
};

// ��������֮���ŷ����þ���
double euclideanDistance(const Point& p1, const Point& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// K��ֵ�����㷨
void kMeans(Point points[], int n, int K) {
    Point centroids[10];      // ���֧�� 10 ����
    Point newCentroids[10];   // ���ڸ��´�����
    int pointCounts[10];      // ÿ���صĵ���

    // �����ʼ��K��������
    std::srand(std::time(0));
    for (int i = 0; i < K; ++i) {
        centroids[i] = points[std::rand() % n];
    }

    bool converged = false;
    while (!converged) {
        // ����1��Ϊÿ�����ݵ�����
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

        // ����2�������´������������
        for (int k = 0; k < K; ++k) {
            newCentroids[k].x = 0.0;
            newCentroids[k].y = 0.0;
            pointCounts[k] = 0;
        }

        // �ۼ����꣬ͳ��ÿ�ص���
        for (int i = 0; i < n; ++i) {
            int cluster = points[i].cluster;
            newCentroids[cluster].x += points[i].x;
            newCentroids[cluster].y += points[i].y;
            pointCounts[cluster]++;
        }

        // ȡƽ���õ��µĴ�����
        for (int k = 0; k < K; ++k) {
            if (pointCounts[k] > 0) {
                newCentroids[k].x /= pointCounts[k];
                newCentroids[k].y /= pointCounts[k];
            }
        }

        // �ж��Ƿ�����
        converged = true;
        for (int k = 0; k < K; ++k) {
            if (euclideanDistance(centroids[k], newCentroids[k]) > 1e-6) {
                converged = false;
                break;
            }
        }

        // ���´�����
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
    // �������ݣ�һ���ά��
    Point points[] = {
        {1.0, 2.0, -1}, {1.5, 1.8, -1}, {5.0, 8.0, -1}, {8.0, 8.0, -1},
        {1.0, 0.6, -1}, {9.0, 11.0, -1}, {8.0, 2.0, -1}, {10.0, 2.0, -1},
        {9.0, 3.0, -1}, {7.0, 5.0, -1}
    };
    int n = sizeof(points) / sizeof(points[0]); // �Զ�����������
    int K = 3; // ���ôص�����

    // ִ��K��ֵ����
    kMeans(points, n, K);

    // ���������
    printClusters(points, n);

    return 0;
}
