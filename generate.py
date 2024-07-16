"""
    Script used to generate the lang.h header containing the 
    language database.

    It uses tokei's language.json and modifies it to be used in c. 
"""

import json

counter = 0

defines = []
extensions = []
langs = []

exts = {}
with open('languages.json', encoding='utf-8') as f:
    languages = json.load(f)
    for lang in languages['languages'].items():
        
        name = lang[0]
        sl = ""
        mls = ""
        mle = ""
        
        if 'name' in lang[1]:
            name = lang[1]['name']   

        if 'line_comment' in lang[1]:
            sl = lang[1]['line_comment'][0]

        if 'multi_line_comments' in lang[1]:
            mls = lang[1]['multi_line_comments'][0][0]

        if 'multi_line_comments' in lang[1]:
            mle = lang[1]['multi_line_comments'][0][1]

        defines.append(f'#define {lang[0]} {counter}\n')
        
        langs.append(f'\t{{\n\t\t"{name}",\n\t\t{{"{sl}", "{mls}", "{mle}"}}\n\t}},\n')

        if 'extensions' in lang[1]:
            for ext in lang[1]['extensions']:
                exts[ext] = lang[0]

        counter += 1

exts = dict(sorted(exts.items()))

with open("langs.h", "w", encoding='utf-8') as f:
    for d in defines:
        f.write(d)

    f.write(f'#define EXTENSIONS_SIZE {len(exts)}\n')
    f.write(f'#define LANGUAGES_SIZE {len(langs)}\n\n')

    f.write('''typedef struct
{
    char *name;
    int lang_id;
} loc_extension;

typedef struct
{
    char *name;
    struct
    {
        char sl[20];
        char ml_start[20];
        char ml_end[20];
    } com;
} loc_language;\n\n''')

    f.write("loc_extension extensions[EXTENSIONS_SIZE] =\n{\n")
    for k, v in exts.items():
        f.write(f'\t{{"{k}", {v}}},\n')
    f.write("};\n\n")

    f.write("loc_language languages[LANGUAGES_SIZE] =\n{\n")
    for l in langs:
        f.write(l)
    f.write("};\n\n")