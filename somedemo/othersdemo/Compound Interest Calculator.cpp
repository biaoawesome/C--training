#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double principal = 10000.0;     // Initial investment
    double annualRate = 5.0;        // Annual interest rate (%)
    double years = 10.0;            // Investment period
    
    cout << "Year\tBalance" << endl;
    
    // Calculate compound interest annually
    for (int year = 1; year <= years; year++) {
        double balance = principal * pow(1.0 + annualRate/100, year);
        cout << year << "\t" << balance << endl;
    }
    
    // Final value
    double finalAmount = principal * pow(1.0 + annualRate/100, years);
    cout << "Final amount: " << finalAmount << endl;
    return 0;
}
