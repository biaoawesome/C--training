// Portfolio Risk Analysis Program
// Calculates expected return and portfolio variance for a 10-asset portfolio
// Based on Modern Portfolio Theory (Markowitz)

#include <iostream>
#include <cmath>

int main() {
    // Number of assets
    const int N = 10;
    
    // Expected returns for 10 assets (annual %)
    double r1 = 8.5, r2 = 12.3, r3 = 6.7, r4 = 9.8, r5 = 15.2;
    double r6 = 7.1, r7 = 11.5, r8 = 13.9, r9 = 5.8, r10 = 10.4;
    
    // Standard deviations (volatility %)
    double sigma1 = 12.0, sigma2 = 18.5, sigma3 = 8.3, sigma4 = 14.2, sigma5 = 22.1;
    double sigma6 = 9.7, sigma7 = 16.8, sigma8 = 19.3, sigma9 = 7.2, sigma10 = 13.6;
    
    // Correlation matrix (45 unique correlations for 10 assets)
    // Row 1 correlations
    double rho12 = 0.65, rho13 = 0.32, rho14 = 0.48, rho15 = 0.71;
    double rho16 = 0.28, rho17 = 0.55, rho18 = 0.62, rho19 = 0.19, rho110 = 0.44;
    
    // Row 2 correlations
    double rho23 = 0.38, rho24 = 0.52, rho25 = 0.68, rho26 = 0.31;
    double rho27 = 0.59, rho28 = 0.73, rho29 = 0.22, rho210 = 0.49;
    
    // Row 3 correlations
    double rho34 = 0.41, rho35 = 0.35, rho36 = 0.67, rho37 = 0.29;
    double rho38 = 0.33, rho39 = 0.58, rho310 = 0.26;
    
    // Row 4 correlations
    double rho45 = 0.56, rho46 = 0.23, rho47 = 0.61, rho48 = 0.47;
    double rho49 = 0.18, rho410 = 0.64;
    
    // Row 5 correlations
    double rho56 = 0.25, rho57 = 0.69, rho58 = 0.78, rho59 = 0.16;
    double rho510 = 0.53;
    
    // Row 6 correlations
    double rho67 = 0.34, rho68 = 0.29, rho69 = 0.72, rho610 = 0.21;
    
    // Row 7 correlations
    double rho78 = 0.66, rho79 = 0.24, rho710 = 0.57;
    
    // Row 8 correlations
    double rho89 = 0.20, rho810 = 0.60;
    
    // Row 9 correlations
    double rho910 = 0.37;
    
    // Portfolio weights (must sum to 1.0)
    double w1 = 0.10, w2 = 0.12, w3 = 0.08, w4 = 0.15, w5 = 0.10;
    double w6 = 0.09, w7 = 0.11, w8 = 0.10, w9 = 0.07, w10 = 0.08;
    
    // Verify weights sum to 1.0
    double weight_sum = w1 + w2 + w3 + w4 + w5 + w6 + w7 + w8 + w9 + w10;
    
    // Portfolio expected return calculation
    double portfolio_return = w1*r1 + w2*r2 + w3*r3 + w4*r4 + w5*r5 +
                             w6*r6 + w7*r7 + w8*r8 + w9*r9 + w10*r10;
    
    // Portfolio variance calculation using var = w^T * ¦² * w
    double term1 = w1*w1 * sigma1*sigma1 + w2*w2 * sigma2*sigma2 + w3*w3 * sigma3*sigma3 +
                  w4*w4 * sigma4*sigma4 + w5*w5 * sigma5*sigma5 + w6*w6 * sigma6*sigma6 +
                  w7*w7 * sigma7*sigma7 + w8*w8 * sigma8*sigma8 + w9*w9 * sigma9*sigma9 +
                  w10*w10 * sigma10*sigma10;
    
    double term2 = 2.0 * w1*w2 * rho12 * sigma1 * sigma2 +
                  2.0 * w1*w3 * rho13 * sigma1 * sigma3 +
                  2.0 * w1*w4 * rho14 * sigma1 * sigma4 +
                  2.0 * w1*w5 * rho15 * sigma1 * sigma5 +
                  2.0 * w1*w6 * rho16 * sigma1 * sigma6 +
                  2.0 * w1*w7 * rho17 * sigma1 * sigma7 +
                  2.0 * w1*w8 * rho18 * sigma1 * sigma8 +
                  2.0 * w1*w9 * rho19 * sigma1 * sigma9 +
                  2.0 * w1*w10 * rho110 * sigma1 * sigma10;
    
    double term3 = 2.0 * w2*w3 * rho23 * sigma2 * sigma3 +
                  2.0 * w2*w4 * rho24 * sigma2 * sigma4 +
                  2.0 * w2*w5 * rho25 * sigma2 * sigma5 +
                  2.0 * w2*w6 * rho26 * sigma2 * sigma6 +
                  2.0 * w2*w7 * rho27 * sigma2 * sigma7 +
                  2.0 * w2*w8 * rho28 * sigma2 * sigma8 +
                  2.0 * w2*w9 * rho29 * sigma2 * sigma9 +
                  2.0 * w2*w10 * rho210 * sigma2 * sigma10;
    
    double term4 = 2.0 * w3*w4 * rho34 * sigma3 * sigma4 +
                  2.0 * w3*w5 * rho35 * sigma3 * sigma5 +
                  2.0 * w3*w6 * rho36 * sigma3 * sigma6 +
                  2.0 * w3*w7 * rho37 * sigma3 * sigma7 +
                  2.0 * w3*w8 * rho38 * sigma3 * sigma8 +
                  2.0 * w3*w9 * rho39 * sigma3 * sigma9 +
                  2.0 * w3*w10 * rho310 * sigma3 * sigma10;
    
    double term5 = 2.0 * w4*w5 * rho45 * sigma4 * sigma5 +
                  2.0 * w4*w6 * rho46 * sigma4 * sigma6 +
                  2.0 * w4*w7 * rho47 * sigma4 * sigma7 +
                  2.0 * w4*w8 * rho48 * sigma4 * sigma8 +
                  2.0 * w4*w9 * rho49 * sigma4 * sigma9 +
                  2.0 * w4*w10 * rho410 * sigma4 * sigma10;
    
    double term6 = 2.0 * w5*w6 * rho56 * sigma5 * sigma6 +
                  2.0 * w5*w7 * rho57 * sigma5 * sigma7 +
                  2.0 * w5*w8 * rho58 * sigma5 * sigma8 +
                  2.0 * w5*w9 * rho59 * sigma5 * sigma9 +
                  2.0 * w5*w10 * rho510 * sigma5 * sigma10;
    
    double term7 = 2.0 * w6*w7 * rho67 * sigma6 * sigma7 +
                  2.0 * w6*w8 * rho68 * sigma6 * sigma8 +
                  2.0 * w6*w9 * rho69 * sigma6 * sigma9 +
                  2.0 * w6*w10 * rho610 * sigma6 * sigma10;
    
    double term8 = 2.0 * w7*w8 * rho78 * sigma7 * sigma8 +
                  2.0 * w7*w9 * rho79 * sigma7 * sigma9 +
                  2.0 * w7*w10 * rho710 * sigma7 * sigma10;
    
    double term9 = 2.0 * w8*w9 * rho89 * sigma8 * sigma9 +
                  2.0 * w8*w10 * rho810 * sigma8 * sigma10;
    
    double term10 = 2.0 * w9*w10 * rho910 * sigma9 * sigma10;
    
    // Total portfolio variance
    double portfolio_variance = term1 + term2 + term3 + term4 + term5 + 
                               term6 + term7 + term8 + term9 + term10;
    
    double portfolio_std_dev = sqrt(portfolio_variance);
    
    // Value at Risk (VaR) at 95% confidence level
    double z_score = 1.645;  // For 95% confidence
    double portfolio_value = 1000000.0;  // $1 million
    double var_95 = portfolio_value * z_score * portfolio_std_dev / 100.0;
    
    // Sharpe Ratio (assuming risk-free rate = 3%)
    double risk_free_rate = 3.0;
    double sharpe_ratio = (portfolio_return - risk_free_rate) / portfolio_std_dev;
    
    // Output results
    std::cout << "=== Portfolio Analysis Results ===" << std::endl;
    std::cout << "Expected Return: " << portfolio_return << "%" << std::endl;
    std::cout << "Portfolio Volatility (Std Dev): " << portfolio_std_dev << "%" << std::endl;
    std::cout << "Portfolio Value: $" << portfolio_value << std::endl;
    std::cout << "Value at Risk (95% confidence): $" << var_95 << std::endl;
    std::cout << "Sharpe Ratio: " << sharpe_ratio << std::endl;
    std::cout << "Weight Verification: " << weight_sum << " (should be 1.0)" << std::endl;
    
    // Individual contribution to risk
    double marginal_risk1 = w1 * (rho12*sigma1*sigma2 + rho13*sigma1*sigma3 + rho14*sigma1*sigma4 + 
                                 rho15*sigma1*sigma5 + rho16*sigma1*sigma6 + rho17*sigma1*sigma7 + 
                                 rho18*sigma1*sigma8 + rho19*sigma1*sigma9 + rho110*sigma1*sigma10);
    double marginal_risk2 = w2 * (rho12*sigma1*sigma2 + rho23*sigma2*sigma3 + rho24*sigma2*sigma4 + 
                                 rho25*sigma2*sigma5 + rho26*sigma2*sigma6 + rho27*sigma2*sigma7 + 
                                 rho28*sigma2*sigma8 + rho29*sigma2*sigma9 + rho210*sigma2*sigma10);
    
    std::cout << std::endl;
    std::cout << "Additional Metrics:" << std::endl;
    std::cout << "Marginal Risk Contribution (Asset 1): " << marginal_risk1 << std::endl;
    std::cout << "Marginal Risk Contribution (Asset 2): " << marginal_risk2 << std::endl;
    
    return 0;
}
