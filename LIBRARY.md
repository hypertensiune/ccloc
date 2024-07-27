<h2 align="center">CCLOC library</h2>

CCLOC can be used as a static library. You can build the library yourself by running ```make lib```, or download the built static library from the releases section. Include the ```ccloc.h``` header.

By default the library API exposes only the ```ccloc``` function and the required structures to use it. If you want to use the languages & extensions database use the following defines before including the header:
```
#define CCLOC_LANGS_DEFS    // for the defines
#define CCLOC_LANGS         // for the languages database
#define CCLOC_EXTS          // for the extensions database
```

All the [options](https://github.com/hypertensiune/ccloc/blob/master/README.md#options) that are used with the ccloc cli tool can be used with the library. The time options doesn't need to be specified, as it is used only by the cli tool to display the time stats (time is calculated regardless of this options). Options are set using the ```loc_options```:
```
typedef struct 
{
    int all;
    int time;
    int sort;
    int langs;
    int threads;
    int langs_n;
    char sort_method[10];
    char langs_array[100][20];
} loc_options;
```

The resulting report is found in the ```report``` parameter of the ```ccloc``` function. If option -a is used ccloc expects that paramter to be a ```loc_file_report``` otherwise a ```loc_report```.

### Example

```
// > ccloc .
#include "ccloc.h"

int main()
{
    char* path = "main.c";
    loc_options options = {0, 0, 0, 0, 20}; // no extra options, 20 threads
    loc_report report = {.length = 0};

    int result = ccloc(path, &options, (void*)&report);

    return 0;
}
```

```
// > ccloc . -a
#include "ccloc.h"

int main()
{
    char* path = ".";
    loc_options options = {1, 0, 0, 0, 20}; // -a, 20 threads
    loc_file_report report = {0, 0, 0, 0, NULL};

    int result = ccloc(path, &options, (void*)&report);

    return 0;
}

```
```
// > ccloc . -s comments -l Python
#include "ccloc.h"

int main()
{
    char* path = ".";
    loc_report report = {.length = 0};

    loc_options options = {0, 0, 1, 1, 20}; // -s -l, 20 threads
    options.langs = 1;
    strcpy(options.langs_array[0], "Python");
    strcpy(options.sort_method, "comments");
    
    int result = ccloc(path, &options, (void*)&report);

    return 0;
}
```

Build the program and link the statc library:
```
gcc main.c -o main.exe -lccloc
```