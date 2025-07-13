#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstring>

// Configuration: Maximum number of assets supported
#define MAX_ASSETS 100   // Max number of assets in the index

// Asset structure
struct Asset {
    char name[32];     // Asset name (limited to 31 characters)
    double price;      // Current market price
    double quantity;   // Number of shares or weight
};

// Calculate Price-Weighted Index
double calculatePriceWeightedIndex(const Asset assets[], int count, double divisor = 1.0) {
    double totalPrice = 0.0;
    for (int i = 0; i < count; ++i) {
        totalPrice += assets[i].price;
    }
    return totalPrice / divisor;
}

// Calculate Market-Cap Weighted Index
double calculateMarketCapWeightedIndex(const Asset assets[], int count, double baseValue) {
    double totalMarketCap = 0.0;
    for (int i = 0; i < count; ++i) {
        totalMarketCap += assets[i].price * assets[i].quantity;
    }
    return totalMarketCap / baseValue;
}

// Calculate Equal-Weighted Index
double calculateEqualWeightedIndex(const Asset assets[], int count) {
    double totalPrice = 0.0;
    for (int i = 0; i < count; ++i) {
        totalPrice += assets[i].price;
    }
    return totalPrice / count;
}

// Main function
int main() {
    // Define asset data
    Asset assets[MAX_ASSETS] = {
        {"Asset A", 100.0, 50.0},   // Price 100, Quantity 50
        {"Asset B", 200.0, 30.0},   // Price 200, Quantity 30
        {"Asset C", 300.0, 20.0}    // Price 300, Quantity 20
    };

    int assetCount = 3;            // Actual number of assets
    double divisor = 1.0;          // Divisor for price-weighted index
    double baseValue = 1000.0;     // Base value for market-cap weighted index

    // Check if asset count exceeds array size
    if (assetCount > MAX_ASSETS) {
        std::cerr << "Error: Asset count exceeds maximum allowed." << std::endl;
        return 1;
    }

    // Compute index values
    double priceWeightedIndex = calculatePriceWeightedIndex(assets, assetCount, divisor);
    double marketCapWeightedIndex = calculateMarketCapWeightedIndex(assets, assetCount, baseValue);
    double equalWeightedIndex = calculateEqualWeightedIndex(assets, assetCount);

    // Output results
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Price-Weighted Index: " << priceWeightedIndex << std::endl;
    std::cout << "Market-Cap Weighted Index: " << marketCapWeightedIndex << std::endl;
    std::cout << "Equal-Weighted Index: " << equalWeightedIndex << std::endl;

    return 0;
}
