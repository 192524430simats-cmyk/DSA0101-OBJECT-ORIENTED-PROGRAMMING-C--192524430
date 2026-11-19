# A4 - Exception strategy

The hierarchy is `std::exception` → `BillingError` → `ClaimError`, with specialized input/package errors derived from `BillingError`. Negative charges use `std::invalid_argument`; billed amount above cover uses `ClaimError`; unknown package and missing patient record use typed billing errors; allocation failure remains `std::bad_alloc`.

Validation, bill creation, and claim approval may throw. Destructors, cleanup, and simple `noexcept` observers do not throw. A destructor throwing during stack unwinding can terminate the process, so cleanup reports errors through separate status/logging paths. Return codes avoid exception transfer but require every caller to check and pass error details explicitly. Normal successful return-code calls and exception calls are both O(1); exceptions can be expensive when errors are thrown, while return-code checks execute on every path.
