# peroxide-h

peroxide-h is meant to be a safer C library that is more comfortable to work with than Rust lang.

## Installation

To install peroxide-h, you can use the following command:

```bash
./install.sh
```

Windows and macOS support is not available yet.

## Usage

### Printing to the console

```c
#include <peroxide.h>

int main() {
    px_print("Hello, World!\n");
    return 0;
}
```
