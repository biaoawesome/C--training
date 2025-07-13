#include <iostream>
#include <string>
#include <map>
#include <cassert>
 
// �����ඨ��
class Currency {
public:
    // ���캯��
    Currency(const std::string& symbol, const std::string& name, double exchangeRate = 1.0)
        : symbol(symbol), name(name), exchangeRate(exchangeRate) {}
 
    // ��ȡ���ҷ���
    std::string getSymbol() const {
        return symbol;
    }
 
    // ��ȡ��������
    std::string getName() const {
        return name;
    }
 
    // ��ȡ����
    double getExchangeRate() const {
        return exchangeRate;
    }
 
    // ����֮���ת��
    double convertTo(const Currency& other, double amount) const {
        // ����ת���ǻ��ڵ�ǰ���ҵĻ�����Ŀ����ҵĻ���
        double convertedAmount = amount * (other.getExchangeRate() / exchangeRate);
        return convertedAmount;
    }
 
    // ���ұȽϣ��ȽϷ����Ƿ���ͬ
    bool operator==(const Currency& other) const {
        return symbol == other.symbol;
    }
 
    bool operator!=(const Currency& other) const {
        return symbol != other.symbol;
    }
 
    // ���������Ϣ
    void printInfo() const {
        std::cout << "Currency: " << name << " (" << symbol << "), Exchange Rate: " << exchangeRate << std::endl;
    }
 
private:
    std::string symbol;       // ���ҷ���
    std::string name;         // ��������
    double exchangeRate;      // ���ҵĻ��ʣ������Ĭ�ϻ�׼���ң�
};
 
// ����ת������
void testCurrencyConversion() {
    Currency usd("USD", "US Dollar", 1.0); // ��Ԫ
    Currency eur("EUR", "Euro", 0.85);     // ŷԪ������1��Ԫ=0.85ŷԪ
 
    double amountInUSD = 100.0;
    double amountInEUR = usd.convertTo(eur, amountInUSD);
    
    std::cout << amountInUSD << " USD is equivalent to " << amountInEUR << " EUR." << std::endl;
}
 
// ���ұȽϲ���
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
 
// ������Ϣ��ӡ����
void testCurrencyInfo() {
    Currency usd("USD", "US Dollar", 1.0);
    Currency eur("EUR", "Euro", 0.85);
 
    usd.printInfo();
    eur.printInfo();
}
 
int main() {
    // ���Ҳ���ʵ��
    testCurrencyConversion();  // ���Ի���ת��
    testCurrencyComparison();  // ���Ի��ұȽ�
    testCurrencyInfo();       // ���Ի�����Ϣ��ӡ
 
    return 0;
}
