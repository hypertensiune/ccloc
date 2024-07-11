#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "langs.h"

#define SIZE(x) (sizeof(x) / sizeof(x[0]))
#define ARG(i, s) (strcmp(argv[i], s) == 0)

struct loc_options
{
    int all;
    int code;
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
} loc_info;

typedef struct 
{
    char language[20];
    int files;
    loc_info info;
} loc_lang_report;

typedef struct
{
    int length;
    loc_lang_report data[100];
    loc_lang_report total;
} loc_report;

typedef struct 
{
    char* file_name;
    loc_language* lang;
} loc_file;

typedef struct
{
    int k;
    int len;
    int max_filename_length;
    loc_file* files;
} loc_files;

typedef struct _loc_list_node
{
    char str[500];
    struct _loc_list_node* next;
    struct _loc_list_node* prev;
} loc_list_node;

typedef struct
{
    loc_list_node* first;
    loc_list_node* last;
} loc_list;

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

void loc_list_delete(loc_list* list)
{
    loc_list_node* n = list->last;
    list->last->next = NULL;

    n->prev = NULL;
    free(n);
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
            return 1;

        p = p->next;
    }
    return 0;
}

static inline void PRINT_REPORT(char* lang, loc_info *li, int files)
{
    printf("%-25s | %10d | %10d | %10d | %10d\n", lang, li->total_lines, li->code_lines, li->com_lines, files);
}

static inline void PRINT_FILE_REPORT(char* file, char* lang,  loc_info *li)
{
    printf("%-50s | %-25s | %-10d | %-10d | %-10d\n", file, lang, li->total_lines, li->code_lines, li->com_lines);
}

static inline void PRINT_TOTAL(loc_info *li)
{
    printf("--------------------------+------------+------------+------------+------------\n");
    printf("%-25s | %-10d | %-10d | %-10d | %-10d\n", "TOTAL", li->total_lines, li->code_lines, li->com_lines, li->files);
}

int report_code_comp(const void* a, const void* b)
{   
    int aa = ((loc_lang_report*)a)->info.code_lines;
    int bb = ((loc_lang_report*)b)->info.code_lines;
    return (aa < bb) - (aa > bb);
}

int report_total_comp(const void* a, const void* b)
{
    int aa = ((loc_lang_report*)a)->info.total_lines;
    int bb = ((loc_lang_report*)b)->info.total_lines;
    return (aa < bb) - (aa > bb);
}

int report_comments_comp(const void* a, const void* b)
{
    int aa = ((loc_lang_report*)a)->info.com_lines;
    int bb = ((loc_lang_report*)b)->info.com_lines;
    return (aa < bb) - (aa > bb);
}

int report_files_comp(const void* a, const void* b)
{
    int aa = ((loc_lang_report*)a)->files;
    int bb = ((loc_lang_report*)b)->files;
    return (aa < bb) - (aa > bb);
}

void loc(const char* path, loc_list gitignoreFiles, loc_report* report);
void lang_report_add(loc_report* report, char* name, loc_info* info);

loc_language* get_lang(char* file);

loc_info parse_file(FILE* file, loc_language* lang);

