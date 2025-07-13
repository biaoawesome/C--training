#include <iostream>
#include <vector>
#include <cmath>
 
// ����������
class OISDiscountCurve {
public:
    // ���캯��������OIS�������ݣ�ÿ�굽�ڵ�OIS���ʣ�
    OISDiscountCurve(const std::vector<double>& oisRates, const std::vector<double>& maturities)
        : oisRates_(oisRates), maturities_(maturities) {}
 
    // ����ĳһ�������޵��ۿ�����
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
    std::vector<double> oisRates_;  // OIS�����б�
    std::vector<double> maturities_;  // ��Ӧ�ĵ���ʱ�䣨�꣩
};
 
// ����������
class InterestRateSwap {
public:
    // ���캯�������̶ܹ�֧�����ʡ�����֧�������Լ���ز���
    InterestRateSwap(double notional, double fixedRate, const std::vector<double>& floatingRates, const OISDiscountCurve& discountCurve)
        : notional_(notional), fixedRate_(fixedRate), floatingRates_(floatingRates), discountCurve_(discountCurve) {}
 
    // ����5�������ʻ���
    double priceSwap() {
        double fixedLegPV = 0.0;
        double floatingLegPV = 0.0;
        double notional = notional_;
 
        // ����̶�֧���ֽ�������ֵ
        for (size_t i = 0; i < floatingRates_.size(); ++i) {
            double maturity = i + 1;  // ����ÿ��֧��һ��
            double discountFactor = discountCurve_.discountFactor(maturity);
            fixedLegPV += fixedRate_ * notional * discountFactor;
            floatingLegPV += floatingRates_[i] * notional * discountFactor;
        }
 
        return fixedLegPV - floatingLegPV;
    }
 
private:
    double notional_;  // ���屾��
    double fixedRate_;  // �̶�����
    std::vector<double> floatingRates_;  // ��������
    OISDiscountCurve discountCurve_;  // OIS�ۿ�����
};
 
// ����ʵ��
void testSwapPricing() {
    // �����г����ݣ�OIS���ʺͶ�Ӧ����ʱ��
    std::vector<double> oisRates = {0.01, 0.015, 0.02, 0.025, 0.03};  // OIS����
    std::vector<double> maturities = {1.0, 2.0, 3.0, 4.0, 5.0};  // ����ʱ��
 
    // ����OIS�ۿ�����
    OISDiscountCurve discountCurve(oisRates, maturities);
 
    // ������г����ݣ��̶����ʺ͸������ʣ����磺����OIS���ߣ�
    double fixedRate = 0.025;  // �̶�����Ϊ2.5%
    std::vector<double> floatingRates = {0.015, 0.02, 0.025, 0.03, 0.035};  // ����������������
 
    // ����InterestRateSwap����
    InterestRateSwap swap(1000000, fixedRate, floatingRates, discountCurve);
 
    // ���㻥���۸�
    double swapPrice = swap.priceSwap();
 
    // ����������۽��
    std::cout << "Swap Price (Fixed - Floating): " << swapPrice << std::endl;
}
 
int main() {
    // ִ��5���ڻ������۲���
    testSwapPricing();
    return 0;
}
