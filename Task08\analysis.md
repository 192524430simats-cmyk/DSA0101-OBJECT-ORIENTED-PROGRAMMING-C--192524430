# B3 - Correctness, throughput, and exception cost

The benchmark compares virtual calls through a base interface, a tagged record with `switch`, and `std::variant` with `std::visit`. Each method computes the same checksum for 10 bills and for 1,000, 1,000,000, and 10,000,000 bills. The exception experiment checks 1,000,000 claims with 0%, 1%, and 50% invalid cases against return-code validation. Results are recorded in `measurements.csv` with the compiler command and machine context; timing is environment-dependent and should be repeated on the submission machine.

All approaches are O(n) for a full batch. Variant stores enough space for its largest alternative plus a discriminator, switch stores a tag, and virtual objects commonly store a vptr. Prefer virtual interfaces when types are extended independently; variant for a closed type set; switch for a small fixed set. Use exceptions for exceptional failures, not routine expected rejection rates.