int main(int argc, char** argv)
{    
    if(argc < 2 || ARG(1, "-h") || ARG(1, "--help"))
    {
        printf("Usage:\n loc <directory|file> [options]\n\n");
        printf("Options:\n");
        printf(" -h, --help                 Print this info\n");
        printf(" -a, --all                  Show details about every file\n");
        printf(" -c, --code                 Code only report\n");
        printf(" -t, --time                 Show time taken\n");
        printf(" -s, --sort <method>        Sort by (sorted by code by default)\n");
        printf("    methods: <total|code|comments|files>\n");         
        printf(" -l, --langs [langs]        Select only specified languages\n");
        printf("    langs: name of any supported language\n");
        printf("\n\n");
        return 0;
    }
        
    for(int i = 2; i < argc; i++)
    {
        if(ARG(i, "-a") || ARG(i, "--all"))
            options.all = 1;
        if(ARG(i, "-c") || ARG(i, "-code"))
            options.code = 1;
        if(ARG(i, "-t") || ARG(i, "--time"))
            options.time = 1;
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

    loc_list gitignoredFiles = {NULL, NULL};
    loc_list_add(&gitignoredFiles, ".\\.gitignore");

    loc_report report = {.length = 0, .total.language = "TOTAL"};

    if(options.all)
    {
        printf("%-50s | %-25s | %-10s | %-10s | %-10s\n", "File", "Language", "Total", "Code", "Comments");
        printf("---------------------------------------------------+---------------------------+------------+------------+------------\n");
    }

    loc(argv[1], gitignoredFiles, &report);

    
    if(!options.sort || (options.sort && strcmp(options.sort_method, "code") == 0))
    {
        qsort(report.data, report.length, sizeof(loc_lang_report), &report_code_comp);
    }
    else
    {
        if(strcmp(options.sort_method, "total") == 0)
        {
            qsort(report.data, report.length, sizeof(loc_lang_report), &report_total_comp);
        }
        else if(strcmp(options.sort_method, "comments") == 0)
        {
            qsort(report.data, report.length, sizeof(loc_lang_report), &report_comments_comp);
        }
        else if(strcmp(options.sort_method, "files") == 0)
        {
            qsort(report.data, report.length, sizeof(loc_lang_report), &report_files_comp);
        }
    }

    clock_t end = clock();

    if(!options.all)
    {   
        printf("--------------------------+------------+------------+------------+------------\n");
        printf("%-25s | %10s | %10s | %10s | %10s\n", "Language", "Total", "Code", "Comments", "Files");
        printf("--------------------------+------------+------------+------------+------------\n");
        for(int i = 0; i < report.length; i++)
        {
            PRINT_REPORT(report.data[i].language, &report.data[i].info, report.data[i].files);
        }
        printf("--------------------------+------------+------------+------------+------------\n");
        PRINT_REPORT(report.total.language, &report.total.info, report.total.files);
        printf("--------------------------+------------+------------+------------+------------\n");
        printf("\n");

    }

    if(options.time)
    {
        double time = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("\nTook: %lf, files/sec: %lf\n\n", time, (double)report.total.files / time);
    }

    return 0;
}

loc_language* get_lang(char* file)
{
    char aux[500]; //= calloc(strlen(file), sizeof(char));
    char* extension;

    strcpy(aux, file);
    char* tok = strtok(aux, ".");
    while(tok != NULL)
    {   
        extension = tok;
        tok = strtok(NULL, ".");
    }

    int l = 0, r = EXTENSIONS_SIZE - 1;

    while(l <= r)
    {
        int m = (l + r) / 2;
        int comp = strcmp(extension, extensions[m].name);
        if(comp == 0)
            return &languages[extensions[m].lang_id];
        else if(comp < 0)
            r = m - 1;
        else
            l = m + 1;
    }
    
    return NULL;
}

void loc(const char* path, loc_list gitignoreFiles, loc_report* report)
{
    // if the current directory contains a .gitignore file use it to skip files from parsing
    char gitpath[500];
    sprintf(gitpath, "%s\\.gitignore", path);

    FILE* fgit = fopen(gitpath, "r");
    if(fgit != NULL)
    {
        char ignored[500];
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

    char file[500];
    sprintf(file, "%s\\*", path);

    WIN32_FIND_DATA findData;
    HANDLE findHnd = NULL;

    // return if current path is invalid
    // if((findHnd = FindFirstFileEx(file, FindExInfoBasic, &findData, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH)) == INVALID_HANDLE_VALUE)
    if((findHnd = FindFirstFile(file, &findData)) == INVALID_HANDLE_VALUE)
    {
        return;
    }

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
            loc(file, gitignoreFiles, report);
        }
        else
        {   
            loc_language* lang = get_lang(file);
            if(lang != NULL)
            {

                FILE* f = fopen(file, "r");
                loc_info info = parse_file(f, lang);
                fclose(f);

                if(options.all)
                {
                    PRINT_FILE_REPORT(file + 2, lang->name, &info);
                }
                else
                {
                    lang_report_add(report, lang->name, &info);
                }

            }
        }

    } while(FindNextFile(findHnd, &findData));

    FindClose(findHnd);
}

loc_info parse_file(FILE* file, loc_language* lang)
{
    loc_info info = {0, 0, 0, 0};

    char c;
    int com_status = 0;

    int cc = 0, sc = 0;

    int sl = strlen(lang->com.sl);
    int mls = strlen(lang->com.ml_start);
    int mle = strlen(lang->com.ml_end);

    char* s2 = calloc(1000, sizeof(char));
    while(fgets(s2, 1000, file))
    {
        char* s = s2;
        while(*s == ' ')
            s++;

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

        info.total_lines++;
    }
    free(s2);

    info.code_lines = info.total_lines - info.com_lines - info.blank_lines;
    
    return info;
}

void lang_report_add(loc_report* report, char* language, loc_info* info)
{
    
    int index = report->length;
    for(int i = 0; i < report->length; i++)
    {
        if(strcmp(report->data[i].language, language) == 0)
        {
            index = i;
            break;
        }
    }

    if(index != report->length)
        report->data[index].files++;
    else
    {
        strcpy(report->data[report->length].language, language);
        report->data[index].files = 1;
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
    report->total.files++;
}