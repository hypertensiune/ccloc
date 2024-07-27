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

#ifndef CCLOC_P_H
#define CCLOC_P_H

#ifdef WIN32
    #include <windows.h>
#endif
#ifdef __unix__
    #define _DEFAULT_SOURCE
    #include <dirent.h>
#endif
 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define CCLOC_LIB
#include "../include/ccloc.h"
 
#define MAX_FILE_DISPLAY_LEN 50

typedef struct _loc_list_node
{
    char str[MAX_FILE_LEN];
    struct _loc_list_node* next;
    struct _loc_list_node* prev;
} loc_list_node;
 
typedef struct
{
    loc_list_node* first;
    loc_list_node* last;
} loc_list;
 
typedef struct _queue_node
{
    char str[500];
    struct _queue_node* next;
} queue_node;
 
typedef struct
{
    queue_node* head;
    queue_node* tail;
    int len;
} queue;
 
typedef struct
{
    queue* q;
    void* report;
    loc_options* options;
} thread_arg;

void enqueue(queue* q, char* str);
char* dequeue(queue* q);

void loc_list_add(loc_list* list, char* str);
int loc_list_search(loc_list* list, const char* str);

int get_lang(const char* file, loc_options* options);
loc_info parse_file(FILE* file, loc_language* lang);

void loc_report_add(loc_report* report, loc_info* info);
void loc_file_report_add(loc_file_report* report, const char* file, loc_info* info);

// Iterate trough the dictionary given by path and add all found files to a queue for later processing.
int find_files(const char* path, loc_list gitignoreFiles, queue* fileq);

// Comparator for sorting by language first and then by code. Used with -a option
int file_report_comp(const void* a, const void* b);

// Comparators for sorting by code, total, comment lines or by the number of files. Used without -a option.
int report_code_comp(const void* a, const void* b);
int report_total_comp(const void* a, const void* b);
int report_comments_comp(const void* a, const void* b);
int report_files_comp(const void* a, const void* b);

void* thread_worker(void* arg);

#endif