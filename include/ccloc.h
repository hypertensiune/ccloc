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

#include "langs.h"

#define MAX_REPORTS 100

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

typedef struct
{
    int length;
    loc_info data[MAX_REPORTS];
    loc_info total;
    double time;
} loc_report;

typedef struct 
{
    int all;
    int time;
    int sort;
    char sort_method[10];
    int langs;
    int langs_n;
    char langs_array[100][20];
    int threads;
} loc_options;

extern loc_language languages[];
extern loc_extension extensions[];

/**
 * @param path The file/directory on which to perform the counting
 * @param options Usage options of the tool
 * @param report The final report produced by ccloc after counting
 * @returns CCLOC_X status code
 */
int ccloc(const char* path, loc_options* options, loc_report* report);

#endif