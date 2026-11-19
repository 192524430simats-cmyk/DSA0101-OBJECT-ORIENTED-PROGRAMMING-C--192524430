## Task A5

Build/run: `g++ -std=c++17 -Wall -Wextra unwinding.cpp -o unwinding && ./unwinding`

Result: stack unwinding destroys the local guard in `f`, then the guard in `main`, before the handler receives 42.
