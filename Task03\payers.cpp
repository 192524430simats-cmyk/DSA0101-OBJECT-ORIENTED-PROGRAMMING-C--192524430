#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

struct Bill {
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual std::string type() const = 0;
};
struct OPBill final : Bill {
    double total() const override { return 1700; }
    std::string type() const override { return "OP"; }
};
struct Payer {
    virtual ~Payer() = default;
    virtual double amountCovered(const Bill&) const = 0;
};
struct SelfPay final : Payer {
    double amountCovered(const Bill& b) const override { return b.total(); }
};
struct Insurance final : Payer {
    Insurance(double limit, double copayPercent) : limit_(limit), copay_(copayPercent) {}
    double amountCovered(const Bill& b) const override {
        return std::min(limit_, b.total() * (100.0 - copay_) / 100.0);
    }
private:
    double limit_;
    double copay_;
};
struct GovernmentScheme final : Payer {
    double amountCovered(const Bill& b) const override {
        return b.type() == "OP" ? 1500.0 : 0.0;
    }
};
struct CorporatePayer final : Payer {
    double amountCovered(const Bill& b) const override { return std::min(60000.0, b.total() * 0.70); }
};

int main() {
    OPBill bill;
    SelfPay self;
    Insurance insurance(50000, 20);
    GovernmentScheme scheme;
    CorporatePayer corporate;
    const Payer* payers[] = {&self, &insurance, &scheme, &corporate};
    const char* names[] = {"SelfPay", "Insurance", "Government", "Corporate"};
    for (int i = 0; i < 4; ++i)
        std::cout << names[i] << " covers " << payers[i]->amountCovered(bill) << " of " << bill.total() << '\n';
}
