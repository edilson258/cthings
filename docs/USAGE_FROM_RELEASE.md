# C Things Framework

[Learn More](https://github.com/edilson258/cthings)

## Usage from release

This section will guide on how to use cthings from release package. 

1. Download you platform release [here](https://github.com/edilson258/cthings/releases/tag/v0.1.0)
2. Unzip to get the `cthings` folder
3. Include the `cthings/include/cthings.h` on your source file

- `main.c`
```C
#include "cthings/include/cthings.h"

int main(void) {
    // Your trash code goes here
    return 0;
}
```

4. Build your code into <b>object</> file
```shell
clang -c -o main.o main.c
```

5. Link your trash code with my trash code
```shell
clang -o main main.o -lcthings -L./cthings/lib
```
