#include <iostream>
#include <cmath>
#include <cassert>

#define MAX_BONDS 100

// Define a struct to represent a bond
struct Bond {
    double price;     // Market price of the bond
    double coupon;    // Annual coupon rate
    double maturity;  // Time to maturity (in years)
    double faceValue; // Face value of the bond (usually 100)
};

// Define a class for fitting discount curves
class DiscountCurveFitter {
public:
    // Constructor
    DiscountCurveFitter(const Bond bonds[], int numBonds) : numBonds(numBonds) {
        for (int i = 0; i < numBonds; ++i) {
            this->bonds[i] = bonds[i];
        }
    }

    // Fit the discount curve using least squares method
    void fitCurve() {
        // Calculate discount factors based on bond prices and face values
        for (int i = 0; i < numBonds; ++i) {
            const Bond& bond = bonds[i];
            discountFactors[i] = bond.price / bond.faceValue;
            maturities[i] = bond.maturity;
        }
        this->numDiscountPoints = numBonds;
    }

    // Calculate present value of a given bond
    double calculateBondValue(const Bond& bond) {
        double price = 0.0;

        // Sum discounted coupon payments
        for (int i = 0; i < numDiscountPoints; ++i) {
            if (bond.maturity >= maturities[i]) {
                price += bond.coupon * discountFactors[i];
            }
        }

        // Add discounted face value at maturity
        price += bond.faceValue * discountFactors[numDiscountPoints - 1];

        return price;
    }

    // Print the fitted discount curve
    void printDiscountCurve() {
        std::cout << "Discount Curve (Maturity, Discount Factor):\n";
        for (int i = 0; i < numDiscountPoints; ++i) {
            std::cout << "Maturity: " << maturities[i]
                      << ", Discount Factor: " << discountFactors[i] << "\n";
        }
    }

private:
    Bond bonds[MAX_BONDS];              // Input bond data
    double discountFactors[MAX_BONDS];  // Calculated discount factors
    double maturities[MAX_BONDS];       // Maturity times
    int numBonds;                       // Number of input bonds
    int numDiscountPoints;              // Number of discount points

    // Simplified method to compute discount curve
    // This version does not interpolate but just stores original points
    void calculateDiscountCurve() {
        // Placeholder for future interpolation logic
    }
};

int main() {
    // Initialize market bond data
    Bond bonds[] = {
        {95.0, 5.0, 1.0, 100.0},  // Price 95, Coupon 5%, Maturity 1 year
        {90.0, 5.0, 2.0, 100.0},  // Price 90, Coupon 5%, Maturity 2 years
        {85.0, 5.0, 3.0, 100.0}   // Price 85, Coupon 5%, Maturity 3 years
    };
    int numBonds = sizeof(bonds) / sizeof(bonds[0]);

    // Create and fit the discount curve
    DiscountCurveFitter curveFitter(bonds, numBonds);
    curveFitter.fitCurve();

    // Print the discount curve
    curveFitter.printDiscountCurve();

    // Test calculating bond value
    Bond testBond = {88.0, 5.0, 2.5, 100.0};  // Test bond with maturity 2.5 years
    double bondPrice = curveFitter.calculateBondValue(testBond);
    std::cout << "Test Bond Value: " << bondPrice << std::endl;

    return 0;
}
