# C Things Library
Despite its many strengths, C is a low-level programming language that requires developers to implement data structures and algorithms from scratch. This can be both time-consuming and error-prone.

The C Things Library aims to address these challenges by providing an abstraction layer for common data structures and functionalities. Our library exposes a user-friendly and easy-to-use API, allowing developers to focus on building their applications without reinventing the wheel.

## Features
- [x] [Multiple Producer Single Consumer Channel for thread-safe communication](docs/MPSC.md)
- [x] [Strings methods](docs/STRINGS.md)
- [x] [Queue Data structure](docs/QUEUE.md)
- [ ] Stack Data structure
- [x] [Vectors](docs/VECTOR.md)
- [ ] HashMaps
- [ ] Log System
- [ ] Date and Time
- [ ] Tester Library

## Usage

#### Use from source code

1. Clone and Build

```shell
git clone https://github.com/edilson258/cthings.git
cd cthings
cmake -B build
cmake --build build
python3 headers-joiner.py
```
2. Write some code 

`cthings/main.c`
```c
#include "./build/cthings.h"

int main(void) {
    Vector_t vec = Vector_new();
    // See examples/ for more
    return 0;
}
```

3. Compile and link with `cthings` library

```shell
clang -c -o main.o main.c
clang -o main main.o -lcthings -L./build
```

#### Use from release (linux)

1. Download the release for your platform
2. Unzip the file
3. write some code

`main.c`
```c
#include "./cthings/include/cthings.h"

int main(void) {
    Vector_t vec = Vector_new();
    // See examples folder for more
    return 0;
}
```

## Contributions

This project follows the **KISS (Keep It Simple, Stupid)** principle, ensuring that the codebase remains clean, straightforward, and easy to understand. We welcome contributions from developers of all experience levels, especially those new to coding in C. Whether you're looking to fix bugs, add new features, or improve documentation, your efforts are valued and appreciated.

### Getting Help

If you need any help or have questions, feel free to open an issue or reach out to [me](mailto:dev.258.edilson@gmail.com). I encourage you to ask questions and engage with the community.
