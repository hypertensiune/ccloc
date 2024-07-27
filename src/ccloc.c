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
 
#include "ccloc.h"
 
pthread_mutex_t mutex;
 
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
 
int get_lang(const char* file, loc_options* options)
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
            if(options->langs_n > 0)
            {
                int found = 0;
                for(int i = 0; i < options->langs_n; i++)
                {
                    if(strcmp(languages[lang_id].name, options->langs_array[i]) == 0)
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
 
    // https://stackoverflow.com/a/238607
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    info.bytes = (long long)size;

    fseek(file, 0, SEEK_SET);
 
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

    // Testing another parsing method.

    // char* s2 = calloc(size + 1, sizeof(char));

    // fread(s2, sizeof(char), size, file);
    // s2[size] = '\0';

    // char* save;
    // char* p = s2;
    // char* tok = strtok_r(s2, "\n", &save);
    // while(tok != NULL)
    // {   
    //     info.total_lines++;

    //     char* s = tok;
    //     while(isspace(s[0]) && s[0] != '\n')
    //         s++;
 
    //     if(tok != s2 && *(tok - 1) == '\n')
    //     {
    //         info.total_lines++;
    //         info.blank_lines++;
    //     }
    //     else if(s[0] == '\n' && com_status == 0)
    //     {
    //         info.blank_lines++;
    //     }
    //     else
    //     {
    //         if(sl > 0 && memcmp(s, lang->com.sl, sl) == 0)
    //         {
    //             info.com_lines++;
    //         }
    
    //         if(mls > 0)
    //         {   
    //             if(com_status == 0)
    //             {
    //                 if(memcmp(s, lang->com.ml_start, mls) == 0)
    //                 {
    //                     com_status = 1;
    //                 }
    //             }
    //             else 
    //             {
    //                 if(memcmp(s, lang->com.ml_end, mle) == 0)
    //                 {
    //                     info.com_lines++;
    //                     com_status = 0;
    //                 }
    //             }
    //         }
    
    //         if(com_status == 1)
    //             info.com_lines++;
    //     }

    //     tok = strtok_r(NULL, "\n", &save);
    // }
 
    // free(s2);

    info.code_lines = info.total_lines - info.com_lines - info.blank_lines;
 
    return info;
}
 
void loc_report_add(loc_report* report, loc_info* info)
{ 
    pthread_mutex_lock(&mutex);
    
    // check if the current language is already added in the final report
    int index = report->length;
    for(int i = 0; i < report->length; i++)
    {
        if(report->data[i].language_id == info->language_id)
        {
            index = i;
            break;
        }
    }
 
    if(index != report->length)
        report->data[index].files++;
    else
    {
        report->data[index].language_id = info->language_id;
        report->data[index].files = 1;
        report->length++;
    }
 
    report->data[index].blank_lines += info->blank_lines;
    report->data[index].code_lines += info->code_lines;
    report->data[index].com_lines += info->com_lines;
    report->data[index].total_lines += info->total_lines;
 
    report->total.blank_lines += info->blank_lines;
    report->total.code_lines += info->code_lines;
    report->total.com_lines += info->com_lines;
    report->total.total_lines += info->total_lines;
    report->total.files++;
    report->total.bytes += info->bytes;
 
    pthread_mutex_unlock(&mutex);
}

void loc_file_report_add(loc_file_report* report, const char* file, loc_info* info)
{
    pthread_mutex_lock(&mutex);

    printf("%s adding file\n", file);

    // if the report is unallocated
    if(report->capacity == 0 && report->length == 0 && report->data == NULL)
    {
        report->capacity = 1000;
        // report->data contains a char array of length MAX_FILE_LEN and loc_info
        report->data = calloc(report->capacity = 1000, MAX_FILE_LEN + sizeof(loc_info));
    }

    // grow the array if there is no more space
    if(report->length >= report->capacity)
    {
        report->capacity *= 2;
        report->data = realloc(report->data, report->capacity * (MAX_FILE_LEN + sizeof(loc_info)));
    }

    strcpy(report->data[report->length].file, file);
    report->data[report->length].data = *info;

    report->length++;

    report->total.blank_lines += info->blank_lines;
    report->total.code_lines += info->code_lines;
    report->total.com_lines += info->com_lines;
    report->total.total_lines += info->total_lines;
    report->total.files++;
    report->total.bytes += info->bytes;

    pthread_mutex_unlock(&mutex);
}
 
#ifdef WIN32
    int find_files(const char* path, loc_list gitignoreFiles, queue* fileq)
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
            return CCLOC_FILE_NOT_FOUND;
 
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
                find_files(file, gitignoreFiles, fileq);
            }
            else
            {     
                enqueue(fileq, file);
            }
 
        } while(FindNextFile(findHnd, &findData));
 
        FindClose(findHnd);
 
        return CCLOC_SUCCESS;
    }
