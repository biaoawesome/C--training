#include <iostream>
using namespace std;

int main() {
    double sum = 0.0;        // Sum of squares
    double n = 10.0;         // Number of terms
    double offset = 5.0;     // Starting offset
    
    // Calculate sum of (i + offset)^2 for i from 1 to n
    for (double i = 1.0; i <= n; i += 1.0) {
        double value = i + offset;
        sum += value * value;
        cout << "Term " << i << ": " << value*value << endl;
    }
    
    cout << "Total sum: " << sum << endl;
    cout << "Average: " << sum / n << endl;
    return 0;
}
