# A1 - Polymorphic bill hierarchy

## Common contract

Every bill provides `total() const`, `type() const`, and `print() const`. The common state is the patient or encounter identifier. Bill-specific inputs remain in derived classes: consultation and tests for outpatient, days/rate/procedure for inpatient, package price for day care, and base/time charge for emergency. A virtual destructor makes deletion through `Bill*` safe.

## Hierarchy

`Bill` is abstract: `total` is pure virtual, while `type` and `print` are virtual. `OutPatientBill`, `InPatientBill`, `DayCareBill`, and `EmergencyBill` override `total` and `type`. The diagram is in `uml.svg`.

## Daily total pseudocode

```text
ALGORITHM TotalDay(bills[0..n-1])
    total <- 0
    FOR i <- 0 TO n - 1
        total <- total + bills[i].total()
    END FOR
    RETURN total
END ALGORITHM
```

The dispatch is O(1) per bill, so a full pass is O(n) time and O(1) auxiliary space. The alternative tagged `Bill` plus `switch` is also O(n); each record carries a tag and the switch must be updated for a new type, whereas a polymorphic extension can add a derived type without editing the processing loop.

## Validation assumptions

All monetary values are nonnegative; a bill cannot be printed before its constructor has validated its inputs. This assignment's starter uses `double`, so the examples use exact whole rupee amounts. A production implementation should use integer paise or a decimal money type.
