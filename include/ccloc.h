/*
    MIT License

    Copyright (c) 2024 hypertensiune

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef CCLOC_H
#define CCLOC_H

#if defined CCLOC_LIB || defined CCLOC_ALL
    #define CCLOC_LANGS_DEFS
    #define CCLOC_LANGS
    #define CCLOC_EXTS
#endif

#include "langs.h"

#define MAX_REPORTS 100
#define MAX_FILE_REPORTS 1000

#define MAX_FILE_LEN 500

#define CCLOC_SUCCESS 0
#define CCLOC_FILE_NOT_FOUND -1
#define CCLOC_FILES_SKIPPED -2

typedef struct
{
    int language_id;
    int total_lines;
    int com_lines;
    int code_lines;
    int blank_lines;
    int files;
    long long bytes;
} loc_info;

// loc_report is the final report in the default mode. (Contains details about every language used)
typedef struct
{
    double time;
    int length;
    loc_info data[MAX_REPORTS];
    loc_info total;
} loc_report;

// loc_file_report is the final report in the "all" mode. (Contains details about every file parsed)
typedef struct
{
    double time;
    int length;
    int capacity;
    struct 
    {
        loc_info info;
        char file[MAX_FILE_LEN];
    } *data;
    loc_info total;
} loc_file_report;

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

#ifdef CCLOC_LANGS
    extern loc_language languages[];
#endif

#ifdef CCLOC_EXTS
    extern loc_extension extensions[];
#endif

/**
 * @param path The file/directory on which to perform the counting
 * @param options Usage options of the tool
 * @param report The final report produced by ccloc after counting
 * @returns CCLOC_X status code
 */
int ccloc(const char* path, loc_options* options, void* report);

#endif