#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

struct Bill {
    std::string patient;
    explicit Bill(std::string p) : patient(std::move(p)) {}
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual std::string type() const = 0;
};
struct OutPatient : Bill {
    double consultation, tests;
    OutPatient(std::string p, double c, double t) : Bill(std::move(p)), consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
    std::string type() const override { return "OP"; }
};
struct InPatient : Bill {
    int days; double rate, procedures;
    InPatient(std::string p, int d, double r, double s) : Bill(std::move(p)), days(d), rate(r), procedures(s) {}
    double total() const override { return days * rate + procedures; }
    std::string type() const override { return "IP"; }
};
struct DayCare : Bill {
    double package;
    DayCare(std::string p, double x) : Bill(std::move(p)), package(x) {}
    double total() const override { return package; }
    std::string type() const override { return "DayCare"; }
};
struct Emergency : Bill {
    double base, perHour; int hours;
    Emergency(std::string p, double b, double rate, int h) : Bill(std::move(p)), base(b), perHour(rate), hours(h) {}
    double total() const override { return base + perHour * hours; }
    std::string type() const override { return "Emergency"; }
};
struct Payer {
    virtual ~Payer() = default;
    virtual std::string name() const = 0;
    virtual double amountCovered(const Bill&) const = 0;
};
struct SelfPay : Payer {
    std::string name() const override { return "SelfPay"; }
    double amountCovered(const Bill& b) const override { return b.total(); }
};
struct Insurance : Payer {
    double limit, copay;
    Insurance(double l, double c) : limit(l), copay(c) {}
    std::string name() const override { return "Insurance"; }
    double amountCovered(const Bill& b) const override { return std::min(limit, b.total() * (100.0 - copay) / 100.0); }
};
struct Government : Payer {
    std::string name() const override { return "Government"; }
    double amountCovered(const Bill& b) const override {
        const double rate = b.type() == "OP" ? 1500 : b.type() == "IP" ? 40000 : b.type() == "DayCare" ? 18000 : 8000;
        return std::min(rate, b.total());
    }
};

int main() {
    std::vector<std::unique_ptr<Bill>> bills;
    bills.emplace_back(std::make_unique<OutPatient>("Ravi", 500, 1200));
    bills.emplace_back(std::make_unique<InPatient>("Meena", 3, 2500, 40000));
    bills.emplace_back(std::make_unique<DayCare>("Isha", 22000));
    bills.emplace_back(std::make_unique<Emergency>("Arun", 5000, 1500, 4));
    SelfPay self; Insurance insurance(50000, 20); Government government;
    const Payer* payers[] = {&self, &insurance, &government};
    double allCovered = 0;
    for (const auto& bill : bills) {
        std::cout << bill->type() << ' ' << bill->patient << " total=" << bill->total();
        for (const Payer* payer : payers) {
            const double covered = payer->amountCovered(*bill);
            allCovered += covered;
            std::cout << ' ' << payer->name() << '=' << covered;
        }
        std::cout << '\n';
    }
    std::cout << "Verified cases=" << bills.size() * 3 << " aggregateCovered=" << allCovered << '\n';
}
