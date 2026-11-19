# B4 - Final engineering decision

`final_engineering.cpp` adds `TelemedicineBill` and `CorporatePayer` as new derived types without modifying the previously defined outpatient/inpatient bill or payer classes. Existing bill processing and settlement use their abstract interfaces. The test includes successful settlement and a thrown/caught claim error while RAII owns the bill objects.

For 15 hospitals processing 200,000 bills/day and extending bill/payer types annually, polymorphism is suitable: extensions add focused classes, and the stable processing loop remains unchanged. Exceptions are appropriate for invalid claims and infrastructure failures, while expected non-approval can be represented as a result type if measurements show high rejection rates. The local build includes an AddressSanitizer attempt; the report distinguishes a clean sanitizer run from toolchain limitations if the runtime is unavailable.

Configuration-driven plug-ins reduce C++ rebuilds but add validation, versioning, and operational risks. Interpreting a rate rule is O(1) per bill in this simple case, with O(rules) storage; a virtual call is also O(1) but its rules are compiled into code.
