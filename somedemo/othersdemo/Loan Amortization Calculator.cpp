#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double principal = 200000.0;    // Loan amount
    double annualRate = 4.5;        // Annual interest rate (%)
    int years = 30;                 // Loan term
    
    double monthlyRate = annualRate / 100 / 12;
    int numPayments = years * 12;
    
    // Monthly payment calculation
    double monthlyPayment = principal * monthlyRate * pow(1 + monthlyRate, numPayments) 
                           / (pow(1 + monthlyRate, numPayments) - 1);
    
    cout << "Month\tPayment\t\tPrincipal\tInterest\tBalance" << endl;
    
    double balance = principal;
    for (int month = 1; month <= numPayments; month++) {
        double interest = balance * monthlyRate;
        double principalPaid = monthlyPayment - interest;
        balance -= principalPaid;
        
        cout << month << "\t" << monthlyPayment << "\t" 
             << principalPaid << "\t" << interest << "\t" << balance << endl;
    }
    return 0;
}
