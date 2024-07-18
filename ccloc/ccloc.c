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
 
#include "langs.h"
 
#define MAX_REPORTS 100
#define MAX_FILE_LEN 500
#define MAX_FILE_DISPLAY_LEN 50
 
#define ARG(i, s) (strcmp(argv[i], s) == 0)

#ifndef WIN32
	#define max(x, y) ((x) > (y) ? (x) : (y))
#endif
 
pthread_mutex_t mutex;
 
struct loc_options
{
    int all;
    int time;
    int sort;
    char sort_method[10];
    int langs;
    int langs_n;
    char langs_array[100][20];
} options;
 
typedef struct
{
    int total_lines;
    int com_lines;
    int code_lines;
    int blank_lines;
    int files;
    long long bytes;
} loc_info;
 
typedef struct 
{
    int language_id;
    loc_info info;
} loc_file_report;
 
typedef struct
{
    int length;
    loc_file_report data[MAX_REPORTS];
    loc_file_report total;
} loc_report;
 
 
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
    loc_report* report;
} thread_arg;
 
void enqueue(queue* q, char* str)
{
    queue_node* n = calloc(1, sizeof(queue_node));
    n->next = NULL;
    strcpy(n->str, str);
 
    if(q->head == NULL && q->tail == NULL)
    {
        q->tail = n;
        q->head = n;
        q->len = 1;
    }
    else
    {
        q->len++;
        q->tail->next = n;
        q->tail = q->tail->next;
    }
}
 
char* dequeue(queue* q)
{
    pthread_mutex_lock(&mutex);
 
    char* ret = NULL;
    if(q->len > 0)
    {
        queue_node* n = q->head;
        q->head = q->head->next;

        // change pointed by https://www.reddit.com/r/C_Programming/comments/1e5r8r0/comment/ldp2t32/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
        
        //ret = calloc(MAX_FILE_LEN, sizeof(char));
        //strcpy(ret, n->str);

        ret = n->str;

        //free(n);
        q->len--;
    }
 
    pthread_mutex_unlock(&mutex);
    return ret;
}
 
static inline void PRINT_REPORT_HEADER()
{
    printf("--------------------------+------------+------------+------------+------------\n");
    printf("%-25s | %10s | %10s | %10s | %10s\n", "Language", "Total", "Code", "Comments", "Files");
    printf("--------------------------+------------+------------+------------+------------\n");
}
 
static inline void PRINT_REPORT(loc_file_report* report)
{
    printf("%-25s | %10d | %10d | %10d | %10d\n", languages[report->language_id].name, report->info.total_lines, report->info.code_lines, report->info.com_lines, report->info.files);
}
 
static inline void PRINT_REPORT_TOTAL(loc_file_report* total)
{
    printf("--------------------------+------------+------------+------------+------------\n");
    PRINT_REPORT(total);
    printf("--------------------------+------------+------------+------------+------------\n");
}
 
static inline void PRINT_FILE_REPORT_HEADER()
{
    printf("---------------------------------------------------+---------------------------+------------+------------+------------\n");
    printf("%-50s | %25s | %10s | %10s | %10s\n", "File", "Language", "Total", "Code", "Comments");
    printf("---------------------------------------------------+---------------------------+------------+------------+------------\n");
}

static inline void PRINT_FILE_REPORT(char* file, int lang_id,  loc_info *li)
{
    int len = max(strlen(file), MAX_FILE_DISPLAY_LEN);
    file = file + len - 50;
    file[0] = '~';
    printf("%-50s | %-25s | %10d | %10d | %10d\n", file, languages[lang_id].name, li->total_lines, li->code_lines, li->com_lines);
}
 
static inline void PRINT_FILE_REPORT_TOTAL(loc_info *li)
{
    printf("---------------------------------------------------+---------------------------+------------+------------+------------\n");
    printf("%-50s | %-25s | %10d | %10d | %10d\n", "TOTAL", "", li->total_lines, li->code_lines, li->com_lines);
    printf("---------------------------------------------------+---------------------------+------------+------------+------------\n");
}
 
