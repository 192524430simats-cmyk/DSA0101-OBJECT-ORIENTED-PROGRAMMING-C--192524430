# A5 - Recovery, rethrowing, and RAII

The logging layer catches a specific exception, records context, and uses `throw;` to rethrow the same exception. The application boundary catches `std::exception` and produces a safe user-facing message. A final `catch (...)` is a last-resort boundary for unknown exceptions.

For the supplied program, the predicted and observed sequence is `~f ~main caught 42` followed by a newline. Throwing exits `f`, so local `Guard g` is destroyed; propagation then leaves the `try` block, destroying `Guard m`; only then does the handler print. `not printed` is unreachable after `f()` throws. RAII objects release resources during stack unwinding, avoiding a separate manual delete for every error path. Rethrow with `throw;`, not `throw e;`, to preserve the dynamic exception type.
