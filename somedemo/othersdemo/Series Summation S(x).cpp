#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x = 2.0;          // Input value
    double sum = 1.0;        // S(x) series sum
    double term = 1.0;       // Current term
    int k = 1;               // Term index
    int maxTerms = 20;
    
    // Calculate series using recurrence relation
    while (k <= maxTerms) {
        term *= -x / k;      // Recurrence: r_k = -r_(k-1) * x / k
        sum += term;         // Add to sum
        k++;
    }
    
    cout << "S(" << x << ") approximation: " << sum << endl;
    cout << "Expected (e^(-x)): " << exp(-x) << endl;
    return 0;
}
