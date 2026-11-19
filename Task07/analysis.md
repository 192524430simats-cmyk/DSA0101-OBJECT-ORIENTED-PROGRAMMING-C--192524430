# B2 - Engineer error conditions

Tests cover a valid amount, a negative amount, amount above the cover, an unknown package, nonnumeric input passed to `std::stod`, and a guaranteed oversized `operator new` request caught as `std::bad_alloc`. The completed TODO program prints `approved 40000`, then audits and rethrows the over-cover `ClaimError`, then reports the negative-amount `invalid_argument`.

The supplied prediction program should print `ok done caught negative [log too large] caught too large ` and a newline. Only `out_of_range` is logged inside `process`; `invalid_argument` bypasses that handler. `throw;` keeps the same exception object/type, whereas `throw e;` creates an exception from the static type of `e` and can slice derived information.
