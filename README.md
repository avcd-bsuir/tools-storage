[![License](https://img.shields.io/badge/license-CC%20BY--NC--SA%204.0-blue.svg)](https://bit.ly/cc-by-nc-sa-40)

# Installation

Add submodule:
```
$ git submodule add https://github.com/avcd-bsuir/tools-storage third-party/tools-storage
```

Update all submodules:
```
$ git submodule update --remote
```

Add
```json
"C_Cpp.default.includePath": [
    "${workspaceFolder}/third-party/tools-storage/include"
]
```
to your local VSCode `settings.json` file

Do not forget to add include flag to your compiler command:
```
-I"third-party/tools-storage/include"
```

# Tools: Storage

Implementations of some storage types in C.

# Usage

To use Storage library add
```c
#include "storage/Storage.h"
```
to your program.

## Array

```c
Array array; // Create Array object
aArrayInit(&array, 10, int); // Initialize array with 10 integers

int value = 10;
aArraySet(&array, 5, &int); // Set 5-th element to value
aArraySetI(&array, 6, 11); // Set 6-th element to 11
aArrayPushI(&array, 12); // Push 12. If array does not have enough space it will be grown
aArrayInsertI(&array, 3, 13); // Insert 13 to the 3rd position

value = aArrayGetAs(&array, 3, int); // Get 3rd element from array as integer
value = aArrayPopAs(&array, int); // Get last element from array as integer and remove it from array

aArrayRemove(&array, 5); // Remove 5th element from array

aArrayDestroy(&array); // Free allocated space
```

# Credits

Written by Alexey Filich.

# License

This repository is licensed under [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International](LICENCE.md).