static inline void PRINT_TIME_STATS(double time, int files, long long bytes)
{
    double files_per_sec = files / time;
    double bytes_per_sec = bytes / time;
 
    if(time >= 1)
        printf("Took: %lf seconds\n", time);
    else
        printf("Took: %.2lf milliseconds\n", time * 1000);
 
    printf("Parsed %d files, files/s: %.2lf\n", files, files_per_sec);
    printf("Read %lld bytes (%.2lf megabytes), bytes/s: %.2lf (mb/s: %.2lf)\n", bytes, bytes / 1e6, bytes_per_sec, bytes_per_sec / 1e6);
    printf("\n\n");
}
 
static inline void PRINT_HELP()
{
    printf("ccloc v1.0.1\nhttps://github.com/hypertensiune/ccloc\n\n");
    printf("Usage:\n ccloc <directory|file> [options]\n\n");
    printf("Options:\n");
    printf(" -h,  --help                 Print this info\n");
    printf(" -a,  --all                  Show details about every file\n");
    printf(" -t,  --time                 Show time taken\n");
    printf(" -th, --threads <number>     Set the number of threads to be used (5 default)");
    printf(" -s,  --sort <method>        Sort by (sorted by code by default)\n");
    printf("      methods: <total|code|comments|files>\n");         
    printf(" -l,  --langs [langs]        Select only specified languages\n");
    printf("      langs: name of any supported language\n");
    printf("\n\n");
}
 
 
void loc_list_add(loc_list* list, char* str)
{
    loc_list_node* n = calloc(1, sizeof(loc_list_node));
    strcpy(n->str, str);
 
    n->next = NULL;
 
    if(list->last == NULL)
    {
        n->prev = NULL;
        list->first = list->last = n;
    }
    else
    {
        n->prev = list->last;
        list->last->next = n;
        list->last = n;
    }
}
 
int loc_list_search(loc_list* list, const char* str)
{
    loc_list_node* p = list->first;
    while(p != NULL)
    {
        // use custom comparator that considers that '/' and '\' are the same
 
        int result = 1;
        for(int i = 0, j = 0; p->str[i] || str[j]; i++, j++)
            if(p->str[i] != str[j])
            {
                if(!(p->str[i] == '/' && str[j] == '\\') && !(p->str[i] == '\\' && str[j] == '/'))
                {
                    result = 0;
                    break;
                }
            }
 
        if(result)
        {
            return 1;
        }
 
        p = p->next;
    }
    return 0;
}
 
int get_lang(char* file)
{
    char aux[MAX_FILE_LEN];
    strcpy(aux, file);
    
    char* extension = NULL;
    
    // changed strtok to strtok_r which is thread safe 
    // pointed by https://www.reddit.com/r/C_Programming/comments/1e5r8r0/comment/ldp2t32/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
    char* save;
    char* tok = strtok_r(aux, ".", &save);
    while(tok != NULL)
    {   
        extension = tok;
        tok = strtok_r(NULL, ".", &save);
    }
 
    // return -1 if the files doesn't have an extension
    // prevents comparing an uninitialized pointed further down
    if(extension == NULL)
        return -1;

    int l = 0, r = EXTENSIONS_SIZE - 1;
    
    while(l <= r)
    {
        int m = (l + r) / 2;
        int comp = strcmp(extension, extensions[m].name);
        if(comp == 0)
        {
            int lang_id = extensions[m].lang_id;
 
            // if wanted languages are specified check if the identified 
            // language of the current file is in that list
            if(options.langs_n > 0)
            {
                int found = 0;
                for(int i = 0; i < options.langs_n; i++)
                {
                    if(strcmp(languages[lang_id].name, options.langs_array[i]) == 0)
                    {
                        found = 1;
                        break;
                    }
                }
                if(!found)
                    return -1;
            }
            return extensions[m].lang_id;
        }
        else if(comp < 0)
            r = m - 1;
        else
            l = m + 1;
    }
 
    return -1;
}
 
