#include <iostream>

struct Bill {
    virtual double total() const = 0;
    ~Bill() = default; // Intentionally wrong: deletion through Bill* is undefined behavior.
};
struct OPBill final : Bill {
    char* resource = new char[64];
    double total() const override { return 500; }
    ~OPBill() { std::cout << "~OPBill releases resource\n"; delete[] resource; }
};
int main() { Bill* b = new OPBill; delete b; }
