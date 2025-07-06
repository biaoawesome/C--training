#include <iostream>
#include <cmath>

using namespace std;

// 2D 超限插值
double transfiniteInterpolation2D(double x, double y, const double boundary[2][2]) {
    double f00 = boundary[0][0]; // f(0, 0)
    double f01 = boundary[0][1]; // f(0, 1)
    double f10 = boundary[1][0]; // f(1, 0)
    double f11 = boundary[1][1]; // f(1, 1)

    double fx0 = (1 - x) * boundary[0][0] + x * boundary[1][0]; // f(x, 0)
    double fx1 = (1 - x) * boundary[0][1] + x * boundary[1][1]; // f(x, 1)
    double f0y = (1 - y) * boundary[0][0] + y * boundary[0][1]; // f(0, y)
    double f1y = (1 - y) * boundary[1][0] + y * boundary[1][1]; // f(1, y)

    double fxy = (1 - x) * f0y + x * f1y +
                 (1 - y) * fx0 + y * fx1 -
                 (1 - x) * (1 - y) * f00 -
                 x * (1 - y) * f10 -
                 (1 - x) * y * f01 -
                 x * y * f11;

    return fxy;
}

// 用于辅助计算 2D 插值（作为子函数）
double interpolate2D(double x, double y, const double boundary[2][2]) {
    return transfiniteInterpolation2D(x, y, boundary);
}

// 3D 超限插值
double transfiniteInterpolation3D(double x, double y, double z, const double boundary[2][2][2]) {
    double f000 = boundary[0][0][0];
    double f001 = boundary[0][0][1];
    double f010 = boundary[0][1][0];
    double f011 = boundary[0][1][1];
    double f100 = boundary[1][0][0];
    double f101 = boundary[1][0][1];
    double f110 = boundary[1][1][0];
    double f111 = boundary[1][1][1];

    // 边界插值
    double fx00[] = {(1 - x) * boundary[0][0][0] + x * boundary[1][0][0]};
    double fx01[] = {(1 - x) * boundary[0][0][1] + x * boundary[1][0][1]};
    double fx10[] = {(1 - x) * boundary[0][1][0] + x * boundary[1][1][0]};
    double fx11[] = {(1 - x) * boundary[0][1][1] + x * boundary[1][1][1]};

    double f0y0[] = {(1 - y) * boundary[0][0][0] + y * boundary[0][1][0]};
    double f0y1[] = {(1 - y) * boundary[0][0][1] + y * boundary[0][1][1]};
    double f1y0[] = {(1 - y) * boundary[1][0][0] + y * boundary[1][1][0]};
    double f1y1[] = {(1 - y) * boundary[1][0][1] + y * boundary[1][1][1]};

    double f00z[] = {(1 - z) * boundary[0][0][0] + z * boundary[0][0][1]};
    double f01z[] = {(1 - z) * boundary[0][1][0] + z * boundary[0][1][1]};
    double f10z[] = {(1 - z) * boundary[1][0][0] + z * boundary[1][0][1]};
    double f11z[] = {(1 - z) * boundary[1][1][0] + z * boundary[1][1][1]};

    // 子平面插值
    double plane0[2][2] = {
        {boundary[0][0][0], boundary[0][1][0]},
        {boundary[1][0][0], boundary[1][1][0]}
    };
    double plane1[2][2] = {
        {boundary[0][0][1], boundary[0][1][1]},
        {boundary[1][0][1], boundary[1][1][1]}
    };

    double fxy0 = interpolate2D(x, y, plane0); // f(x, y, 0)
    double fxy1 = interpolate2D(x, y, plane1); // f(x, y, 1)

    double fxyz = (1 - z) * fxy0 + z * fxy1;

    return fxyz;
}

int main() {
    // 2D 示例
    double boundary2D[2][2] = {
        {1.0, 2.0}, // f(0, y)
        {3.0, 4.0}  // f(1, y)
    };

    double x = 0.5;
    double y = 0.5;
    double result2D = transfiniteInterpolation2D(x, y, boundary2D);
    cout << "2D Interpolation at (" << x << ", " << y << "): " << result2D << "\n";

    // 3D 示例
    double boundary3D[2][2][2] = {
        {{1.0, 2.0}, {3.0, 4.0}}, // f(0, y, z)
        {{5.0, 6.0}, {7.0, 8.0}}  // f(1, y, z)
    };

    double z = 0.5;
    double result3D = transfiniteInterpolation3D(x, y, z, boundary3D);
    cout << "3D Interpolation at (" << x << ", " << y << ", " << z << "): " << result3D << "\n";

    return 0;
}
