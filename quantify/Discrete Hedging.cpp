#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>

using namespace std;

// Asset class representing a spot financial asset
class Asset {
private:
    double price;  // Current price of the asset

public:
    Asset(double initialPrice) : price(initialPrice) {}

    // Get current asset price
    double getPrice() const {
        return price;
    }

    // Update price using a random walk model with volatility
    void updatePrice(double volatility, double deltaT) {
        random_device rd;
        mt19937 gen(rd());
        normal_distribution<> d(0, 1);  // Standard normal distribution

        // Simulate random shock based on volatility and time step
        double randomShock = d(gen) * volatility * sqrt(deltaT);
        price *= exp(randomShock);  // Log-normal price change
    }
};

// Hedge instrument class (e.g., futures contract)
class HedgeInstrument {
private:
    double price;      // Price of the hedge instrument
    double position;   // Position held in this instrument

public:
    HedgeInstrument(double initialPrice) : price(initialPrice), position(0) {}

    // Get current price
    double getPrice() const {
        return price;
    }

    // Update price based on the spot asset price
    void updatePrice(double assetPrice) {
        price = assetPrice;  // Assume perfect correlation
    }

    // Adjust hedge position
    void adjustPosition(double targetPosition) {
        position = targetPosition;
    }

    // Calculate profit and loss
    double calculatePL(double oldPosition) {
        return position * (price - oldPosition);
    }
};

// Hedging strategy class
class HedgingStrategy {
private:
    Asset& asset;
    HedgeInstrument& hedgeInstrument;
    double hedgeRatio;

public:
    HedgingStrategy(Asset& asset, HedgeInstrument& hedgeInstrument, double hedgeRatio)
        : asset(asset), hedgeInstrument(hedgeInstrument), hedgeRatio(hedgeRatio) {}

    // Adjust hedge position based on current asset price
    void adjustHedgePosition(double timeStep) {
        double assetPrice = asset.getPrice();
        double targetPosition = hedgeRatio * assetPrice;
        hedgeInstrument.adjustPosition(targetPosition);
        hedgeInstrument.updatePrice(assetPrice);
    }

    // Calculate total profit and loss
    double calculateTotalPL(double prevHedgePosition) {
        double assetPrice = asset.getPrice();
        double assetPL = 0.0;  // Simplified: assume no direct P&L tracking here
        double hedgePL = hedgeInstrument.calculatePL(prevHedgePosition);
        return assetPL + hedgePL;
    }
};

int main() {
    // Initial setup
    double initialAssetPrice = 100.0;
    double volatility = 0.02;       // Annualized volatility of 2%
    double hedgeRatio = 1.0;        // Full hedge ratio
    double deltaT = 1.0 / 252.0;    // Daily time step (assuming 252 trading days per year)

    Asset asset(initialAssetPrice);
    HedgeInstrument hedgeInstrument(initialAssetPrice);

    HedgingStrategy hedgingStrategy(asset, hedgeInstrument, hedgeRatio);

    const int numSteps = 252;       // Simulate one full year
    double totalPL = 0.0;
    double prevHedgePosition = 0.0;

    // Run simulation
    for (int i = 0; i < numSteps; ++i) {
        asset.updatePrice(volatility, deltaT);
        hedgingStrategy.adjustHedgePosition(deltaT);

        double currentPL = hedgingStrategy.calculateTotalPL(prevHedgePosition);
        totalPL += currentPL;

        prevHedgePosition = hedgeInstrument.getPrice();
    }

    // Output final result
    cout << "Total Profit and Loss from Hedging: $" << fixed << setprecision(2) << totalPL << endl;

    return 0;
}
