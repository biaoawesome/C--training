#include <iostream>
using namespace std;

int main() {
    double number = 25.0;       // Number to find sqrt of
    double guess = number / 2;  // Initial guess
    double tolerance = 0.00001; // Precision
    
    cout << "Iteration\tGuess" << endl;
    
    // Newton-Raphson iteration
    int iteration = 0;
    while (fabs(guess * guess - number) > tolerance) {
        guess = (guess + number / guess) / 2;
        iteration++;
        cout << iteration << "\t\t" << guess << endl;
    }
    
    cout << "Square root of " << number << ": " << guess << endl;
    return 0;
}
