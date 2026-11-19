#include <iostream>
#include <new>
#include <stdexcept>
#include <string>

struct BillingError : std::runtime_error { using std::runtime_error::runtime_error; };
struct ClaimError : BillingError { using BillingError::BillingError; };
struct UnknownPackage : BillingError { using BillingError::BillingError; };
struct MissingPatient : BillingError { using BillingError::BillingError; };

void requirePatient(bool recordExists) {
    if (!recordExists) throw MissingPatient("patient record not found");
}

double approve(double billed, double cover) {
    if (billed < 0 || cover < 0) throw std::invalid_argument("negative amount");
    if (billed > cover) throw ClaimError("exceeds cover");
    return billed;
}

void cleanup() noexcept { std::cout << "cleanup safe\n"; }

int main() {
    try { (void)approve(1200, 1000); }
    catch (const ClaimError& e) { std::cout << "claim: " << e.what() << '\n'; }
    try { throw UnknownPackage("package X9 not found"); }
    catch (const BillingError& e) { std::cout << "billing: " << e.what() << '\n'; }
    try { requirePatient(false); }
    catch (const MissingPatient& e) { std::cout << "patient: " << e.what() << '\n'; }
    cleanup();
}
