#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Bond class representing a standard coupon-paying bond
class Bond {
private:
    double faceValue;     // Face value of the bond
    double couponRate;    // Annual coupon rate
    double maturity;      // Maturity in years
    double marketPrice;   // Current market price

public:
    Bond(double faceValue, double couponRate, double maturity, double marketPrice)
        : faceValue(faceValue), couponRate(couponRate), maturity(maturity), marketPrice(marketPrice) {}

    // Getters
    double getFaceValue() const { return faceValue; }
    double getCouponRate() const { return couponRate; }
    double getMaturity() const { return maturity; }
    double getMarketPrice() const { return marketPrice; }

    // Calculate present value of the bond given a yield (YTM)
    double calculatePresentValue(double yield) const {
        double presentValue = 0.0;
        double couponPayment = faceValue * couponRate;

        for (int t = 1; t <= maturity; ++t) {
            presentValue += couponPayment / pow(1 + yield, t);
        }

        presentValue += faceValue / pow(1 + yield, maturity);
        return presentValue;
    }

    // Calculate Yield to Maturity (YTM) using Newton-Raphson method
    double calculateYield(double epsilon = 1e-6) const {
        double lowerBound = 0.0001;
        double upperBound = 1.0;
        double guess = 0.05;
        double price = marketPrice;

        while (upperBound - lowerBound > epsilon) {
            double priceAtGuess = calculatePresentValue(guess);
            double derivative = 0.0;

            for (int t = 1; t <= maturity; ++t) {
                derivative -= t * (faceValue * couponRate) / pow(1 + guess, t + 1);
            }
            derivative -= maturity * faceValue / pow(1 + guess, maturity + 1);

            guess = guess - (priceAtGuess - price) / derivative;

            if (guess < lowerBound) guess = lowerBound;
            if (guess > upperBound) guess = upperBound;
        }

        return guess;
    }

    // Calculate bond price given a yield
    double calculatePrice(double yield) const {
        return calculatePresentValue(yield);
    }
};

// Constant for maximum number of term structure entries
const int MAX_RATES = 10;

// Term structure class to represent yield curve
class TermStructure {
private:
    double maturities[MAX_RATES];  // Array to store maturity times
    double rates[MAX_RATES];       // Array to store corresponding yields
    int count;                     // Number of stored values

public:
    TermStructure(const double maturitiesArr[], const double ratesArr[], int size)
        : count(size) {
        for (int i = 0; i < size && i < MAX_RATES; ++i) {
            maturities[i] = maturitiesArr[i];
            rates[i] = ratesArr[i];
        }
    }

    // Get yield for a specific maturity
    double getYield(double maturity) const {
        for (int i = 0; i < count; ++i) {
            if (maturities[i] == maturity) {
                return rates[i];
            }
        }
        return -1.0;  // Return invalid value if not found
    }

    // Print the term structure
    void printStructure() const {
        for (int i = 0; i < count; ++i) {
            cout << "Maturity: " << maturities[i] << " years, Rate: " << rates[i] * 100 << "%" << endl;
        }
    }
};

int main() {
    // Define the term structure (yield curve) using static arrays
    double maturities[] = {1, 2, 3, 5, 10};
    double rates[] = {0.02, 0.025, 0.03, 0.035, 0.04};
    int size = sizeof(maturities) / sizeof(maturities[0]);

    TermStructure termStructure(maturities, rates, size);
    termStructure.printStructure();

    // Create a bond: $1000 face value, 5% coupon, 3-year maturity, current price $1050
    Bond bond(1000, 0.05, 3, 1050);

    // Calculate Yield to Maturity (YTM)
    double ytm = bond.calculateYield();
    cout << "Calculated Yield (YTM): " << fixed << setprecision(4) << ytm * 100 << "%" << endl;

    // Calculate bond price from YTM
    double price = bond.calculatePrice(ytm);
    cout << "Calculated Bond Price at Yield: " << fixed << setprecision(2) << price << endl;

    // Use term structure to get the yield for 3 years and calculate bond price
    double rateAtMaturity = termStructure.getYield(3);  // Get 3-year yield
    double priceUsingTermStructure = bond.calculatePrice(rateAtMaturity);
    cout << "Bond Price using Term Structure Rate: " << fixed << setprecision(2) << priceUsingTermStructure << endl;

    return 0;
}
