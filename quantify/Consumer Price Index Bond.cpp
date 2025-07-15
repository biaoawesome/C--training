#include <iostream>
#include <cmath>
#include <random>

using namespace std;

// Constants
const int MAX_SIMULATIONS = 10000;

// CPI Bond structure
typedef struct {
    double principal;       // Face value
    double couponRate;      // Annual coupon rate
    int maturityYears;      // Maturity in years
    double inflationRate;   // Inflation rate
} CPIBond;

// Market simulator structure
typedef struct {
    double inflationRate;       // Current inflation rate
    double inflationVolatility; // Inflation volatility
    mt19937 rng;                // Random number generator
} MarketSimulator;

// Bond switch strategy
typedef struct {
    CPIBond* bondA;
    CPIBond* bondB;
} BondSwitchStrategy;

// === CPIBond functions ===

// Calculate cash flow in a given year
double calculateCashFlow(CPIBond* bond, int year) {
    return bond->couponRate * bond->principal * pow(1 + bond->inflationRate, year);
}

// Price the bond using discounted cash flows
double priceBond(CPIBond* bond) {
    double price = 0.0;
    for (int t = 1; t <= bond->maturityYears; ++t) {
        double cashFlow = calculateCashFlow(bond, t);
        price += cashFlow / pow(1 + bond->inflationRate, t); // Discount
    }
    price += bond->principal / pow(1 + bond->inflationRate, bond->maturityYears); // Discount principal
    return price;
}

// === MarketSimulator functions ===

// Initialize market simulator
void initMarketSimulator(MarketSimulator* market, double initialInflationRate, double inflationVolatility) {
    market->inflationRate = initialInflationRate;
    market->inflationVolatility = inflationVolatility;
    market->rng = mt19937(random_device()());
}

// Simulate future inflation rate
double simulateInflationRate(MarketSimulator* market) {
    normal_distribution<double> dist(market->inflationRate, market->inflationVolatility);
    market->inflationRate = dist(market->rng);
    return market->inflationRate;
}

// === BondSwitchStrategy functions ===

// Select bond based on price
CPIBond* selectBond(BondSwitchStrategy* strategy) {
    double priceA = priceBond(strategy->bondA);
    double priceB = priceBond(strategy->bondB);
    return (priceA < priceB) ? strategy->bondA : strategy->bondB;
}

// === Monte Carlo Simulator (no class) ===

// Run Monte Carlo simulation
void runMonteCarloSimulation(int numSimulations, MarketSimulator* market, BondSwitchStrategy* strategy) {
    double totalReturn = 0.0;

    for (int i = 0; i < numSimulations; ++i) {
        double inflationRate = simulateInflationRate(market);

        CPIBond* selectedBond = selectBond(strategy);
        double bondPrice = priceBond(selectedBond);

        totalReturn += bondPrice;

        cout << "Simulation " << i + 1 << ": Inflation Rate = " << inflationRate
             << ", Selected Bond Price = " << bondPrice << endl;
    }

    double averageReturn = totalReturn / numSimulations;
    cout << "Average Return from " << numSimulations << " simulations: " << averageReturn << endl;
}

// === Main function ===
int main() {
    // Create two CPI bonds
    CPIBond bondA = {1000.0, 0.05, 10, 0.02};
    CPIBond bondB = {1000.0, 0.04, 10, 0.02};

    // Create market simulator
    MarketSimulator market;
    initMarketSimulator(&market, 0.02, 0.01);

    // Create bond switch strategy
    BondSwitchStrategy strategy = {&bondA, &bondB};

    // Run Monte Carlo simulation
    int numSimulations = 5; // You can change to 1000 for more accuracy
    runMonteCarloSimulation(numSimulations, &market, &strategy);

    return 0;
}
