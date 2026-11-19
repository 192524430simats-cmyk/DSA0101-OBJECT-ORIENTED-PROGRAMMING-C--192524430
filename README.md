# Assignment 5 - Reliable Hospital Billing

**Student:** Mohamed Haarun M.H  
**Register number:** 192524430  
**Course:** DSA0101 - Object-Oriented Programming with C++ (CO5)  
**Repository:** https://github.com/192524430simats-cmyk/DSA0101-OBJECT-ORIENTED-PROGRAMMING-C--192524430  
**Compiler:** g++ 13.3.0 (MinGW-w64/UCRT for local command compatibility; GitHub Actions uses Ubuntu g++)  

## Build and run

Run commands from this directory. Standard task programs use:

```sh
g++ -std=c++17 -Wall -Wextra Task02/binding.cpp -o binding
./binding
```

Replace `Task02/binding.cpp` and `binding` with each program path and executable name. The benchmark command is:

```sh
g++ -std=c++17 -O2 -Wall -Wextra Task08/benchmark.cpp -o benchmark
./benchmark
```

The sanitizer commands are:

```sh
g++ -std=c++17 -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer Task09/final_engineering.cpp -o final_engineering
./final_engineering
```

The intentionally incorrect non-virtual destructor experiment is separate under `Task06/experiments/`; run it with `ASAN_OPTIONS=detect_leaks=1` on a GCC/Linux environment to observe the missed derived cleanup.

## Task index

| Folder | Assignment task | Main contents |
|---|---|---|
| Task01 | A1 | Bill hierarchy, UML, processing pseudocode, complexity |
| Task02 | A2 | Binding prediction/program, three vtable diagrams, destructor analysis |
| Task03 | A3 | Payer interface, policies, corporate extension example |
| Task04 | A4 | Error inventory, exception hierarchy, strategy code |
| Task05 | A5 | Catch/rethrow plan, stack unwinding, RAII output program |
| Task06 | B1 | Completed TODO program, all bill/payer tests, negative experiments |
| Task07 | B2 | Completed claim TODO, invalid-input and allocation-failure cases |
| Task08 | B3 | Virtual/switch/variant timing and return-code/exception measurements |
| Task09 | B4 | New bill and payer types, sanitizer run, final design decision |

Every task folder contains its written response and supporting evidence. Executed output screenshots, measured results, and the complete PDF are included when the run workflow finishes. Source code and test inputs are stored alongside each task.

## Results and evidence

`Assignment5_Report.pdf` contains the task responses, full source listings, diagrams, input/output evidence, benchmark table, and sanitizer findings. `DSA0101-192524430-ASSIGNMENT5.zip` is the complete project package. Measurements are specific to the recorded runner and should be repeated on the submission machine before final submission.

