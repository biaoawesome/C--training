#include <iostream>
using namespace std;

int main() {
    double a = 1.0;             // First term
    double r = 0.5;             // Common ratio
    int n = 20;                 // Number of terms
    double sum = 0.0;
    
    cout << "Term\tValue\t\tSum" << endl;
    
    // Calculate geometric series
    double term = a;
    for (int i = 1; i <= n; i++) {
        sum += term;
        cout << i << "\t" << term << "\t\t" << sum << endl;
        term *= r;
    }
    
    // Theoretical sum: a/(1-r)
    double theoretical = a / (1 - r);
    cout << "Theoretical sum: " << theoretical << endl;
    return 0;
}
