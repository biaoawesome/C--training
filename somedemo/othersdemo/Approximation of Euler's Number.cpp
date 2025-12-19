#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double e = 1.0;      // Approximation of e
    double term = 1.0;   // Current term in series
    int n = 1;           // Term counter
    double precision = 1e-15;
    
    // Calculate e using Taylor series: e = 1 + 1/1! + 1/2! + 1/3! + ...
    while (term > precision) {
        term /= n;           // Calculate next term
        e += term;           // Add to sum
        n++;                 // Increment counter
    }
    
    cout << fixed << setprecision(20);
    cout << "Approximated e: " << e << endl;
    cout << "Actual e: " << 2.71828182845904523536 << endl;
    return 0;
}
