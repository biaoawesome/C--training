#include <iostream>
using namespace std;

int main() {
    double basePrice = 1000.0;      // Base product price
    double annualDiscount = 3.0;    // Annual discount rate (%)
    double years = 5.0;
    
    cout << "Year\tDiscounted Price\tCumulative Savings" << endl;
    
    double previousPrice = basePrice;
    for (int y = 1; y <= years; y++) {
        double discountRate = annualDiscount * y / 100;
        double currentPrice = basePrice * (1 - discountRate);
        double savings = previousPrice - currentPrice;
        cout << y << "\t" << currentPrice << "\t\t" << savings << endl;
        previousPrice = currentPrice;
    }
    return 0;
}
