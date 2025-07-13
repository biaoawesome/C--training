#include <iostream>
#include <cmath>
#include <iomanip>

// Configuration: Maximum number of periods supported
#define MAX_PERIODS 1000  // Max number of payment periods

// Bond parameter structure
struct BondParams {
    double faceValue;     // Face value of the bond
    double couponRate;    // Annual coupon rate (e.g., 5% = 0.05)
    int maturity;         // Total number of periods
    int frequency;        // Number of payments per year
    double discountRate;  // Discount rate (annual)
};

// Cash flow structure
struct CashFlow {
    double interest;   // Interest payment per period
    double principal;  // Principal payment per period
    double total;      // Total payment per period
};

// Generate amortizing cash flows
int generateCashFlows(const BondParams& params, CashFlow cashFlows[]) {
    double r = params.couponRate / params.frequency;  // Periodic interest rate
    int n = params.maturity;                         // Total number of periods
    double PMT = (r * params.faceValue) / (1 - pow(1 + r, -n)); // Payment per period

    double remainingPrincipal = params.faceValue;

    for (int t = 0; t < n; ++t) {
        double interest = r * remainingPrincipal;
        double principal = PMT - interest;
        remainingPrincipal -= principal;

        cashFlows[t] = {interest, principal, PMT};
    }

    return n;  // Return number of generated cash flows
}

// Calculate Net Present Value (NPV)
double calculateNPV(const CashFlow cashFlows[], int count, double discountRate, int frequency) {
    double npv = 0.0;
    double r = discountRate / frequency;

    for (int t = 0; t < count; ++t) {
        npv += cashFlows[t].total / pow(1 + r, t + 1);
    }

    return npv;
}

// Calculate Duration
double calculateDuration(const CashFlow cashFlows[], int count, double discountRate, int frequency, double npv) {
    double duration = 0.0;
    double r = discountRate / frequency;

    for (int t = 0; t < count; ++t) {
        duration += (t + 1) * cashFlows[t].total / pow(1 + r, t + 1);
    }

    return duration / npv;
}

// Calculate Convexity
double calculateConvexity(const CashFlow cashFlows[], int count, double discountRate, int frequency, double npv) {
    double convexity = 0.0;
    double r = discountRate / frequency;

    for (int t = 0; t < count; ++t) {
        convexity += (t + 1) * (t + 2) * cashFlows[t].total / pow(1 + r, t + 3);
    }

    return convexity / npv;
}

// Main function
int main() {
    // Define bond parameters
    BondParams params = {
        100000.0,   // Face value
        0.05,       // Annual coupon rate (5%)
        60,         // Maturity (60 periods)
        12,         // Monthly payments
        0.04        // Annual discount rate (4%)
    };

    // Check if maturity exceeds max allowed
    if (params.maturity > MAX_PERIODS) {
        std::cerr << "Error: Maturity exceeds maximum allowed periods." << std::endl;
        return 1;
    }

    // Use static array to avoid stack overflow
    static CashFlow cashFlows[MAX_PERIODS];

    // Generate cash flows
    int cashFlowCount = generateCashFlows(params, cashFlows);

    // Compute NPV, Duration, and Convexity
    double npv = calculateNPV(cashFlows, cashFlowCount, params.discountRate, params.frequency);
    double duration = calculateDuration(cashFlows, cashFlowCount, params.discountRate, params.frequency, npv);
    double convexity = calculateConvexity(cashFlows, cashFlowCount, params.discountRate, params.frequency, npv);

    // Output results
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Net Present Value (NPV): " << npv << std::endl;
    std::cout << "Duration: " << duration << std::endl;
    std::cout << "Convexity: " << convexity << std::endl;

    // Output detailed cash flow schedule
    std::cout << "\nPeriod\tInterest\tPrincipal\tTotal Payment\n";
    for (int t = 0; t < cashFlowCount; ++t) {
        std::cout << t + 1 << "\t"
                  << cashFlows[t].interest << "\t"
                  << cashFlows[t].principal << "\t"
                  << cashFlows[t].total << std::endl;
    }

    return 0;
}
