#include <iostream>
#include <cmath>
#include <iomanip>

#define MAX_CASHFLOWS 100  // Maximum number of cashflows a bond can have

// Structure representing a single cashflow
struct Cashflow {
    double amount;   // Amount of the cashflow
    int time;        // Time (in years) when the cashflow is received
};

// Financial product (e.g. Bond) class
class Bond {
private:
    double faceValue;     // Face value of the bond
    double couponRate;    // Annual coupon rate (as a percentage)
    int maturity;         // Maturity in years
    double discountRate;  // Discount rate for present value calculation

    Cashflow cashflows[MAX_CASHFLOWS];  // Static array to store cashflows
    int cashflowCount;                  // Number of cashflows generated

public:
    // Constructor: Initialize bond with given parameters
    Bond(double faceValue, double couponRate, int maturity, double discountRate)
        : faceValue(faceValue), couponRate(couponRate), maturity(maturity),
          discountRate(discountRate), cashflowCount(0) {
        generateCashflows();  // Generate cashflows based on bond parameters
    }

    // Generate annual coupon payments and final principal payment
    void generateCashflows() {
        // Add coupon payments every year
        for (int year = 1; year <= maturity; ++year) {
            double couponPayment = faceValue * couponRate;
            if (cashflowCount < MAX_CASHFLOWS) {
                cashflows[cashflowCount++] = {couponPayment, year};
            } else {
                std::cerr << "Maximum cashflow limit reached. Cannot add more." << std::endl;
                return;
            }
        }

        // Add final principal repayment at maturity
        if (cashflowCount < MAX_CASHFLOWS) {
            cashflows[cashflowCount++] = {faceValue, maturity};
        } else {
            std::cerr << "Maximum cashflow limit reached. Cannot add principal." << std::endl;
        }
    }

    // Calculate present value of all cashflows
    double calculatePresentValue() const {
        double presentValue = 0.0;

        for (int i = 0; i < cashflowCount; ++i) {
            const Cashflow& cf = cashflows[i];
            presentValue += cf.amount / std::pow(1 + discountRate, cf.time);
        }

        return presentValue;
    }

    // Print details of each cashflow
    void printCashflows() const {
        std::cout << "Bond Cashflows:\n";
        for (int i = 0; i < cashflowCount; ++i) {
            std::cout << "Time: " << cashflows[i].time << " year(s), "
                      << "Amount: " << cashflows[i].amount << std::endl;
        }
    }
};

// Main function
int main() {
    // Define bond parameters
    double faceValue = 1000.0;    // Face value
    double couponRate = 0.05;     // 5% coupon rate
    int maturity = 10;            // 10-year maturity
    double discountRate = 0.02;   // 2% risk-free rate

    // Create bond object
    Bond bond(faceValue, couponRate, maturity, discountRate);

    // Output bond cashflows
    bond.printCashflows();

    // Calculate and display bond present value
    double presentValue = bond.calculatePresentValue();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Bond Present Value: " << presentValue << std::endl;

    return 0;
}
