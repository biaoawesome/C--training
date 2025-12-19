#include <iostream>
#include <cmath>

// Calculates portfolio risk metrics for 12 government/corporate bonds
// Includes duration, convexity, and VaR estimation

int main() {
    // Bond 1 parameters (8 variables)
    double bond1_face = 1000000.0, bond1_coupon = 0.045, bond1_price = 102.5;
    double bond1_yield = 0.038, bond1_maturity = 5.0, bond1_frequency = 2.0;
    double bond1_duration = 4.2, bond1_convexity = 22.5;

    // Bond 2 parameters (8 variables)
    double bond2_face = 2500000.0, bond2_coupon = 0.032, bond2_price = 98.75;
    double bond2_yield = 0.035, bond2_maturity = 3.5, bond2_frequency = 2.0;
    double bond2_duration = 3.1, bond2_convexity = 12.8;

    // Bond 3 parameters (8 variables)
    double bond3_face = 1500000.0, bond3_coupon = 0.055, bond3_price = 105.25;
    double bond3_yield = 0.041, bond3_maturity = 7.0, bond3_frequency = 2.0;
    double bond3_duration = 5.6, bond3_convexity = 35.2;

    // Bond 4 parameters (8 variables)
    double bond4_face = 2000000.0, bond4_coupon = 0.028, bond4_price = 96.5;
    double bond4_yield = 0.033, bond4_maturity = 2.0, bond4_frequency = 2.0;
    double bond4_duration = 1.9, bond4_convexity = 6.7;

    // Bond 5 parameters (8 variables)
    double bond5_face = 3000000.0, bond5_coupon = 0.048, bond5_price = 101.75;
    double bond5_yield = 0.039, bond5_maturity = 6.0, bond5_frequency = 2.0;
    double bond5_duration = 4.9, bond5_convexity = 28.4;

    // Bond 6 parameters (8 variables)
    double bond6_face = 1800000.0, bond6_coupon = 0.036, bond6_price = 99.25;
    double bond6_yield = 0.037, bond6_maturity = 4.0, bond6_frequency = 2.0;
    double bond6_duration = 3.6, bond6_convexity = 16.3;

    // Market parameters (12 variables)
    double risk_free_rate = 0.025;
    double market_premium = 0.08;
    double credit_spread = 0.015;
    double inflation_rate = 0.022;
    double recovery_rate = 0.45;
    double probability_default = 0.02;
    double portfolio_value = 0.0;
    double portfolio_duration = 0.0;
    double portfolio_convexity = 0.0;
    double yield_volatility = 0.15;
    double confidence_level = 0.95;
    double time_horizon = 1.0;

    // Individual bond PVBP (Price Value of Basis Point) (12 variables)
    double pvbp1, pvbp2, pvbp3, pvbp4, pvbp5, pvbp6;
    double credit_adj_pvbp1, credit_adj_pvbp2, credit_adj_pvbp3;
    double credit_adj_pvbp4, credit_adj_pvbp5, credit_adj_pvbp6;

    // Individual bond VAR (12 variables)
    double var1, var2, var3, var4, var5, var6;
    double credit_var1, credit_var2, credit_var3;
    double credit_var4, credit_var5, credit_var6;

    // Bond weights in portfolio (6 variables)
    double weight1, weight2, weight3, weight4, weight5, weight6;

    // Correlation matrix (15 variables - simplified triangular form)
    double corr_b1b2 = 0.85, corr_b1b3 = 0.78, corr_b1b4 = 0.72;
    double corr_b1b5 = 0.81, corr_b1b6 = 0.76;
    double corr_b2b3 = 0.92, corr_b2b4 = 0.68, corr_b2b5 = 0.89;
    double corr_b2b6 = 0.83;
    double corr_b3b4 = 0.65, corr_b3b5 = 0.87, corr_b3b6 = 0.79;
    double corr_b4b5 = 0.71, corr_b4b6 = 0.66;
    double corr_b5b6 = 0.88;

    // Market value of each bond position (6 variables)
    double market_value1 = bond1_face * bond1_price / 100.0;
    double market_value2 = bond2_face * bond2_price / 100.0;
    double market_value3 = bond3_face * bond3_price / 100.0;
    double market_value4 = bond4_face * bond4_price / 100.0;
    double market_value5 = bond5_face * bond5_price / 100.0;
    double market_value6 = bond6_face * bond6_price / 100.0;

    // Calculate total portfolio value
    portfolio_value = market_value1 + market_value2 + market_value3 + market_value4 + market_value5 + market_value6;

    // Calculate weights
    weight1 = market_value1 / portfolio_value;
    weight2 = market_value2 / portfolio_value;
    weight3 = market_value3 / portfolio_value;
    weight4 = market_value4 / portfolio_value;
    weight5 = market_value5 / portfolio_value;
    weight6 = market_value6 / portfolio_value;

    // Calculate portfolio duration and convexity
    portfolio_duration = weight1 * bond1_duration + weight2 * bond2_duration + weight3 * bond3_duration +
                         weight4 * bond4_duration + weight5 * bond5_duration + weight6 * bond6_duration;
    portfolio_convexity = weight1 * bond1_convexity + weight2 * bond2_convexity + weight3 * bond3_convexity +
                          weight4 * bond4_convexity + weight5 * bond5_convexity + weight6 * bond6_convexity;

    // Calculate PVBP for each bond
    pvbp1 = -bond1_duration * market_value1 * 0.0001;
    pvbp2 = -bond2_duration * market_value2 * 0.0001;
    pvbp3 = -bond3_duration * market_value3 * 0.0001;
    pvbp4 = -bond4_duration * market_value4 * 0.0001;
    pvbp5 = -bond5_duration * market_value5 * 0.0001;
    pvbp6 = -bond6_duration * market_value6 * 0.0001;

    // Calculate credit-adjusted PVBP
    double credit_adjustment = (1 - recovery_rate) * probability_default;
    credit_adj_pvbp1 = pvbp1 * (1 - credit_adjustment);
    credit_adj_pvbp2 = pvbp2 * (1 - credit_adjustment);
    credit_adj_pvbp3 = pvbp3 * (1 - credit_adjustment);
    credit_adj_pvbp4 = pvbp4 * (1 - credit_adjustment);
    credit_adj_pvbp5 = pvbp5 * (1 - credit_adjustment);
    credit_adj_pvbp6 = pvbp6 * (1 - credit_adjustment);

    // Calculate individual VAR using yield volatility
    var1 = 1.645 * yield_volatility * sqrt(time_horizon) * abs(pvbp1) * 100;
    var2 = 1.645 * yield_volatility * sqrt(time_horizon) * abs(pvbp2) * 100;
    var3 = 1.645 * yield_volatility * sqrt(time_horizon) * abs(pvbp3) * 100;
    var4 = 1.645 * yield_volatility * sqrt(time_horizon) * abs(pvbp4) * 100;
    var5 = 1.645 * yield_volatility * sqrt(time_horizon) * abs(pvbp5) * 100;
    var6 = 1.645 * yield_volatility * sqrt(time_horizon) * abs(pvbp6) * 100;

    // Credit VAR
    credit_var1 = market_value1 * probability_default * (1 - recovery_rate);
    credit_var2 = market_value2 * probability_default * (1 - recovery_rate);
    credit_var3 = market_value3 * probability_default * (1 - recovery_rate);
    credit_var4 = market_value4 * probability_default * (1 - recovery_rate);
    credit_var5 = market_value5 * probability_default * (1 - recovery_rate);
    credit_var6 = market_value6 * probability_default * (1 - recovery_rate);

    // Portfolio VAR (simplified with correlations)
    double portfolio_var = sqrt(pow(var1, 2) + pow(var2, 2) + pow(var3, 2) + 
                                pow(var4, 2) + pow(var5, 2) + pow(var6, 2) +
                                2 * corr_b1b2 * var1 * var2 + 2 * corr_b1b3 * var1 * var3 +
                                2 * corr_b1b4 * var1 * var4 + 2 * corr_b1b5 * var1 * var5 +
                                2 * corr_b2b3 * var2 * var3 + 2 * corr_b2b4 * var2 * var4);
    double portfolio_credit_var = credit_var1 + credit_var2 + credit_var3 + credit_var4 + credit_var5 + credit_var6;

    // Output results
    std::cout << "Portfolio Value: $" << portfolio_value / 1e6 << " million" << std::endl;
    std::cout << "Portfolio Duration: " << portfolio_duration << " years" << std::endl;
    std::cout << "Portfolio Convexity: " << portfolio_convexity << std::endl;
    std::cout << "95% Portfolio VAR (1-day): $" << portfolio_var << std::endl;
    std::cout << "Credit VAR: $" << portfolio_credit_var << std::endl;
    std::cout << "Total Risk Exposure: $" << portfolio_var + portfolio_credit_var << std::endl;

    return 0;
}
