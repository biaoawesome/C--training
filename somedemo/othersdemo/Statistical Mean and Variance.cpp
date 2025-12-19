#include <iostream>
using namespace std;

int main() {
    double data[] = {12.5, 18.3, 22.1, 15.7, 19.9, 16.4, 21.2, 17.8, 20.0, 14.6};
    int n = 10;
    
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    double mean = sum / n;
    
    double varianceSum = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = data[i] - mean;
        varianceSum += diff * diff;
    }
    double variance = varianceSum / n;
    double stdDev = sqrt(variance);
    
    cout << "Mean: " << mean << endl;
    cout << "Variance: " << variance << endl;
    cout << "Std Dev: " << stdDev << endl;
    return 0;
}
