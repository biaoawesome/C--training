#include <iostream>
#include <vector>
#include <cmath>
 
// 利率曲线类
class OISDiscountCurve {
public:
    // 构造函数，接受OIS利率数据（每年到期的OIS利率）
    OISDiscountCurve(const std::vector<double>& oisRates, const std::vector<double>& maturities)
        : oisRates_(oisRates), maturities_(maturities) {}
 
    // 计算某一给定期限的折扣因子
    double discountFactor(double maturity) {
        double discount = 1.0;
        for (size_t i = 0; i < maturities_.size(); ++i) {
            if (maturities_[i] > maturity) {
                double deltaT = maturities_[i] - maturities_[i - 1];
                double rate = oisRates_[i];
                discount *= exp(-rate * deltaT);
            }
        }
        return discount;
    }
 
private:
    std::vector<double> oisRates_;  // OIS利率列表
    std::vector<double> maturities_;  // 对应的到期时间（年）
};
 
// 互换定价类
class InterestRateSwap {
public:
    // 构造函数，接受固定支付利率、浮动支付利率以及相关参数
    InterestRateSwap(double notional, double fixedRate, const std::vector<double>& floatingRates, const OISDiscountCurve& discountCurve)
        : notional_(notional), fixedRate_(fixedRate), floatingRates_(floatingRates), discountCurve_(discountCurve) {}
 
    // 定价5年期利率互换
    double priceSwap() {
        double fixedLegPV = 0.0;
        double floatingLegPV = 0.0;
        double notional = notional_;
 
        // 计算固定支付现金流的现值
        for (size_t i = 0; i < floatingRates_.size(); ++i) {
            double maturity = i + 1;  // 假设每年支付一次
            double discountFactor = discountCurve_.discountFactor(maturity);
            fixedLegPV += fixedRate_ * notional * discountFactor;
            floatingLegPV += floatingRates_[i] * notional * discountFactor;
        }
 
        return fixedLegPV - floatingLegPV;
    }
 
private:
    double notional_;  // 名义本金
    double fixedRate_;  // 固定利率
    std::vector<double> floatingRates_;  // 浮动利率
    OISDiscountCurve discountCurve_;  // OIS折扣曲线
};
 
// 测试实例
void testSwapPricing() {
    // 假设市场数据：OIS利率和对应到期时间
    std::vector<double> oisRates = {0.01, 0.015, 0.02, 0.025, 0.03};  // OIS利率
    std::vector<double> maturities = {1.0, 2.0, 3.0, 4.0, 5.0};  // 到期时间
 
    // 创建OIS折扣曲线
    OISDiscountCurve discountCurve(oisRates, maturities);
 
    // 假设的市场数据：固定利率和浮动利率（例如：基于OIS曲线）
    double fixedRate = 0.025;  // 固定利率为2.5%
    std::vector<double> floatingRates = {0.015, 0.02, 0.025, 0.03, 0.035};  // 浮动利率逐年增加
 
    // 创建InterestRateSwap对象
    InterestRateSwap swap(1000000, fixedRate, floatingRates, discountCurve);
 
    // 计算互换价格
    double swapPrice = swap.priceSwap();
 
    // 输出互换定价结果
    std::cout << "Swap Price (Fixed - Floating): " << swapPrice << std::endl;
}
 
int main() {
    // 执行5年期互换定价测试
    testSwapPricing();
    return 0;
}