loc_info parse_file(FILE* file, loc_language* lang)
{
    loc_info info = {0, 0, 0, 0, 0, 0};
 
    char c;
    int com_status = 0;
 
    int cc = 0, sc = 0;
 
    int sl = strlen(lang->com.sl);
    int mls = strlen(lang->com.ml_start);
    int mle = strlen(lang->com.ml_end);
 
    if(options.time)
    {
        // https://stackoverflow.com/a/238607
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        info.bytes = (long long)size;
 
        fseek(file, 0, SEEK_SET);
    }
 
    char* s2 = calloc(1000, sizeof(char));
    while(fgets(s2, 1000, file))
    {
        info.total_lines++;
 
        char* s = s2;
        while(isspace(s[0]) && s[0] != '\n')
            s++;
 
        if(s[0] == '\n' && com_status == 0)
        {
            info.blank_lines++;
            continue;
        }
 
        if(sl > 0 && memcmp(s, lang->com.sl, sl) == 0)
        {
            info.com_lines++;
        }
 
        if(mls > 0)
        {   
            if(com_status == 0)
            {
                if(memcmp(s, lang->com.ml_start, mls) == 0)
                {
                    com_status = 1;
                }
            }
            else 
            {
                if(memcmp(s, lang->com.ml_end, mle) == 0)
                {
                    info.com_lines++;
                    com_status = 0;
                }
            }
        }
 
        if(com_status == 1)
            info.com_lines++;
    }
    free(s2);
 
    info.code_lines = info.total_lines - info.com_lines - info.blank_lines;
 
    return info;
}
 
void lang_report_add(loc_report* report, int language_id, loc_info* info)
{
    // check if the current language is already added in the final report
 
    pthread_mutex_lock(&mutex);
 
    int index = report->length;
    for(int i = 0; i < report->length; i++)
    {
        if(report->data[i].language_id == language_id)
        {
            index = i;
            break;
        }
    }
 
    if(index != report->length)
        report->data[index].info.files++;
    else
    {
        report->data[index].language_id = language_id;
        report->data[index].info.files = 1;
        report->length++;
    }
 
    report->data[index].info.blank_lines += info->blank_lines;
    report->data[index].info.code_lines += info->code_lines;
    report->data[index].info.com_lines += info->com_lines;
    report->data[index].info.total_lines += info->total_lines;
 
    report->total.info.blank_lines += info->blank_lines;
    report->total.info.code_lines += info->code_lines;
    report->total.info.com_lines += info->com_lines;
    report->total.info.total_lines += info->total_lines;
    report->total.info.files++;
    report->total.info.bytes += info->bytes;
 
    pthread_mutex_unlock(&mutex);
}
 
#ifdef WIN32
    int loc(const char* path, loc_list gitignoreFiles, queue* fileq)
    {
        // if the current directory contains a .gitignore file use it to skip files from parsing
        char gitpath[MAX_FILE_LEN];
        sprintf(gitpath, "%s\\.gitignore", path);
 
        FILE* fgit = fopen(gitpath, "r");
        if(fgit != NULL)
        {
            char ignored[MAX_FILE_LEN];
            while(fscanf(fgit, "%s", ignored) == 1)
            {
                if(ignored[0] == '/')
                    sprintf(gitpath, "%s%s", path, ignored);
                else
                    sprintf(gitpath, "%s\\%s", path, ignored);
                loc_list_add(&gitignoreFiles, gitpath);
            }
        }
        fclose(fgit);
 
        char file[MAX_FILE_LEN];
        sprintf(file, "%s\\*", path);
 
        WIN32_FIND_DATA findData;
        HANDLE findHnd = NULL;
 
 
        // return if current path is invalid
        // if((findHnd = FindFirstFileEx(file, FindExInfoBasic, &findData, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH)) == INVALID_HANDLE_VALUE)    
        if((findHnd = FindFirstFile(file, &findData)) == INVALID_HANDLE_VALUE)
            return -1;
 
        // Find all files in the current path. 
        // If a file is a directory (FILE_ATTRIBUTE_DIRECTORY) recursively call the function with the new path
        do 
        {
            // continue if the current file is . or .. to avoid getting in the same directory again and in the parent directory
            if(strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
                continue;
 
            sprintf(file, "%s\\%s", path, findData.cFileName);
 
            // continue if the current file is ignored by a .gitignore file
            if(loc_list_search(&gitignoreFiles, file))
                continue;
 
            if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                loc(file, gitignoreFiles, fileq);
            }
            else
            {     
                enqueue(fileq, file);
            }
 
        } while(FindNextFile(findHnd, &findData));
 
        FindClose(findHnd);
 
        return 0;
    }
