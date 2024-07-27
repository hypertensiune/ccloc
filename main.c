#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CCLOC_ALL
#include "include/ccloc.h"

#define ARG(i, s) (strcmp(argv[i], s) == 0)

static inline void PRINT_REPORT_HEADER()
{
    printf("--------------------------+------------+------------+------------+------------\n");
    printf("%-25s | %10s | %10s | %10s | %10s\n", "Language", "Total", "Code", "Comments", "Files");
    printf("--------------------------+------------+------------+------------+------------\n");
}
 
static inline void PRINT_REPORT(loc_info* report)
{
    printf("%-25s | %10d | %10d | %10d | %10d\n", languages[report->language_id].name, report->total_lines, report->code_lines, report->com_lines, report->files);
}
 
static inline void PRINT_REPORT_TOTAL(loc_info* total)
{
    printf("--------------------------+------------+------------+------------+------------\n");
    PRINT_REPORT(total);
    printf("--------------------------+------------+------------+------------+------------\n");
}
 
static inline void PRINT_FILE_REPORT_HEADER()
{
    printf("---------------------------------------------------+---------------------------+------------+------------+------------\n");
    printf("%-50s | %-25s | %10s | %10s | %10s\n", "File", "Language", "Total", "Code", "Comments");
    printf("---------------------------------------------------+---------------------------+------------+------------+------------\n");
}

static inline void PRINT_FILE_REPORT(char* file,  loc_info *li)
{
    int len = __max(strlen(file), 50);
    file = file + len - 50;
    file[0] = '~';
    printf("%-50s | %-25s | %10d | %10d | %10d\n", file, languages[li->language_id].name, li->total_lines, li->code_lines, li->com_lines);
}
 
static inline void PRINT_FILE_REPORT_TOTAL(loc_info *li)
{
    printf("---------------------------------------------------+---------------------------+------------+------------+------------\n");
    printf("TOTAL %38d files | %-25s | %10d | %10d | %10d\n", li->files, "", li->total_lines, li->code_lines, li->com_lines);
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

int main(int argc, char** argv)
{   
    loc_options options = {.all = 0, .time = 0, .sort = 0, .langs = 0, .threads = 20};
    
    loc_report lreport = {.length = 0, .total.language_id = TOTAL};
    loc_file_report freport = {0, 0, 0, NULL};

    void* report = &lreport;

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
            options.threads = 1;
            report = &freport;
        }
        if(ARG(i, "-t") || ARG(i, "--time"))
            options.time = 1;
        if(ARG(i, "-th") || ARG(i, "--threads"))
        {
            i++;
            options.threads = atoi(argv[i]);
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

    int result = ccloc(argv[1], &options, report);
    if(result == CCLOC_FILE_NOT_FOUND)
    {
        printf("Error: Directory / file not found");
        return 0;
    }

    if(!options.all)
    {   
        PRINT_REPORT_HEADER();
        for(int i = 0; i < lreport.length; i++)
        {
            PRINT_REPORT(&lreport.data[i]);
        }
        PRINT_REPORT_TOTAL(&lreport.total);

        if(options.time)
        {
            PRINT_TIME_STATS(lreport.time, lreport.total.files, lreport.total.bytes);
        }
    }
    else
    {   
        PRINT_FILE_REPORT_HEADER();
        for(int i = 0; i < freport.length; i++)
        {
            if(i > 0 && freport.data[i].info.language_id != freport.data[i - 1].info.language_id)
                    printf("---------------------------------------------------+---------------------------+------------+------------+------------\n");
            PRINT_FILE_REPORT(freport.data[i].file, &freport.data[i].info);
        }
        PRINT_FILE_REPORT_TOTAL(&freport.total);

        if(options.time)
        {
            PRINT_TIME_STATS(freport.time, freport.total.files, freport.total.bytes);
        }
    }
    
    return 0;
}