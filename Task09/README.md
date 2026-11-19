## Task B4

Build/run: `g++ -std=c++17 -Wall -Wextra final_engineering.cpp -o final_engineering && ./final_engineering`

AddressSanitizer: `g++ -std=c++17 -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer final_engineering.cpp -o final_engineering_asan && ./final_engineering_asan`

Result: TelemedicineBill and CorporatePayer extend the existing interfaces; RAII owns all bills throughout normal and exception paths.
