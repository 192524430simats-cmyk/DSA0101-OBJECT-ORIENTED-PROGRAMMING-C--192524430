# B1 - Implement and validate polymorphic billing

The completed starter program is `complete_code.cpp`; its three TODOs implement the pure virtual contract and overrides without changing the surrounding starter logic. `billing_matrix.cpp` expands validation to outpatient, inpatient, day-care, and emergency bills across self-pay, insurance, and government payers. Expected totals are computed directly from each formula and checked in the run output.

Removing `virtual` from the pure virtual `total()` declaration leaves a pure virtual function and therefore prevents instantiation of the intended derived types unless the override contract is removed too; the base-pointer call no longer dispatches to a derived implementation. Removing the virtual destructor makes `delete Bill*` undefined behavior and may skip derived destruction. See `actual_output.txt` and `screenshot.png` for the executed result.
