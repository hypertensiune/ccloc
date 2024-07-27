<h1 align="center">CCLOC</h1>

## Table of Contents
1. [Usage](#usage)
2. [How it works](#how-it-works)
3. [Performance](#performance)
    1. [Mousedroid - 80 files, 42k lines](#mousedroid-80-files-42k-lines)
    2. [Redis - 1.5k files, 400k lines](#redis-15k-total-files-400k-lines)
    3. [React - 6k files, 700k lines](#react-6k-total-files-700k-lines)
    4. [DragonFlyBSD - 30k files, 14m lines](#dragonflybsd-30k-total-files-14m-lines)
    5. [Linux Kernel - 60k files, 35m lines](#linux-kernel-60k-total-files-35m-lines)
    6. [10x Linux Kernel](#10-copies-of-linux-kernel-600k-total-files-350m-lines)
    7. [Multi-threading](#multi-threading)
4. [Supported Languages](#supported-languages)

<p>
    CCLOC is a tool for counting lines of code written in C. 
    It's inspired by other lines of code counting tools like 
    <a href="https://github.com/XAMPPRocky/tokei">tokei</a>,
    <a href="https://github.com/boyter/scc">scc</a> and
    <a href="https://github.com/AlDanial/cloc">cloc</a>.
    CCLOC has vast language support, can accurately count lines of code. ([see](#how-it-works) for more details about comment lines counting). 
    It's goal is to be the <b>fastest line counting tool</b> on windows & linux.
</p>
<p>
    CCLOC is also a library. For more details and how to use see <a href="https://github.com/hypertensiune/ccloc/blob/master/LIBRARY.md">this</a>.
</p>

### Example

```
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

### Installation

You can build ccloc by yourself or you can download the availabe prebuilt binaries for **windows** and **linux** in the releases section. 

### Options

```
ccloc v1.0.2
https://github.com/hypertensiune/ccloc

Usage:
 ccloc <directory|file> [options]

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

#### Show details about every processed file

```
> ccloc . -a -t
---------------------------------------------------+---------------------------+------------+------------+------------
File                                               | Language                  |      Total |       Code |   Comments
---------------------------------------------------+---------------------------+------------+------------+------------
~\src\langs.c                                      | C                         |       1621 |       1594 |         23
~\src\ccloc.c                                      | C                         |        671 |        443 |        114
~\main.c                                           | C                         |        167 |        145 |          0
---------------------------------------------------+---------------------------+------------+------------+------------
~\include\langs.h                                  | C Header                  |        335 |        306 |         23
~\src\ccloc.h                                      | C Header                  |        111 |         65 |         26
~\include\ccloc.h                                  | C Header                  |        107 |         62 |         31
---------------------------------------------------+---------------------------+------------+------------+------------
~\graphs\react.json                                | JSON                      |       2078 |       2078 |          0
~\languages.json                                   | JSON                      |       1800 |       1800 |          0
~\linux.json                                       | JSON                      |       1024 |       1024 |          0
~\graphs\linux.json                                | JSON                      |       1024 |       1024 |          0
---------------------------------------------------+---------------------------+------------+------------+------------
~\README.md                                        | Markdown                  |        604 |        545 |          0
~\LIBRARY.md                                       | Markdown                  |         33 |         26 |          0
---------------------------------------------------+---------------------------+------------+------------+------------
~\generate.py                                      | Python                    |         82 |         56 |          6
~\plot.py                                          | Python                    |         33 |         21 |          0
---------------------------------------------------+---------------------------+------------+------------+------------
~\res.txt                                          | Plain Text                |       5746 |       5746 |          0
---------------------------------------------------+---------------------------+------------+------------+------------
TOTAL                                     15 files |                           |      15436 |      14935 |        223
---------------------------------------------------+---------------------------+------------+------------+------------
Took: 8.00 milliseconds
Parsed 15 files, files/s: 1875.00
Read 1613215 bytes (1.61 megabytes), bytes/s: 201651875.00 (mb/s: 201.65)
```

#### Process only files that contain C Header or Python source code

```
> ccloc . -a -t -l "C Header" Python
---------------------------------------------------+---------------------------+------------+------------+------------
File                                               | Language                  |      Total |       Code |   Comments
---------------------------------------------------+---------------------------+------------+------------+------------
~\include\langs.h                                  | C Header                  |        335 |        306 |         23
~\src\ccloc.h                                      | C Header                  |        111 |         65 |         26
~\include\ccloc.h                                  | C Header                  |        107 |         62 |         31
---------------------------------------------------+---------------------------+------------+------------+------------
~\generate.py                                      | Python                    |         82 |         56 |          6
~\plot.py                                          | Python                    |         33 |         21 |          0
---------------------------------------------------+---------------------------+------------+------------+------------
TOTAL                                      5 files |                           |        668 |        510 |         86
---------------------------------------------------+---------------------------+------------+------------+------------
Took: 10.00 milliseconds
Parsed 5 files, files/s: 500.00
Read 17048 bytes (0.02 megabytes), bytes/s: 1704800.00 (mb/s: 1.70)
```

####  Sort by lines of comments
```
> ccloc . -t -s comments
--------------------------+------------+------------+------------+------------
Language                  |      Total |       Code |   Comments |      Files
--------------------------+------------+------------+------------+------------
C                         |        689 |        541 |         37 |          1
C Header                  |       1927 |       1896 |         23 |          1
Python                    |         82 |         56 |          6 |          1
JSON                      |       1800 |       1800 |          0 |          1
Markdown                  |        514 |        463 |          0 |          1
--------------------------+------------+------------+------------+------------
TOTAL                     |       5012 |       4756 |         66 |          5
--------------------------+------------+------------+------------+------------
Took: 1.00 milliseconds
Parsed 5 files, files/s: 5000.00
Read 139917 bytes (0.14 megabytes), bytes/s: 139917000.00 (mb/s: 139.92)
```


## How it works
ccloc works by recursively listing all files in the given directory, checking for each of them if it contains source code of a supported language and then parses that file to count the number of lines.

It also ignores files base on ```.gitignore``` files. ***It doesn't work** with special patterns like ```/path/*.c``` or ```/path**/*.c```.

1. On each directory encountered parse ```.gitignore``` file (if it exists)
2. Recursively list all files using ```FindFirstFile``` and ```FindNextFile``` on Windows and ```opendir``` and ```readdir``` on Linux. Add each file to a queue for later processing if it is not ignored.
3. Start removing files from the queue in order to process them. Get the file's extension in order to determine the language. (If the file has no extension the language is not determined and the file is skipped).
4. If the file contains source code of a supported language start processing it to count the number of lines.

    1. Get the number of bytes by seeking to the end, getting the position and seeking back at the front. (https://stackoverflow.com/a/238607)
    2. Start reading the file line by line. For each line remove the whitespaces from the begging of the line.
    3. If the first character after stripping is '\n' then it's a **blank line**, otherwise compare the first characters of the line with the characters marking a single line comment and a multi line comment.
    4. If the multi line comment characters are found change the FSM's state to count all following lines as comment lines until the characters marking the end of a multi line comment are found.
    5. Calculate the **code lines** = **total lines - comment lines - blank lines**
    6. Store the results

### Notes
Because of the method I chose for counting the lines there are some cases in which comment lines are not counted like other tools would. ccloc counts lines as comment lines only those lines that are fully occupied by comments. A line that contains both code and comment is only counted as a code line. I made this decision because it makes the program simpler and cases like this are not that common.

Blank lines inside comments are counted as comment lines.

#### This would be wrongly counted as 2 code lines and 0 comment lines.
```
int a = 5; /*
    comment
*/ 
```

#### This is counted only as a code line
```
int a = 5; // comment
```

#### This is counted as 4 comment lines
```
/*
    some comment

*/
```

## Performance

I tested and compared ccloc to tokei, scc and cloc on one of my projects and some bigger ones. In all tests ccloc ran faster on average, though in some cases it was pretty close to tokei. 

ccloc's performance is given by multithreading. By default it creates 20 threads to process the files in the queue.

Note: All tests were performed with <a href="https://github.com/sharkdp/hyperfine">hyperfine</a> with ```--warmup 3``` for a warm cache and 10 runs. Tests were performed on Windows 11 23H2 and Ubuntu 22.04 LTS virtual machine (Ryzen 9 7940HS with 16GB DDR5 4800Mhz) Timings may very on different machines.

### <a href="https://github.com/hypertensiune/Mousedroid">Mousedroid</a> 80 files, ~4.2k lines

#### Windows
| Tool | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 16.6 ± 2.2 | 14.9 | 38.0 | 1.00 |
| `tokei` | 25.8 ± 6.1 | 21.3 | 71.5 | 1.55 ± 0.42 |
| `scc` | 49.3 ± 2.2 | 46.5 | 61.7 | 2.96 ± 0.42 |
| `cloc` | 1545.8 ± 97.5 | 1464.6 | 1762.0 | 92.85 ± 13.83 |

#### Linux
| Tool | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 3.3 ± 0.3 | 2.6 | 4.6 | 1.00 |
| `tokei` | 5.1 ± 0.6 | 4.2 | 8.0 | 1.54 ± 0.22 |
| `scc` | 7.7 ± 0.6 | 6.9 | 11.0 | 2.33 ± 0.26 |
| `cloc` | 94.9 ± 5.8 | 89.6 | 113.6 | 28.65 ± 2.94 |

### <a href="https://github.com/redis/redis">Redis</a> ~1.5k total files, ~400k lines

#### Windows
| Tool | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 35.1 ± 12.5 | 29.7 | 136.4 | 1.00 |
| `scc` | 67.1 ± 1.1 | 65.3 | 71.6 | 1.91 ± 0.68 |
| `tokei` | 89.0 ± 46.4 | 53.6 | 217.3 | 2.54 ± 1.60 |
| `cloc` | 2312.9 ± 36.4 | 2274.1 | 2392.3 | 65.86 ± 23.44 |

#### Linux
| Tool | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 14.3 ± 0.5 | 13.4 | 15.7 | 1.00 |
| `tokei` | 22.2 ± 2.5 | 20.3 | 37.7 | 1.55 ± 0.18 |
| `scc` | 26.1 ± 2.2 | 22.9 | 35.8 | 1.82 ± 0.16 |
| `cloc` | 806.8 ± 14.4 | 791.2 | 839.2 | 56.23 ± 2.04 |

### <a href="https://github.com/facebook/react">React</a> ~6k total files, ~700k lines

#### Windows
| Tool | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 95.0 ± 3.1 | 90.2 | 103.6 | 1.00 |
| `tokei` | 117.5 ± 6.8 | 107.6 | 136.1 | 1.24 ± 0.08 |
| `scc` | 131.4 ± 1.8 | 128.6 | 134.6 | 1.38 ± 0.05 |
| `cloc` | 6560.9 ± 131.6 | 6411.9 | 6754.7 | 69.03 ± 2.63 |

#### Linux
| Tool | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 40.9 ± 0.6 | 39.8 | 43.2 | 1.00 |
| `tokei`  | 50.4 ± 3.8 | 45.8 | 67.6 | 1.23 ± 0.09 |
| `scc` | 79.3 ± 1.5 | 75.7 | 83.2 | 1.94 ± 0.05 |
| `cloc` | 2000.6 ± 58.4 | 1930.1 | 2080.2 | 48.93 ± 1.61 |   

### <a href="https://github.com/DragonFlyBSD/DragonFlyBSD">DragonFlyBSD</a> ~30k total files, ~14m lines

#### Windows
| Tool | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 528.2 ± 18.4 | 496.5 | 558.7 | 1.00 |
| `scc` | 646.2 ± 64.3 | 591.1 | 775.8 | 1.22 ± 0.13 |
| `tokei` | 760.7 ± 68.5 | 691.1 | 868.7 | 1.44 ± 0.14 |
| `cloc` | 98341.0 ± 13755.0 | 67055.4 | 113494.0 | 186.17 ± 26.84 |

#### Linux
| Tool | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 229.0 ± 4.0 | 223.5 | 235.1 | 1.00 |
| `scc` | 426.5 ± 16.6 | 391.3 | 450.1 | 1.86 ± 0.08 |
| `tokei` | 479.2 ± 10.8 | 460.6 | 493.1 | 2.09 ± 0.06 |
| `cloc` | 28219.2 ± 417.4 | 27713.8 | 28877.3 | 123.22 ± 2.82 |

### <a href="https://github.com/torvalds/linux">Linux Kernel</a> ~60k total files, ~35m lines

Using only 1 thread is very slow in comparison with the rest. It actually is slower than not using threading at all and processing the file right when it was discovered instead of adding it to a queue for later processing.

#### Windows
| Tool | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 1.648 ± 0.022 | 1.621 | 1.686 | 1.00 |
| `tokei` | 1.694 ± 0.026 | 1.656 | 1.739 | 1.03 ± 0.02 |
| `scc` | 2.751 ± 0.015 | 2.726 | 2.771 | 1.67 ± 0.02 |
| `ccloc -th 1` | 6.438 ± 0.020 | 6.413 | 6.481 | 3.91 ± 0.05 |

#### Linux
| Tool | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc` | 782.2 ± 11.3 | 772.1 | 809.3 | 1.00 |
| `tokei` | 1017.0 ± 43.5 | 976.1 | 1116.7 | 1.30 ± 0.06 |
| `scc` | 1325.0 ± 57.8 | 1250.2 | 1436.8 | 1.69 ± 0.08 |
| `ccloc -th 1` | 2239.0 ± 30.7 | 2216.9 | 2312.1 | 2.86 ± 0.06 |

### 10 copies of <a href="https://github.com/torvalds/linux">Linux Kernel</a> ~600k total files, ~350m lines

In this case, on windows, tokei is faster than ccloc. Interestingly increasing the number of threads doesn't make it any faster, on the contrary it slows it down a bit. On the other hand, on linux, ccloc is still the fastest one and here increasing the number of threads actually increases performance (not by much though even if the number of threads is doubled).
.
#### Windows
| Tool | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `tokei` | 88.630 ± 6.231 | 82.825 | 100.736 | 1.00 |
| `ccloc` | 95.670 ± 4.058 | 89.658 | 105.416 | 1.08 ± 0.09 |
| `ccloc -th 50` | 96.204 s ±  5.449 s | 89.259 | 108.151 | 1.09 ± 0.1 |
| `scc` | 108.624 ± 7.338 | 95.996 | 120.292 | 1.23 ± 0.12 |

#### Linux
| Tool | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `ccloc-th 50` | 24.768 ± 0.534 | 23.254 | 25.016 | 1.00 |
| `ccloc` | 26.046 ± 2.653 | 19.468 | 29.372 | 1.05 ± 0.11 |
| `scc` | 32.560 ± 5.658 | 17.389 | 37.592 | 1.31 ± 0.23 |
| `tokei` | 35.302 ± 0.562 | 34.907 | 36.805 | 1.43 ± 0.04 |

### Conclusion

**On windows**, ccloc is the fastest one on average but as the code base increases the time difference between it and tokei is getting smaller and smaller, tokei becoming faster on very large code bases, as shown in the last test with 10 copies of the Linux Kernel.

**On linux**, ccloc remains the fastest one in all tests.

### Multi-threading

You can see here how increasing the number of threads actually impacts performance on each platform. Single threaded performance is quite low. I found 20 threads to be the sweet spot, of course in some cases there might be some performance gain by using more than 20 threads but they are not significant. In some cases as seen above, on the contrary, using more threads can slow down the program (this applies on windows, on linux it doesn't seem to slow down).

<p align="center">
    <img src=graphs\windows.png>
    <img src=graphs\linux.png>
</p>

## Supported languages
ccloc supports the same languages (~280) as tokei as it has a nice database of languages, their extensions and comment styles so I used that. scc and other tools also use tokei's database as a starting point. 
https://github.com/XAMPPRocky/tokei/blob/master/languages.json

```
ABAP                                     (abap)      
ABNF                                     (abnf)      
ActionScript                             (as)        
Ada                                      (ada, adb, ads, pad)
Agda                                     (agda)      
Alex                                     (x)         
Alloy                                    (als)       
Arduino C++                              (ino)       
AsciiDoc                                 (adoc, asciidoc)
ASN.1                                    (asn1)      
ASP                                      (asa, asp)  
ASP.NET                                  (asax, ascx, asmx, aspx, master, sitemap, webinfo)
Assembly                                 (asm)       
GNU Style Assembly                       (s)         
Astro                                    (astro)     
ATS                                      (dats, hats, sats, atxt)
Autoconf                                 (in)        
Autoit                                   (au3)       
AutoHotKey                               (ahk)       
Automake                                 (am)        
AWK                                      (awk)       
BASH                                     (bash)      
Batch                                    (bat, btm, cmd)
Bazel                                    (bzl, bazel)
Bean                                     (bean, beancount)
Bitbake                                  (bb, bbclass, bbappend, inc, conf)
BrightScript                             (brs)       
C                                        (c, ec, pgc)
Cabal                                    (cabal)     
Cassius                                  (cassius)   
Ceylon                                   (ceylon)    
Chapel                                   (chpl)      
C Header                                 (h)         
Circom                                   (circom)    
Clojure                                  (clj)       
ClojureC                                 (cljc)      
ClojureScript                            (cljs)      
CMake                                    (cmake)     
COBOL                                    (cob, cbl, ccp, cobol, cpy)
CodeQL                                   (ql, qll)   
CoffeeScript                             (coffee, cjsx)
Cogent                                   (cogent)    
ColdFusion                               (cfm)       
ColdFusion CFScript                      (cfc)       
Coq                                      (v)         
C++                                      (cc, cpp, cxx, c++, pcc, tpp)
C++ Header                               (hh, hpp, hxx, inl, ipp)
Crystal                                  (cr)        
C#                                       (cs, csx)   
C Shell                                  (csh)       
CSS                                      (css)       
CUDA                                     (cu)        
Cython                                   (pyx, pxd, pxi)
D                                        (d)         
DAML                                     (daml)      
Dart                                     (dart)      
Device Tree                              (dts, dtsi) 
Dhall                                    (dhall)     
Dockerfile                               (dockerfile, dockerignore)
.NET Resource                            (resx)      
Dream Maker                              (dm, dme)   
Dust.js                                  (dust)      
Ebuild                                   (ebuild, eclass)
EdgeQL                                   (edgeql)    
EdgeDB Schema Definition                 (esdl)      
Edn                                      (edn)       
Emacs Lisp                               (el)        
Elixir                                   (ex, exs)   
Elm                                      (elm)       
Elvish                                   (elv)       
Emacs Dev Env                            (ede)       
Emojicode                                (emojic, 🍇) 
Erlang                                   (erl, hrl)  
Factor                                   (factor)    
FEN                                      (fen)       
Fennel                                   (fnl)       
Fish                                     (fish)      
FlatBuffers Schema                       (fbs)       
Forge Config                             (cfg)       
Forth                                    (4th, forth, fr, frt, fth, f83, fb, fpm, e4, rx, ft)
FORTRAN Legacy                           (f, for, ftn, f77, pfo)
FORTRAN Modern                           (f03, f08, f90, f95)
FreeMarker                               (ftl, ftlh, ftlx)
F#                                       (fs, fsi, fsx, fsscript)
F*                                       (fst)       
Futhark                                  (fut)       
GDB Script                               (gdb)       
GDScript                                 (gd)        
Gherkin (Cucumber)                       (feature)   
Gleam                                    (gleam)     
GLSL                                     (vert, tesc, tese, geom, frag, comp, mesh, task, rgen, rint, rahit, rchit, rmiss, rcall, glsl)
Gml                                      (gml)       
Go                                       (go)        
Go HTML                                  (gohtml)    
GraphQL                                  (gql, graphql)
Groovy                                   (groovy, grt, gtpl, gvy)
Gwion                                    (gw)        
Haml                                     (haml)      
Hamlet                                   (hamlet)    
Happy                                    (y, ly)     
Handlebars                               (hbs, handlebars)
Haskell                                  (hs)        
Haxe                                     (hx)        
HCL                                      (hcl, tf, tfvars)
Headache                                 (ha)        
HEX                                      (hex)       
HICAD                                    (MAC, mac)  
HLSL                                     (hlsl)      
HolyC                                    (HC, hc, ZC, zc)
HTML                                     (html, htm) 
Hy                                       (hy)        
Idris                                    (idr, lidr) 
INI                                      (ini)       
Intel HEX                                (ihex)      
Isabelle                                 (thy)       
JAI                                      (jai)       
Janet                                    (janet)     
Java                                     (java)      
JavaScript                               (cjs, js, mjs)
Jinja2                                   (j2, jinja) 
jq                                       (jq)        
JSON                                     (json)      
Jsonnet                                  (jsonnet, libsonnet)
JSX                                      (jsx)       
Julia                                    (jl)        
Julius                                   (julius)    
Jupyter Notebooks                        (ipynb)     
K                                        (k)         
Kakoune script                           (kak)       
Kotlin                                   (kt, kts)   
Korn shell                               (ksh)       
LALRPOP                                  (lalrpop)   
KV Language                              (kv)        
Lean                                     (lean, hlean)
LESS                                     (less)      
Liquid                                   (liquid)    
Lingua Franca                            (lf)        
LD Script                                (ld, lds)   
Common Lisp                              (lisp, lsp, asd)
LiveScript                               (ls)        
LLVM                                     (ll)        
Logtalk                                  (lgt, logtalk)
LOLCODE                                  (lol)       
Lua                                      (lua, luau) 
Lucius                                   (lucius)    
M4                                       (m4)        
Madlang                                  (mad)       
Makefile                                 (makefile, mak, mk)
Markdown                                 (md, markdown)
Max                                      (maxpat)    
Metal Shading Language                   (metal)     
Mint                                     (mint)      
Mlatu                                    (mlt)       
Module-Definition                        (def)       
MoonBit                                  (mbt)       
MoonScript                               (moon)      
MSBuild                                  (csproj, vbproj, fsproj, props, targets)
Mustache                                 (mustache)  
Nextflow                                 (nextflow, nf)
Nim                                      (nim)       
Nix                                      (nix)       
Not Quite Perl                           (nqp)       
Nushell                                  (nu)        
Objective-C                              (m)         
Objective-C++                            (mm)        
OCaml                                    (ml, mli, mll, mly, re, rei)
Odin                                     (odin)      
OpenSCAD                                 (scad)      
Open Policy Agent                        (rego)      
OpenQASM                                 (qasm)      
OpenType Feature File                    (fea)       
Org                                      (org)       
Oz                                       (oz)        
Pan                                      (pan, tpl)  
Pascal                                   (pas)       
Perl                                     (pl, pm)    
Pest                                     (pest)      
PHP                                      (php)       
Poke                                     (pk)        
Polly                                    (polly)     
Pony                                     (pony)      
PostCSS                                  (pcss, sss) 
PowerShell                               (ps1, psm1, psd1, ps1xml, cdxml, pssc, psc1)
Processing                               (pde)       
Prolog                                   (p, pro)    
PSL Assertion                            (psl)       
Protocol Buffers                         (proto)     
Pug                                      (pug)       
Puppet                                   (pp)        
PureScript                               (purs)      
Python                                   (py, pyw, pyi)
PRQL                                     (prql)      
Q                                        (q)         
QCL                                      (qcl)       
QML                                      (qml)       
R                                        (r)         
Racket                                   (rkt, scrbl)
Rakefile                                 (rake)      
Raku                                     (raku, rakumod, rakutest, pm6, pl6, p6)
Razor                                    (cshtml, razor)
Redscript                                (reds)      
Ren'Py                                   (rpy)       
ReScript                                 (res, resi) 
ReStructuredText                         (rst)       
Rusty Object Notation                    (ron)       
RPM Specfile                             (spec)      
Ruby                                     (rb)        
Ruby HTML                                (rhtml, erb)
Rust                                     (rs)        
Sass                                     (sass, scss)
Scala                                    (sc, scala) 
Scheme                                   (scm, ss)   
Shell                                    (sh)        
ShaderLab                                (shader, cginc)
Slang                                    (slang)     
Standard ML (SML)                        (sml)       
Smalltalk                                (cs.st, pck.st)
Snakemake                                (smk, rules)
Solidity                                 (sol)       
Specman e                                (e)         
Spice Netlist                            (ckt)       
SQL                                      (sql)       
SQF                                      (sqf)       
SRecode Template                         (srt)       
Stan                                     (stan)      
Stratego/XT                              (str)       
Stylus                                   (styl)      
Svelte                                   (svelte)    
SVG                                      (svg)       
Swift                                    (swift)     
SWIG                                     (swg, i)    
SystemVerilog                            (sv, svh)   
TCL                                      (tcl)       
Tera                                     (tera)      
TeX                                      (tex, sty)  
Plain Text                               (text, txt) 
Thrift                                   (thrift)    
TOML                                     (toml)      
TSX                                      (tsx)       
TTCN-3                                   (ttcn, ttcn3, ttcnpp)
Twig                                     (twig)      
TypeScript                               (ts, mts, cts)
Typst                                    (typ)       
UMPL                                     (umpl)      
Unison                                   (u)         
Unreal Markdown                          (udn)       
Unreal Plugin                            (uplugin)   
Unreal Project                           (uproject)  
Unreal Script                            (uc, uci, upkg)
Unreal Shader                            (usf)       
Unreal Shader Header                     (ush)       
Ur/Web                                   (ur, urs)   
Ur/Web Project                           (urp)       
Vala                                     (vala)      
VB6                                      (frm, bas, cls)
VBScript                                 (vbs)       
Apache Velocity                          (vm)        
Verilog                                  (vg, vh)    
Verilog Args File                        (irunargs, xrunargs)
VHDL                                     (vhd, vhdl) 
Visual Basic                             (vb)        
Visual Studio Project                    (vcproj, vcxproj)
Visual Studio Solution                   (sln)       
Vim Script                               (vim)       
Vue                                      (vue)       
WebAssembly                              (wat, wast) 
The WenYan Programming Language          (wy)        
WebGPU Shader Language                   (wgsl)      
Wolfram                                  (nb, wl)    
XAML                                     (xaml)      
Xcode Config                             (xcconfig)  
XML                                      (xml)       
XSL                                      (xsl, xslt) 
Xtend                                    (xtend)     
YAML                                     (yaml, yml) 
ZenCode                                  (zs)        
Zig                                      (zig)       
ZoKrates                                 (zok)       
Zsh                                      (zsh)       

```
