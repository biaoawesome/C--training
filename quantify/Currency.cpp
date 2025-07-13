#include <iostream>
#include <string>
#include <map>
#include <cassert>
 
// 货币类定义
class Currency {
public:
    // 构造函数
    Currency(const std::string& symbol, const std::string& name, double exchangeRate = 1.0)
        : symbol(symbol), name(name), exchangeRate(exchangeRate) {}
 
    // 获取货币符号
    std::string getSymbol() const {
        return symbol;
    }
 
    // 获取货币名称
    std::string getName() const {
        return name;
    }
 
    // 获取汇率
    double getExchangeRate() const {
        return exchangeRate;
    }
 
    // 货币之间的转换
    double convertTo(const Currency& other, double amount) const {
        // 假设转换是基于当前货币的汇率与目标货币的汇率
        double convertedAmount = amount * (other.getExchangeRate() / exchangeRate);
        return convertedAmount;
    }
 
    // 货币比较，比较符号是否相同
    bool operator==(const Currency& other) const {
        return symbol == other.symbol;
    }
 
    bool operator!=(const Currency& other) const {
        return symbol != other.symbol;
    }
 
    // 输出货币信息
    void printInfo() const {
        std::cout << "Currency: " << name << " (" << symbol << "), Exchange Rate: " << exchangeRate << std::endl;
    }
 
private:
    std::string symbol;       // 货币符号
    std::string name;         // 货币名称
    double exchangeRate;      // 货币的汇率（相对于默认基准货币）
};
 
// 货币转换函数
void testCurrencyConversion() {
    Currency usd("USD", "US Dollar", 1.0); // 美元
    Currency eur("EUR", "Euro", 0.85);     // 欧元，假设1美元=0.85欧元
 
    double amountInUSD = 100.0;
    double amountInEUR = usd.convertTo(eur, amountInUSD);
    
    std::cout << amountInUSD << " USD is equivalent to " << amountInEUR << " EUR." << std::endl;
}
 
// 货币比较测试
void testCurrencyComparison() {
    Currency usd1("USD", "US Dollar", 1.0);
    Currency usd2("USD", "US Dollar", 1.0);
    Currency eur("EUR", "Euro", 0.85);
 
    if (usd1 == usd2) {
        std::cout << "usd1 and usd2 are the same currency." << std::endl;
    } else {
        std::cout << "usd1 and usd2 are different currencies." << std::endl;
    }
 
    if (usd1 != eur) {
        std::cout << "USD and EUR are different currencies." << std::endl;
    }
}
 
// 货币信息打印测试
void testCurrencyInfo() {
    Currency usd("USD", "US Dollar", 1.0);
    Currency eur("EUR", "Euro", 0.85);
 
    usd.printInfo();
    eur.printInfo();
}
 
int main() {
    // 货币测试实例
    testCurrencyConversion();  // 测试货币转换
    testCurrencyComparison();  // 测试货币比较
    testCurrencyInfo();       // 测试货币信息打印
 
    return 0;
}
