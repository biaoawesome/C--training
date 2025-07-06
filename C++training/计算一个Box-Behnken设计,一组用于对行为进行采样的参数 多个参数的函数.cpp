#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_PARAMS = 10;     // ����������
const int MAX_COMBINATIONS = 100; // �������������ݲ����������㣩

// ��������ṹ��
struct Parameter {
    string name;
    double low;
    double mid;
    double high;
};

// ���� Box-Behnken ��ƵĲ������
int generateBoxBehnkenDesign(const Parameter parameters[], int nParams, double design[][MAX_PARAMS]) {
    int designIndex = 0;

    // �����������
    for (int i = 0; i < nParams; ++i) {
        for (int j = i + 1; j < nParams; ++j) {
            double point[MAX_PARAMS];

            // �̶���������Ϊ��ˮƽ
            for (int k = 0; k < nParams; ++k) {
                point[k] = parameters[k].mid;
            }

            // ���õ�ǰ����Ϊ��ˮƽ�͸�ˮƽ
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

    // ������ĵ�
    double centerPoint[MAX_PARAMS];
    for (int i = 0; i < nParams; ++i) {
        centerPoint[i] = parameters[i].mid;
    }
    for (int k = 0; k < nParams; ++k)
        design[designIndex][k] = centerPoint[k];
    ++designIndex;

    return designIndex; // �����������
}

int main() {
    // �������
    Parameter parameters[] = {
        {"A", 10.0, 20.0, 30.0},
        {"B", 5.0, 10.0, 15.0},
        {"C", 1.0, 2.0, 3.0}
    };
    int nParams = sizeof(parameters) / sizeof(parameters[0]);

    // �洢�������
    double design[MAX_COMBINATIONS][MAX_PARAMS];

    // ���� Box-Behnken ���
    int numCombinations = generateBoxBehnkenDesign(parameters, nParams, design);

    // ����������
    cout << "Box-Behnken Design:\n";
    for (int i = 0; i < numCombinations; ++i) {
        for (int j = 0; j < nParams; ++j) {
            cout << design[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
