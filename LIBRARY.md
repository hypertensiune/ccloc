<h2 align="center">CCLOC library</h2>

CCLOC can be used as a static library. You can build the library yourself by running ```make lib```, or download the build static library from the releases section. Include the ```ccloc.h``` header.

By default the library API exposes only the ```ccloc``` function and the required structures to use it. If you want to use the languages & extensions database use the following defines before including the header:
```
#define CCLOC_LANGS_DEFS    // for the defines
#define CCLOC_LANGS         // for the languages database
#define CCLOC_EXTS    // for the extensions database
```

### Example

```
#include "ccloc.h"

int main()
{
    char* path = "main.c";
    loc_options options = {0, 0, 0, 0, 20}; // no extra options, 20 threads
    loc_report report = {.length = 0};

    // options - https://github.com/hypertensiune/ccloc/blob/master/README.md#options
    // report - the final report produced by ccloc after counting
    int result = ccloc(path, &options, &report);

    return 0;
}
```
Build the program and link the statc library:
```
gcc main.c -o main.exe -lccloc
```
