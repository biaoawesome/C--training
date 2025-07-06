#include <iostream>
#include <cmath>

using namespace std;

const int MAX_POINTS = 1024; // 最大支持的点数（根据需要调整）

// 定义点的结构体
struct Point {
    double x, y;
};

// 生成圆弧上的点网格
void generateArcPoints(double cx, double cy, double r, double theta1, double theta2, int N,
                       Point points[]) {
    if (N <= 0 || N > MAX_POINTS) return;

    double deltaTheta = theta2 - theta1; // 总角度
    double dTheta = deltaTheta / (N - 1); // 角度间隔

    for (int k = 0; k < N; ++k) {
        double theta = theta1 + k * dTheta; // 当前极角
        points[k].x = cx + r * cos(theta);  // 转换为笛卡尔坐标
        points[k].y = cy + r * sin(theta);
    }
}

int main() {
    // 输入圆弧参数
    double cx, cy, r, theta1, theta2;
    int N;

    cout << "Enter the center (cx, cy): ";
    cin >> cx >> cy;
    cout << "Enter the radius (r): ";
    cin >> r;
    cout << "Enter the start angle (theta1, in radians): ";
    cin >> theta1;
    cout << "Enter the end angle (theta2, in radians): ";
    cin >> theta2;
    cout << "Enter the number of points (N): ";
    cin >> N;

    if (N <= 0 || N > MAX_POINTS) {
        cerr << "Invalid number of points.\n";
        return 1;
    }

    // 声明静态数组
    Point points[MAX_POINTS];

    // 生成点网格
    generateArcPoints(cx, cy, r, theta1, theta2, N, points);

    // 输出点网格
    cout << "Generated points on the arc:\n";
    for (int i = 0; i < N; ++i) {
        cout << "(" << points[i].x << ", " << points[i].y << ")\n";
    }

    return 0;
}
