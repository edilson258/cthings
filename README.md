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

# Building an Example

1. Build The Library
```shell
git clone https://github.com/edilson258/cthings.git
cd cthings
cmake -B build
cmake --build build
```

2. Build example ([Vector](examples/Vector.c))
```shell
clang -o vec.o examples/Vector.c
clang -o vec vec.o -lcthingsstatic -L./build
./vec # run the final executable
```

# Usage

We have no release yet. So the only way of using is by the source code.

# Contributions

This project follows the **KISS (Keep It Simple, Stupid)** principle, ensuring that the codebase remains clean, straightforward, and easy to understand. We welcome contributions from developers of all experience levels, especially those new to coding in C. Whether you're looking to fix bugs, add new features, or improve documentation, your efforts are valued and appreciated.

## Getting Help

If you need any help or have questions, feel free to open an issue or reach out to [me] at [dev.258.edilson@gmail.com]. I encourage you to ask questions and engage with the community.
