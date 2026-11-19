#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

struct Bill {
    explicit Bill(std::string id) : patient(std::move(id)) {}
    virtual ~Bill() noexcept = default;
    virtual double total() const noexcept = 0;
    virtual const char* type() const noexcept = 0;
    std::string patient;
};
struct OutPatient final : Bill {
    OutPatient(std::string p,double c,double t):Bill(std::move(p)),consult(c),tests(t){}
    double total() const noexcept override { return consult+tests; }
    const char* type() const noexcept override { return "OP"; }
    double consult,tests;
};
struct InPatient final : Bill {
    InPatient(std::string p,int d,double r,double s):Bill(std::move(p)),days(d),rate(r),surgery(s){}
    double total() const noexcept override { return days*rate+surgery; }
    const char* type() const noexcept override { return "IP"; }
    int days; double rate,surgery;
};
struct DayCare final : Bill {
    DayCare(std::string p,double package):Bill(std::move(p)),package(package){}
    double total() const noexcept override { return package; }
    const char* type() const noexcept override { return "DayCare"; }
    double package;
};
struct Emergency final : Bill {
    Emergency(std::string p,double base,double hourly,int hours):Bill(std::move(p)),base(base),hourly(hourly),hours(hours){}
    double total() const noexcept override { return base+hourly*hours; }
    const char* type() const noexcept override { return "Emergency"; }
    double base,hourly; int hours;
};
struct Payer { virtual ~Payer() noexcept=default; virtual double amountCovered(const Bill&) const=0; };
struct Insurance final : Payer {
    explicit Insurance(double cap):cap_(cap){}
    double amountCovered(const Bill& b) const override { return std::min(cap_,b.total()*0.8); }
    double cap_;
};

// Extension: new types are added as derived classes; existing classes above are unchanged.
struct TelemedicineBill final : Bill {
    TelemedicineBill(std::string p,double consult,double remoteTests):Bill(std::move(p)),consult(consult),remoteTests(remoteTests){}
    double total() const noexcept override { return consult+remoteTests; }
    const char* type() const noexcept override { return "Telemedicine"; }
    double consult,remoteTests;
};
struct CorporatePayer final : Payer {
    double amountCovered(const Bill& b) const override { return std::min(60000.0,b.total()*0.70); }
};
double settle(const Bill& b,const Payer& p) {
    const double covered=p.amountCovered(b);
    if (covered<0 || covered>b.total()) throw std::logic_error("invalid payer amount");
    return covered;
}
int main() {
    std::vector<std::unique_ptr<Bill>> bills;
    bills.emplace_back(std::make_unique<OutPatient>("Ravi",500,1200));
    bills.emplace_back(std::make_unique<InPatient>("Meena",3,2500,40000));
    bills.emplace_back(std::make_unique<DayCare>("Isha",22000));
    bills.emplace_back(std::make_unique<Emergency>("Arun",5000,1500,4));
    bills.emplace_back(std::make_unique<TelemedicineBill>("Asha",900,350));
    Insurance insurer(50000); CorporatePayer corporate;
    std::cout<<"extension "<<bills.back()->type()<<" total="<<bills.back()->total()
             <<" corporate="<<settle(*bills.back(),corporate)<<'\n';
    for (const auto& b:bills) std::cout<<b->type()<<' '<<b->patient<<" total="<<b->total()<<" insurance="<<settle(*b,insurer)<<'\n';
    try { throw std::runtime_error("simulated claim rejection"); }
    catch (const std::exception& e) { std::cout<<"caught "<<e.what()<<"; RAII cleanup complete\n"; }
}
