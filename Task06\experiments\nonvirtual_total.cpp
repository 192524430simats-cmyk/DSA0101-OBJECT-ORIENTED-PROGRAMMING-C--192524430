#include <iostream>
struct Bill { virtual ~Bill() = default; double total() const = 0; };
struct OPBill : Bill { double total() const { return 500; } };
int main() { Bill* b = new OPBill; std::cout << b->total() << '\n'; delete b; }