#endif
 
#ifdef __unix__
    int find_files(const char* path, loc_list gitignoreFiles, queue* fileq)
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
            return CCLOC_FILE_NOT_FOUND;
 
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
                find_files(file, gitignoreFiles, fileq);
        }
 
        closedir(d);
 
        return CCLOC_SUCCESS;
    }
#endif
 
int report_code_comp(const void* a, const void* b)
{   
    int aa = ((loc_info*)a)->code_lines;
    int bb = ((loc_info*)b)->code_lines;
    return (aa < bb) - (aa > bb);
}
 
int report_total_comp(const void* a, const void* b)
{
    int aa = ((loc_info*)a)->total_lines;
    int bb = ((loc_info*)b)->total_lines;
    return (aa < bb) - (aa > bb);
}
 
int report_comments_comp(const void* a, const void* b)
{
    int aa = ((loc_info*)a)->com_lines;
    int bb = ((loc_info*)b)->com_lines;
    return (aa < bb) - (aa > bb);
}
 
int report_files_comp(const void* a, const void* b)
{
    int aa = ((loc_info*)a)->files;
    int bb = ((loc_info*)b)->files;
    return (aa < bb) - (aa > bb);
}
 
void* thread_worker(void* arg)
{
    thread_arg* targ = (thread_arg*)arg;
    char* s = NULL;
    while((s = dequeue(targ->q)) != NULL)
    {

        int lang_id = get_lang(s, targ->options);
        if(lang_id != -1)
        {
            FILE* f = fopen(s, "r");
            loc_info info = parse_file(f, &languages[lang_id]);
            info.language_id = lang_id;
            fclose(f);

            if(targ->options->all)
                loc_file_report_add((loc_file_report*)targ->report, s, &info);
            else
                loc_report_add((loc_report*)targ->report, &info);
        }
        free(s);
    }
}

int ccloc(const char* path, loc_options* options, void* report)
{
    int nthreads = 20;
    pthread_t threads[100];

    loc_list gitignoredFiles = {NULL, NULL};
    loc_list_add(&gitignoredFiles, ".\\.gitignore");
 
    queue fileq;
    fileq.head = fileq.tail = NULL;

    clock_t begin = clock();
 
    // if the path given is a file open and process it right away
    if(strcmp(path, ".") != 0 && strcmp(path, "..") != 0)
    {
        #ifdef WIN32
            FILE* f = fopen(path, "r");
        #else
            // avoid opening directories on unix operating systems
            // https://stackoverflow.com/questions/42876210/c-fopen-opening-directories
            FILE* f = fopen(path, "r+");
        #endif
        if(f != NULL)
        {
            int lang_id = get_lang(path, options);
            if(lang_id == -1)
                return 0;
            
            loc_info info = parse_file(f, &languages[lang_id]);
            fclose(f);

            loc_report_add((loc_report*)report, &info);

            return 0;
        }
    }

    int r = find_files(path, gitignoredFiles, &fileq);
    if(r == CCLOC_FILE_NOT_FOUND)
        return CCLOC_FILE_NOT_FOUND;

    thread_arg targ = {&fileq, report, options};
 
    pthread_mutex_init(&mutex, NULL);
    for(int i = 0; i < nthreads; i++)
        pthread_create(&threads[i], NULL, thread_worker, &targ);
 
    for(int i = 0; i < nthreads; i++)
        pthread_join(threads[i], NULL);


    if(!options->all)
    {
        loc_report* lreport = (loc_report*)report;

        // if there is no sort option default to sort by number of code lines
        if(!options->sort || (options->sort && strcmp(options->sort_method, "code") == 0))
        {
            qsort(lreport->data, lreport->length, sizeof(loc_info), &report_code_comp);
        }
        else
        {
            if(strcmp(options->sort_method, "total") == 0)
            {
                qsort(lreport->data, lreport->length, sizeof(loc_info), &report_total_comp);
            }
            else if(strcmp(options->sort_method, "comments") == 0)
            {
                qsort(lreport->data, lreport->length, sizeof(loc_info), &report_comments_comp);
            }
            else if(strcmp(options->sort_method, "files") == 0)
            {
                qsort(lreport->data, lreport->length, sizeof(loc_info), &report_files_comp);
            }
        }
    }
 
    clock_t end = clock();

    ((loc_report*)report)->time = (double)(end - begin) / CLOCKS_PER_SEC;

    return 0;
}