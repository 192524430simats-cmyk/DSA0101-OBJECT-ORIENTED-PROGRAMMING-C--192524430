# A3 - Payer abstraction and extension

`Payer` is an abstract interface with `amountCovered(const Bill&) const`. `SelfPay` covers the bill total. `Insurance` stores a cover limit and co-payment percentage, and covers the lesser of the eligible share and remaining limit. `GovernmentScheme` uses fixed package rates indexed by bill type. Each payer policy is O(1) per bill; the storage is O(1) per payer plus its policy data.

Add a corporate tie-up by deriving `CorporatePayer` and overriding `amountCovered`; the bill classes and billing loop remain unchanged. A `std::function<double(const Bill&)>` policy can also be O(1) per call and captures a cover limit, but data and behavior become less explicit and policy state is hidden in the callable closure.
