#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <variant>
#include <vector>

struct Bill { virtual ~Bill() = default; virtual double total() const = 0; };
struct OP final : Bill { double total() const override { return 1700.0; } };
struct IP final : Bill { double total() const override { return 47500.0; } };
struct Record { int kind; double op, ip; };
struct OpValue { double value; };
struct IpValue { double value; };
using BillVariant = std::variant<OpValue, IpValue>;
volatile double sink = 0;
using Clock = std::chrono::steady_clock;

template<class F> double measureMs(F&& fn) {
    const auto start = Clock::now();
    const double sum = fn();
    const auto stop = Clock::now();
    sink = sum;
    return std::chrono::duration<double, std::milli>(stop - start).count();
}
double sumVirtual(const std::vector<const Bill*>& bills) {
    double sum=0; for (const Bill* b:bills) sum+=b->total(); return sum;
}
double sumSwitch(const std::vector<Record>& bills) {
    double sum=0; for (const auto& b:bills) sum += b.kind==0 ? b.op : b.ip; return sum;
}
double sumVariant(const std::vector<BillVariant>& bills) {
    double sum=0; for (const auto& b:bills) sum += std::visit([](const auto& x){return x.value;},b); return sum;
}
bool validReturn(double amount) { return amount>=0 && amount<=50000; }
bool validThrow(double amount) {
    if (amount<0) throw std::invalid_argument("negative");
    if (amount>50000) throw std::out_of_range("over cover");
    return true;
}
double testReturns(std::size_t n,std::size_t bad) {
    std::size_t accepted=0;
    for (std::size_t i=0;i<n;++i) accepted += validReturn(i<bad ? -1.0 : 40000.0);
    return static_cast<double>(accepted);
}
double testExceptions(std::size_t n,std::size_t bad) {
    std::size_t accepted=0;
    for (std::size_t i=0;i<n;++i) {
        try { accepted += validThrow(i<bad ? -1.0 : 40000.0); }
        catch (const std::exception&) {}
    }
    return static_cast<double>(accepted);
}
int main() {
    static const OP op; static const IP ip;
    std::cout<<std::fixed<<std::setprecision(3);
    for (std::size_t n : {10u,1000u,1000000u,10000000u}) {
        std::vector<const Bill*> virtualBills; virtualBills.reserve(n);
        for(std::size_t i=0;i<n;++i) virtualBills.push_back(i%2 ? static_cast<const Bill*>(&op) : static_cast<const Bill*>(&ip));
        const double virtualMs=measureMs([&]{return sumVirtual(virtualBills);});
        const double virtualSum=sink;
        std::vector<Record> switchBills; switchBills.reserve(n);
        for(std::size_t i=0;i<n;++i) switchBills.push_back({static_cast<int>(i%2),1700.0,47500.0});
        const double switchMs=measureMs([&]{return sumSwitch(switchBills);});
        const double switchSum=sink;
        std::vector<BillVariant> variantBills; variantBills.reserve(n);
        for(std::size_t i=0;i<n;++i) variantBills.emplace_back(i%2 ? BillVariant{OpValue{1700.0}} : BillVariant{IpValue{47500.0}});
        const double variantMs=measureMs([&]{return sumVariant(variantBills);});
        const double variantSum=sink;
        const double expected=static_cast<double>((n+1)/2)*47500.0+static_cast<double>(n/2)*1700.0;
        std::cout<<"dispatch n="<<n<<" virtual_ms="<<virtualMs<<" switch_ms="<<switchMs<<" variant_ms="<<variantMs
                 <<" equal="<<((virtualSum==expected && switchSum==expected && variantSum==expected)?"yes":"NO")
                 <<" expected_sum="<<expected<<" setup_excluded=yes\n";
    }
    constexpr std::size_t n=1000000;
    for (double rate : {0.0,0.01,0.50}) {
        const auto bad=static_cast<std::size_t>(n*rate);
        const double r=measureMs([&]{return testReturns(n,bad);});
        const double e=measureMs([&]{return testExceptions(n,bad);});
        std::cout<<"claims invalid="<<std::fixed<<std::setprecision(0)<<rate*100<<"% return_ms="
                 <<std::setprecision(3)<<r<<" exception_ms="<<e<<" accepted="<<(n-bad)<<'\n';
    }
}