#endif
 
#ifdef __unix__
    int loc(const char* path, loc_list gitignoreFiles, queue* fileq)
    {
        // if the current directory contains a .gitignore file use it to skip files from parsing
        char gitpath[MAX_FILE_LEN];
        sprintf(gitpath, "%s/.gitignore", path);

        FILE* fgit = fopen(gitpath, "r");
        if(fgit != NULL)
        {
            char ignored[MAX_FILE_LEN];
            while(fscanf(fgit, "%s", ignored) == 1)
            {
                if(ignored[0] == '/')
                    sprintf(gitpath, "%s%s", path, ignored);
                else
                    sprintf(gitpath, "%s/%s", path, ignored);
                loc_list_add(&gitignoreFiles, gitpath);
            }
            fclose(fgit); 
        }

        char file[MAX_FILE_LEN];
        
        // return if current path is invalid
        DIR* d = opendir(path);
        if(d == NULL)
            return -1;
 
        // Find all files in the current path.
        // If a file is a directory (dir->d_type == DT_DIR) recursively call the function with the new path 
        struct dirent* dir;
        while((dir = readdir(d)) != NULL)
        {
            // continue if the current file is . or .. to avoid getting in the same directory again and in the parent directory
            if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
                continue;

            sprintf(file, "%s/%s", path, dir->d_name);

            // continue if the current file is ignored by a .gitignore file
            if(loc_list_search(&gitignoreFiles, file))
                continue;

            sprintf(file, "%s/%s", path, dir->d_name);
            if(dir->d_type != DT_DIR)
                enqueue(fileq, file);
            else
                loc(file, gitignoreFiles, fileq);
        }
 
        closedir(d);
 
        return 0;
    }
#endif
 
int report_code_comp(const void* a, const void* b)
{   
    int aa = ((loc_file_report*)a)->info.code_lines;
    int bb = ((loc_file_report*)b)->info.code_lines;
    return (aa < bb) - (aa > bb);
}
 
int report_total_comp(const void* a, const void* b)
{
    int aa = ((loc_file_report*)a)->info.total_lines;
    int bb = ((loc_file_report*)b)->info.total_lines;
    return (aa < bb) - (aa > bb);
}
 
int report_comments_comp(const void* a, const void* b)
{
    int aa = ((loc_file_report*)a)->info.com_lines;
    int bb = ((loc_file_report*)b)->info.com_lines;
    return (aa < bb) - (aa > bb);
}
 
int report_files_comp(const void* a, const void* b)
{
    int aa = ((loc_file_report*)a)->info.files;
    int bb = ((loc_file_report*)b)->info.files;
    return (aa < bb) - (aa > bb);
}
 
void* thread_worker(void* arg)
{
    thread_arg* targ = (thread_arg*)arg;
    char* s = NULL;
    while((s = dequeue(targ->q)) != NULL)
    {

        int lang_id = get_lang(s);
        if(lang_id != -1)
        {
            FILE* f = fopen(s, "r");
            loc_info info = parse_file(f, &languages[lang_id]);
            fclose(f);
 
            if(options.all)
            {
                PRINT_FILE_REPORT(s, lang_id, &info);
            }
 
            lang_report_add(targ->report, lang_id, &info);
        }
        free(s);
    }
}
 
