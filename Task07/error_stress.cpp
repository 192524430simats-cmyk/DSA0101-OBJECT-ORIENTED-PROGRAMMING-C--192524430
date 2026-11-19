#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>

double parseAmount(const std::string& token) { return std::stod(token); }
double packageRate(const std::string& code) {
    if (code == "OP") return 1500;
    if (code == "IP") return 40000;
    throw std::runtime_error("unknown package");
}
struct ResourceGuard {
    ~ResourceGuard() noexcept { std::cout << "RAII object destroyed during exit/unwind\n"; }
};

int main() {
    try { (void)parseAmount("not-a-number"); }
    catch (const std::invalid_argument& e) { std::cout << "text input: " << e.what() << '\n'; }
    try { (void)packageRate("X9"); }
    catch (const std::exception& e) { std::cout << "package: " << e.what() << '\n'; }
    try { (void)::operator new(std::numeric_limits<std::size_t>::max()); }
    catch (const std::bad_alloc&) { std::cout << "allocation: std::bad_alloc caught\n"; }
    try {
        ResourceGuard guard;
        throw 7;
    } catch (...) { std::cout << "top-level catch(...): continued safely\n"; }
}
