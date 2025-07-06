#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_PARAMS = 10;     // 最大参数数量
const int MAX_COMBINATIONS = 100; // 最大组合数（根据参数个数估算）

// 定义参数结构体
struct Parameter {
    string name;
    double low;
    double mid;
    double high;
};

// 生成 Box-Behnken 设计的参数组合
int generateBoxBehnkenDesign(const Parameter parameters[], int nParams, double design[][MAX_PARAMS]) {
    int designIndex = 0;

    // 生成两两组合
    for (int i = 0; i < nParams; ++i) {
        for (int j = i + 1; j < nParams; ++j) {
            double point[MAX_PARAMS];

            // 固定其他参数为中水平
            for (int k = 0; k < nParams; ++k) {
                point[k] = parameters[k].mid;
            }

            // 设置当前参数为低水平和高水平
            point[i] = parameters[i].low;
            point[j] = parameters[j].low;
            for (int k = 0; k < nParams; ++k)
                design[designIndex][k] = point[k];
            ++designIndex;

            point[i] = parameters[i].low;
            point[j] = parameters[j].high;
            for (int k = 0; k < nParams; ++k)
                design[designIndex][k] = point[k];
            ++designIndex;

            point[i] = parameters[i].high;
            point[j] = parameters[j].low;
            for (int k = 0; k < nParams; ++k)
                design[designIndex][k] = point[k];
            ++designIndex;

            point[i] = parameters[i].high;
            point[j] = parameters[j].high;
            for (int k = 0; k < nParams; ++k)
                design[designIndex][k] = point[k];
            ++designIndex;
        }
    }

    // 添加中心点
    double centerPoint[MAX_PARAMS];
    for (int i = 0; i < nParams; ++i) {
        centerPoint[i] = parameters[i].mid;
    }
    for (int k = 0; k < nParams; ++k)
        design[designIndex][k] = centerPoint[k];
    ++designIndex;

    return designIndex; // 返回总组合数
}

int main() {
    // 定义参数
    Parameter parameters[] = {
        {"A", 10.0, 20.0, 30.0},
        {"B", 5.0, 10.0, 15.0},
        {"C", 1.0, 2.0, 3.0}
    };
    int nParams = sizeof(parameters) / sizeof(parameters[0]);

    // 存储参数组合
    double design[MAX_COMBINATIONS][MAX_PARAMS];

    // 生成 Box-Behnken 设计
    int numCombinations = generateBoxBehnkenDesign(parameters, nParams, design);

    // 输出参数组合
    cout << "Box-Behnken Design:\n";
    for (int i = 0; i < numCombinations; ++i) {
        for (int j = 0; j < nParams; ++j) {
            cout << design[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
