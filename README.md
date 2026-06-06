# Lightweight `printf` Implementation in C

A minimal, dependency-free implementation of `printf`, written in C.  
This project is designed as a drop-in alternative for simple formatted output in environments where the standard C library may not be available or desired.

---

## Features

- Core format specifiers:
  - `%c` → single character
  - `%s` → C-string
  - `%d` → signed integer
  - `%u` → unsigned integer
  - `%o` → octal
  - `%x` → hexadecimal (lowercase)
  - `%p` → pointer address
- Outputs directly to `stdout` using `write()`
- Self-contained, no external dependencies
- Extensible design for adding more specifiers

---

## Build

```bash
gcc -O2 -Wall -Wextra -Werror -o myprintf my_printf.c

Example

#include "my_printf.h"

int main() {
    int num = 42;
    char* str = "Hello";
    void* ptr = &num;
    
    my_printf("String: %s, Number: %d, Pointer: %p", str, num, ptr);
    return 0;
}

Output:
$ ./my_printf
A String 100 144 64 1 0x7ffd5a3a8a5c
```

## Technical Details

Demonstrates variadic functions, direct syscalls via write(), 
manual memory management, and multi-base number conversion.


## License
This project is open source and available under the [MIT License.](LICENSE)
