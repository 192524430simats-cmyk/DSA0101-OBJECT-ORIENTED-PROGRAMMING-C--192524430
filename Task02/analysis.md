# A2 - Runtime binding, vtables, and virtual destruction

`show()` is non-virtual, so the call to `show` is selected at compile time from `Bill`. Inside it, `total()` is virtual; the dynamic type `OPBill` selects `OPBill::total()` at runtime, producing 500. Deleting the `OPBill` through `Bill*` invokes `~OPBill()` then `~Bill()` only because the base destructor is virtual.

## Prediction made before execution

`500 ~OPBill ~Bill ` followed by a newline.

Removing `virtual` from `~Bill` makes deletion through `Bill*` undefined behavior. The C++ standard does not promise a new exact output; commonly only `~Bill` is printed and derived cleanup is skipped. AddressSanitizer can expose invalid resource cleanup but is not required to diagnose every such case. The correct fix is a virtual base destructor.

## Dispatch cost and alternative

Virtual dispatch is one indirect call per bill: O(1) per bill and O(n) for n bills. A `dynamic_cast` chain can perform up to k checks per bill, O(k) per bill and O(nk) worst case. Each polymorphic object typically stores one vptr; exact bytes depend on ABI. A switch avoids that vptr but centralizes type knowledge in the switch, which must change for every new bill kind.
