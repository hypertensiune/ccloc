<h1 align="center">CCLOC</h1>

<p>
    CCLOC is a tool for counting lines of code written in C. 
    It's inspired by other lines of code counting tools like 
    <a href="https://github.com/XAMPPRocky/tokei">tokei</a>,
    <a href="https://github.com/boyter/scc">scc</a> and
    <a href="https://github.com/AlDanial/cloc">cloc</a>.
    CCLOC has vast language support, can accurately count lines of code. ([see](#how-it-works) for more details about comment lines counting). 
    It's goal is to be the <b>fastest line counting tool on windows</b>.
</p>

```
> cloc -t
--------------------------+------------+------------+------------+------------
Language                  |      Total |       Code |   Comments |      Files
--------------------------+------------+------------+------------+------------
JSON                      |       4269 |       4269 |          0 |          6
C#                        |       2758 |       2224 |        180 |         52
XAML                      |       1185 |       1081 |         64 |         18
TSX                       |        744 |        635 |          1 |         13
XML                       |        523 |        472 |         29 |         24
TypeScript                |        624 |        454 |         40 |          9
Sass                      |        346 |        283 |          4 |          6
JavaScript                |        337 |        264 |         20 |          7
Kotlin                    |        226 |        172 |         13 |          9
Markdown                  |        125 |         89 |          0 |          3
Batch                     |         89 |         68 |          0 |          1
MSBuild                   |         49 |         42 |          0 |          1
Visual Studio Solution    |         25 |         25 |          0 |          1
Prolog                    |         21 |         18 |          0 |          1
SVG                       |         16 |         16 |          0 |          1
HTML                      |         19 |         15 |          0 |          1
--------------------------+------------+------------+------------+------------
TOTAL                     |      11356 |      10127 |        351 |        153
--------------------------+------------+------------+------------+------------
Took: 18.00 milliseconds
Parsed 153 files, files/s: 8500.00
Read 433244 bytes (0.43 megabytes), bytes/s: 24069111.11 (mb/s: 24.07)
```

## Usage
```
ccloc v1.0
https://github.com/hypertensiune/ccloc

Usage:
 loc <directory|file> [options]

Options:
 -h,  --help                 Print this info
 -a,  --all                  Show details about every file
 -t,  --time                 Show time taken
 -th, --threads <number>     Set the number of threads to be used (5 default)
 -s,  --sort <method>        Sort by (sorted by code by default)
      methods: <total|code|comments|files>
 -l,  --langs [langs]        Select only specified languages
      langs: name of any supported language
```

## How it works
ccloc works by recursively listing all files in the given directory, checking for each of them if it contains source code of a supported language and then parses that file to count the number of lines.

1. On each directory encountered parse ```.gitignore``` file (if it exists)
2. Recursively list all files using ```FindFirstFile``` and ```FindNextFile```. Add each file to a queue for later processing if it is not ignored.
3. Start removing files from the queue in order to process them. Get the file's extension in order to determine the language. (If the file has no extension the language is not determined and the file is skipped).
4. If the file contains source code of a supported language start processing it to count the number of lines.

    1. Get the number of bytes by seeking to the end, getting the position and seeking back at the front. (https://stackoverflow.com/a/238607)
    2. Start reading the file line by line. For each line remove the whitespaces from the begging of the line.
    3. If the first character after stripping is '\n' then it's a **blank line**, otherwise compare the first characters of the line with the characters marking a single line comment and a multi line comment.
    4. If the multi line comment characters are found change the FSM's state to count all following lines as comment lines until the characters marking the end of a multi line comment are found.
    5. Calculate the **code lines** = **total lines - comment lines - blank lines**
    6. Store the results

### Notes
Because of the method I chose for counting the lines there are some cases in which comment lines are not counted like other tools would. ccloc counts lines as comment lines only those lines that are fully occupied by comments. A line that contains both code and comment is only counted as a code line.

#### This is counted as 3 comment lines
```
/*
    comment
*/
```

#### This is counted only as code line
```
int a = 5; // comment
```

#### This would be wrongly counted as 2 code lines and 0 comment lines.
```
int a = 5; /*
    comment
*/ 
```

## Performance

I tested and compared ccloc to tokei, scc and cloc on one of my projects and some bigger ones. In all tests ccloc ran faster on average, though in some cases it was pretty close to tokei. 

Note: All tests were performed with <a href="https://github.com/sharkdp/hyperfine">hyperfine</a> with ```--warmup 3``` for a warm cache and 10 runs. All tests were performed on a Win11 23H2 machine with a Ryzen 9 7940HS with 16GB DDR5 4800Mhz. Timings may very on different machines.

### <a href="https://github.com/hypertensiune/Mousedroid">Mousedroid</a> 80 files, ~4.2k lines

| Command | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 16.6 ± 2.2 | 14.9 | 38.0 | 1.00 |
| `tokei` | 25.8 ± 6.1 | 21.3 | 71.5 | 1.55 ± 0.42 |
| `scc` | 49.3 ± 2.2 | 46.5 | 61.7 | 2.96 ± 0.42 |
| `cloc` | 1545.8 ± 97.5 | 1464.6 | 1762.0 | 92.85 ± 13.83 |

### <a href="https://github.com/redis/redis">Redis</a> ~1.5k total files, ~400k lines
| Tool | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 35.1 ± 12.5 | 29.7 | 136.4 | 1.00 |
| `scc` | 67.1 ± 1.1 | 65.3 | 71.6 | 1.91 ± 0.68 |
| `tokei` | 89.0 ± 46.4 | 53.6 | 217.3 | 2.54 ± 1.60 |
| `cloc` | 2312.9 ± 36.4 | 2274.1 | 2392.3 | 65.86 ± 23.44 |

### <a href="https://github.com/facebook/react">React</a> ~6k total files, ~700k lines

| Tool | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 95.0 ± 3.1 | 90.2 | 103.6 | 1.00 |
| `tokei` | 117.5 ± 6.8 | 107.6 | 136.1 | 1.24 ± 0.08 |
| `scc` | 131.4 ± 1.8 | 128.6 | 134.6 | 1.38 ± 0.05 |
| `cloc` | 6560.9 ± 131.6 | 6411.9 | 6754.7 | 69.03 ± 2.63 |

### <a href="https://github.com/DragonFlyBSD/DragonFlyBSD">DragonFlyBSD</a> ~30k total files, ~14m lines
| Tool | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 528.2 ± 18.4 | 496.5 | 558.7 | 1.00 |
| `scc` | 646.2 ± 64.3 | 591.1 | 775.8 | 1.22 ± 0.13 |
| `tokei` | 760.7 ± 68.5 | 691.1 | 868.7 | 1.44 ± 0.14 |
| `cloc` | 98341.0 ± 13755.0 | 67055.4 | 113494.0 | 186.17 ± 26.84 |

### <a href="https://github.com/torvalds/linux">Linux Kernel</a> ~85k total files, ~14m lines

| Tool | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 1.716 ± 0.025 | 1.685 | 1.749 | 1.00 |
| `tokei` | 1.769 ± 0.038 | 1.732 | 1.862 | 1.03 ± 0.03 |
| `scc` | 2.823 ± 0.014 | 2.807 | 2.850 | 1.64 ± 0.03 |

### 15x <a href="https://github.com/torvalds/linux">Linux Kernel</a> ~1.2m total files, ~210m lines

| Tool | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 1.716 ± 0.025 | 1.685 | 1.749 | 1.00 |
| `tokei` | 1.769 ± 0.038 | 1.732 | 1.862 | 1.03 ± 0.03 |
| `scc` | 2.823 ± 0.014 | 2.807 | 2.850 | 1.64 ± 0.03 |

## Supported languages
ccloc supports the same languages (~280) as tokei as it has a nice database of languages, their extensions and comment styles so I used that. scc and other tools also use tokei's database as a starting point. 
```

```