int main(int argc, char** argv)
{    
    int nthreads = 20;
    pthread_t threads[100];

    if(argc < 2 || ARG(1, "-h") || ARG(1, "--help") || argv[1][0] == '-')
    {
        PRINT_HELP();
        return 0;
    }
 
    for(int i = 2; i < argc; i++)
    {
        if(ARG(i, "-a") || ARG(i, "--all"))
        {
            options.all = 1;
            nthreads = 1;
        }
        if(ARG(i, "-t") || ARG(i, "--time"))
            options.time = 1;
        if(ARG(i, "-th") || ARG(i, "--threads"))
        {
            i++;
            nthreads = atoi(argv[i]);
        }
        if(ARG(i, "-s") || ARG(i, "--sort"))
        {
            options.sort = 1;
            i++;
            strcpy(options.sort_method, argv[i]);
        }
        if(ARG(i, "-l") || ARG(i, "--langs"))
        {
            options.langs = 1;
            i++;
            while(i < argc && argv[i][0] != '-')
                strcpy(options.langs_array[options.langs_n++], argv[i++]);
            i--;
        }
    }

    clock_t begin = clock();
 
    // if the path given is a file open and process it right away
    if(strcmp(argv[1], ".") != 0 && strcmp(argv[1], "..") != 0)
    {
        #ifdef WIN32
            FILE* f = fopen(argv[1], "r");
        #else
            // avoid opening directories on unix operating systems
            // https://stackoverflow.com/questions/42876210/c-fopen-opening-directories
            FILE* f = fopen(argv[1], "r+");
        #endif
        if(f != NULL)
        {
            int lang_id = get_lang(argv[1]);
            if(lang_id == -1)
                return 0;
            
            loc_info info = parse_file(f, &languages[lang_id]);
            fclose(f);
    
            PRINT_REPORT_HEADER();
            printf("%-25s | %10d | %10d | %10d | %10d\n", languages[lang_id].name, info.total_lines, info.code_lines, info.com_lines, 1);
            printf("--------------------------+------------+------------+------------+------------\n\n");
    
            return 0;
        }
    }

    loc_list gitignoredFiles = {NULL, NULL};
    loc_list_add(&gitignoredFiles, ".\\.gitignore");

    loc_report report = {.length = 0, .total.language_id = TOTAL};
 
    queue fileq;
    fileq.head = fileq.tail = NULL;

    if(options.all)
    {
        PRINT_FILE_REPORT_HEADER();
    }

    int r = loc(argv[1], gitignoredFiles, &fileq);
    if(r == -1)
    {
        printf("ERROR: Path not found!\n");
        return 0;
    }

    thread_arg targ = {&fileq, &report};
 
    pthread_mutex_init(&mutex, NULL);
    for(int i = 0; i < nthreads; i++)
        pthread_create(&threads[i], NULL, thread_worker, &targ);
 
    for(int i = 0; i < nthreads; i++)
        pthread_join(threads[i], NULL);
 
    // if there is no sort option default to sort by number of code lines
    if(!options.sort || (options.sort && strcmp(options.sort_method, "code") == 0))
    {
        qsort(report.data, report.length, sizeof(loc_file_report), &report_code_comp);
    }
    else
    {
        if(strcmp(options.sort_method, "total") == 0)
        {
            qsort(report.data, report.length, sizeof(loc_file_report), &report_total_comp);
        }
        else if(strcmp(options.sort_method, "comments") == 0)
        {
            qsort(report.data, report.length, sizeof(loc_file_report), &report_comments_comp);
        }
        else if(strcmp(options.sort_method, "files") == 0)
        {
            qsort(report.data, report.length, sizeof(loc_file_report), &report_files_comp);
        }
    }
 
    clock_t end = clock();
 
    if(!options.all)
    {   
        PRINT_REPORT_HEADER();
        for(int i = 0; i < report.length; i++)
        {
            PRINT_REPORT(&report.data[i]);
        }
        PRINT_REPORT_TOTAL(&report.total);
    }
    else
    {
        PRINT_FILE_REPORT_TOTAL(&report.total.info);
    }
 
    if(options.time)
    {
        PRINT_TIME_STATS((double)(end - begin) / CLOCKS_PER_SEC, report.total.info.files, report.total.info.bytes);
    }
 
    return 0;
}