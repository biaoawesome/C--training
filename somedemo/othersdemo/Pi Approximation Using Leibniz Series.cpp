#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double pi = 0.0;         // Approximation of ¦Ð
    double term;             // Current term value
    double denominator = 1.0; // Denominator in series
    double sign = 1.0;       // Alternating sign
    double precision = 0.00001;
    
    // Leibniz formula: ¦Ð/4 = 1 - 1/3 + 1/5 - 1/7 + ...
    int iterations = 0;
    do {
        term = sign / denominator;
        pi += term;
        sign *= -1;           // Flip sign
        denominator += 2;     // Next odd number
        iterations++;
    } while (fabs(term) > precision);
    
    pi *= 4; // Multiply by 4 to get ¦Ð
    cout << fixed << setprecision(10);
    cout << "Approximated ¦Ð: " << pi << " after " << iterations << " iterations" << endl;
    return 0;
}
