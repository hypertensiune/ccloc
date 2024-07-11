#ifndef LANGS_H
#define LANGS_H

#define Forth 0
#define Ada 1
#define Agda 2
#define ActionScript 3
#define AmbientTalk 4
#define Awk 5
#define Batch 6
#define C 7
#define Cpp 8
#define ColdFusionScript 9
#define CMake 10
#define OpenCl 11
#define CoffeeScript 12
#define Crystal 13
#define CSharp 14
#define CShell 15
#define Css 16
#define CUDA 17
#define CUDAHeader 18
#define D 19
#define Dart 20
#define Dhall 21
#define DeviceTree 22
#define Docker 23
#define Lisp 24
#define Elixir 25
#define Elm 26
#define Erlang 27
#define Gherkin 28
#define FSharp 29
#define Glsl 30
#define Go 31
#define Groovy 32
#define CCppHeader 33
#define Handlebars 34
#define Haskell 35
#define Html 36
#define Idris 37
#define INI 38
#define Jai 39
#define Java 40
#define Julia 41
#define JavaScript 42
#define Jsx 43
#define Kotlin 44
#define LinkerScript 45
#define Lean 46
#define Less 47
#define Lua 48
#define ObjectiveC 49
#define OCaml 50
#define Wolfram 51
#define BourneShell 52
#define Asp 53
#define AspNet 54
#define Autoconf 55
#define Clojure 56
#define ClojureScript 57
#define ClojureC 58
#define FortranLegacy 59
#define FortranModern 60
#define Makefile 61
#define ObjectiveCpp 62
#define Nim 63
#define Nix 64
#define Php 65
#define Perl 66
#define Puppet 67
#define Qcl 68
#define Qml 69
#define Razor 70
#define Mustache 71
#define Oz 72
#define Prolog 73
#define Pascal 74
#define Hex 75
#define IntelHex 76
#define Json 77
#define Markdown 78
#define ReStructuredText 79
#define Text 80
#define Polly 81
#define PowerShell 82
#define Protobuf 83
#define PureScript 84
#define Pyret 85
#define Python 86
#define R 87
#define Ruby 88
#define Reason 89
#define RubyHtml 90
#define Ron 91
#define Rust 92
#define Assembly 93
#define Sass 94
#define Scala 95
#define SaltStack 96
#define Sml 97
#define Solidity 98
#define Sql 99
#define Stylus 100
#define Svelte 101
#define Swift 102
#define Tcl 103
#define Terraform 104
#define Tex 105
#define Toml 106
#define TypeScript 107
#define Tsx 108
#define Isabelle 109
#define UnrealScript 110
#define Coq 111
#define VimScript 112
#define Vue 113
#define XML 114
#define Yaml 115
#define Yacc 116
#define Zig 117
#define Zsh 118
#define Haxe 119
#define XAML 120

const int EXTENSIONS_SIZE = 200;
const int LANGUAGES_SIZE = 130;

typedef struct 
{
    char* name;
    int lang_id;
} loc_extension;

typedef struct
{
    char* name;
    struct 
    {
        char sl[10];
        char ml_start[10];
        char ml_end[10];
    } com;
} loc_language;

loc_extension extensions[200] = 
{
    {"4th", Forth},
    {"ada", Ada},
    {"adb", Ada},
    {"ads", Ada},
    {"agda", Agda},
    {"arr", Pyret},
    {"as", ActionScript},
    {"asa", Asp},
    {"asax", AspNet},
    {"ascx", AspNet},
    {"asm", Assembly},
    {"asmx", AspNet},
    {"asp", Asp},
    {"aspx", AspNet},
    {"at", AmbientTalk},
    {"awk", Awk},
    {"bat", Batch},
    {"btm", Batch},
    {"c", C},
    {"c++", Cpp},
    {"cc", Cpp},
    {"cfc", ColdFusionScript},
    {"cl", OpenCl},
    {"clj", Clojure},
    {"cljc", ClojureC},
    {"cljs", ClojureScript},
    {"cmake", CMake},
    {"cmd", Batch},
    {"coffee", CoffeeScript},
    {"comp", Glsl},
    {"cpp", Cpp},
    {"cr", Crystal},
    {"cs", CSharp},
    {"csh", CShell},
    {"cshtml", Razor},
    {"css", Css},
    {"cu", CUDA},
    {"cuh", CUDAHeader},
    {"cxx", Cpp},
    {"d", D},
    {"dart", Dart},
    {"dhall", Dhall},
    {"docker", Docker},
    {"dts", DeviceTree},
    {"dtsi", DeviceTree},
    {"e4", Forth},
    {"ec", C},
    {"el", Lisp},
    {"elm", Elm},
    {"erb", RubyHtml},
    {"erl", Erlang},
    {"ex", Elixir},
    {"exs", Elixir},
    {"f", FortranLegacy},
    {"f03", FortranModern},
    {"f08", FortranModern},
    {"f77", FortranLegacy},
    {"f83", Forth},
    {"f90", FortranModern},
    {"f95", FortranModern},
    {"fb", Forth},
    {"feature", Gherkin},
    {"for", FortranLegacy},
    {"forth", Forth},
    {"fpm", Forth},
    {"fr", Forth},
    {"frag", Glsl},
    {"frt", Forth},
    {"fs", FSharp},
    {"fsx", FSharp},
    {"ft", Forth},
    {"fth", Forth},
    {"ftn", FortranLegacy},
    {"geom", Glsl},
    {"go", Go},
    {"groovy", Groovy},
    {"h", CCppHeader},
    {"handlebars", Handlebars},
    {"hbs", Handlebars},
    {"hex", Hex},
    {"hh", CCppHeader},
    {"hlean", Lean},
    {"hpp", CCppHeader},
    {"hrl", Erlang},
    {"hs", Haskell},
    {"html", Html},
    {"hx", Haxe},
    {"hxx", CCppHeader},
    {"idr", Idris},
    {"ihex", IntelHex},
    {"in", Autoconf},
    {"ini", INI},
    {"jai", Jai},
    {"java", Java},
    {"jl", Julia},
    {"js", JavaScript},
    {"json", Json},
    {"jsx", Jsx},
    {"kt", Kotlin},
    {"kts", Kotlin},
    {"lds", LinkerScript},
    {"lean", Lean},
    {"less", Less},
    {"lidr", Idris},
    {"lisp", Lisp},
    {"lsp", Lisp},
    {"lua", Lua},
    {"m", ObjectiveC},
    {"makefile", Makefile},
    {"markdown", Markdown},
    {"master", AspNet},
    {"md", Markdown},
    {"mjs", JavaScript},
    {"mk", Makefile},
    {"ml", OCaml},
    {"mli", OCaml},
    {"mm", ObjectiveCpp},
    {"mustache", Mustache},
    {"nb", Wolfram},
    {"nim", Nim},
    {"nix", Nix},
    {"oz", Oz},
    {"p", Prolog},
    {"pad", Ada},
    {"pas", Pascal},
    {"pcc", Cpp},
    {"pcss", Css},
    {"pfo", FortranLegacy},
    {"pgc", C},
    {"php", Php},
    {"pl", Perl},
    {"pm", Perl},
    {"polly", Polly},
    {"postcss", Css},
    {"pp", Puppet},
    {"pro", Prolog},
    {"proto", Protobuf},
    {"ps1", PowerShell},
    {"psd1", PowerShell},
    {"psm1", PowerShell},
    {"purs", PureScript},
    {"py", Python},
    {"qcl", Qcl},
    {"qml", Qml},
    {"r", R},
    {"rake", Ruby},
    {"rb", Ruby},
    {"re", Reason},
    {"rei", Reason},
    {"rhtml", RubyHtml},
    {"rkt", Lisp},
    {"ron", Ron},
    {"rs", Rust},
    {"rst", ReStructuredText},
    {"rx", Forth},
    {"s", Assembly},
    {"sass", Sass},
    {"sc", Scala},
    {"scala", Scala},
    {"scm", Lisp},
    {"scss", Sass},
    {"sh", BourneShell},
    {"sitemap", AspNet},
    {"sls", SaltStack},
    {"sml", Sml},
    {"sol", Solidity},
    {"sql", Sql},
    {"ss", Lisp},
    {"sss", Css},
    {"sty", Tex},
    {"styl", Stylus},
    {"svelte", Svelte},
    {"swift", Swift},
    {"tcl", Tcl},
    {"tesc", Glsl},
    {"tese", Glsl},
    {"tex", Tex},
    {"text", Text},
    {"tf", Terraform},
    {"thy", Isabelle},
    {"toml", Toml},
    {"ts", TypeScript},
    {"tsx", Tsx},
    {"txt", Text},
    {"uc", UnrealScript},
    {"uci", UnrealScript},
    {"upkg", UnrealScript},
    {"v", Coq},
    {"vert", Glsl},
    {"vim", VimScript},
    {"vue", Vue},
    {"webinfo", AspNet},
    {"wl", Wolfram},
    {"xaml", XAML},
    {"xml", XML},
    {"y", Yacc},
    {"yaml", Yaml},
    {"yml", Yaml},
    {"zig", Zig},
    {"zsh", Zsh}
};

loc_language languages[130] = 
{
    {
	    "Forth",
	    {"\\", "(", ")"}
    },
    {
        "Ada",
        {"--", "", ""}
    },
    {
        "Agda",
        {"--", "{-", "-}"}
    },
    {
        "ActionScript",
        {"//", "/*", "*/"}
    },
    {
        "AmbientTalk",
        {"//", "/*", "*/"}
    },
    {
        "Awk",
        {"#", "", ""}
    },
    {
        "Batch",
        {"REM", "", ""}
    },
    {
        "C",
        {"//", "/*", "*/"}
    },
    {
        "C++",
        {"//", "/*", "*/"}
    },
    {
        "ColdFusionScript",
        {"//", "/*", "*/"}
    },
    {
        "CMake",
        {"#", "#[[", "]]"}
    },
    {
        "OpenCL",
        {"//", "/*", "*/"}
    },
    {
        "CoffeeScript",
        {"#", "###", "###"}
    },
    {
        "Crystal",
        {"#", "", ""}
    },
    {
        "C#",
        {"//", "/*", "*/"}
    },
    {
        "CShell",
        {"#", "", ""}
    },
    {
        "CSS",
        {"//", "/*", "*/"}
    },
    {
        "CUDA",
        {"//", "/*", "*/"}
    },
    {
        "CUDAHeader",
        {"//", "/*", "*/"}
    },
    {
        "D",
        {"//", "/*", "*/"}
    },
    {
        "Dart",
        {"//", "/*", "*/"}
    },
    {
        "Dhall",
        {"--", "{-", "-}"}
    },
    {
        "DeviceTree",
        {"//", "/*", "*/"}
    },
    {
        "Docker",
        {"#", "", ""}
    },
    {
        "Lisp",
        {";", "#|", "|#"}
    },
    {
        "Elixir",
        {"#", "", ""}
    },
    {
        "Elm",
        {"--", "{-", "-}"}
    },
    {
        "Erlang",
        {"%", "", ""}
    },
    {
        "Gherkin",
        {"#", "", ""}
    },
    {
        "F#",
        {"//", "(*", "*)"}
    },
    {
        "GLSL",
        {"//", "/*", "*/"}
    },
    {
        "Go",
        {"//", "/*", "*/"}
    },
    {
        "Groovy",
        {"//", "/*", "*/"}
    },
    {
        "C/C++ Header",
        {"//", "/*", "*/"}
    },
    {
        "",
        {"", "", ""}
    },
    {
        "Haskell",
        {"--", "{-", "-}"}
    },
    {
        "HTML",
        {"", "<!--", "-->"}
    },
    {
        "Idris",
        {"--", "{-", "-}"}
    },
    {
        "INI",
        {";", "", ""}
    },
    {
        "Jai",
        {"//", "/*", "*/"}
    },
    {
        "Java",
        {"//", "/*", "*/"}
    },
    {
        "Julia",
        {"#", "#=", "=#"}
    },
    {
        "JavaScript",
        {"//", "/*", "*/"}
    },
    {
        "JavaScript JSX",
        {"//", "/*", "*/"}
    },
    {
        "Kotlin",
        {"//", "/*", "*/"}
    },
    {
        "LinkerScript",
        {"//", "/*", "*/"}
    },
    {
        "Lean",
        {"--", "/-", "-/"}
    },
    {
        "Less",
        {"//", "/*", "*/"}
    },
    {
        "Lua",
        {"--", "--[[", "]]"}
    },
    {
        "Objective-C",
        {"//", "/*", "*/"}
    },
    {
        "OCaml",
        {"", "(*", "*)"}
    },
    {
        "Wolfram",
        {"", "(*", "*)"}
    },
    {
        "BourneShell",
        {"#", "", ""}
    },
    {
        "ASP",
        {"'", "", ""}
    },
    {
        "ASP.NET",
        {"", "<%--", "-->"}
    },
    {
        "Autoconf",
        {"#", "", ""}
    },
    {
        "Clojure",
        {";", "", ""}
    },
    {
        "ClojureScript",
        {";", "", ""}
    },
    {
        "ClojureC",
        {";", "", ""}
    },
    {
        "FORTRANLegacy",
        {"!", "", ""}
    },
    {
        "FORTRANModern",
        {"!", "", ""}
    },
    {
        "Makefile",
        {"#", "", ""}
    },
    {
        "Objective-C++",
        {"//", "/*", "*/"}
    },
    {
        "Nim",
        {"#", "", ""}
    },
    {
        "Terraform",
        {"#", "/*", "*/"}
    },
    {
        "PHP",
        {"//", "/*", "*/"}
    },
    {
        "Perl",
        {"#", "=pod", "=cut"}
    },
    {
        "Puppet",
        {"#", "", ""}
    },
    {
        "Qcl",
        {"//", "/*", "*/"}
    },
    {
        "Qml",
        {"//", "/*", "*/"}
    },
    {
        "Razor",
        {"", "@*", "*@)"}
    },
    {
        "Mustache",
        {"", "{{!", "!}}"}
    },
    {
        "Oz",
        {"%", "/*", "*/"}
    },
    {
        "Prolog",
        {"%", "/*", "*/"}
    },
    {
        "Pascal",
        {"//", "{", "}"}
    },
    {
        "Hex",
        {"", "", ""}
    },
    {
        "IntelHex",
        {"", "", ""}
    },
    {
        "JSON",
        {"", "", ""}
    },
    {
        "Markdown",
        {"", "", ""}
    },
    {
        "reStructuredText",
        {"", "", ""}
    },
    {
        "PlainText",
        {"", "", ""}
    },
    {
        "Polly",
        {"", "<!--", "-->"}
    },
    {
        "PowerShell",
        {"#", "<#", "#>"}
    },
    {
        "Protobuf",
        {"//", "", ""}
    },
    {
        "PureScript",
        {"--", "{-", "-}"}
    },
    {
        "Pyret",
        {"#", "#|", "|#"}
    },
    {
        "Python",
        {"#", "'''", "'''"}
    },
    {
        "R",
        {"#", "", ""}
    },
    {
        "Ruby",
        {"#", "=begin", "=end"}
    },
    {
        "Reason",
        {"//", "/*", "*/"}
    },
    {
        "RubyHtml",
        {"", "<!--", "-->"}
    },
    {
        "RON",
        {"//", "/*", "*/"}
    },
    {
        "Rust",
        {"//", "/*", "*/"}
    },
    {
        "Assembly",
        {";", "", ""}
    },
    {
        "Sass",
        {"//", "/*", "*/"}
    },
    {
        "Scala",
        {"//", "/*", "*/"}
    },
    {
        "SaltStack",
        {"#", "", ""}
    },
    {
        "SML",
        {"", "(*", "*)"}
    },
    {
        "Solidity",
        {"//", "/*", "*/"}
    },
    {
        "SQL",
        {"--", "/*", "*/"}
    },
    {
        "Stylus",
        {"//", "/*", "*/"}
    },
    {
        "Svelte",
        {"//", "/*", "*/"}
    },
    {
        "Swift",
        {"//", "/*", "*/"}
    },
    {
        "Tcl",
        {"#", "", ""}
    },
    {
        "Terraform",
        {"#", "/*", "*/"}
    },
    {
        "TeX",
        {"%", "", ""}
    },
    {
        "Toml",
        {"#", "", ""}
    },
    {
        "TypeScript",
        {"//", "/*", "*/"}
    },
    {
        "TypesSript TSX",
        {"//", "/*", "*/"}
    },
    {
        "Isabelle",
        {"--", "(*", "*)"}
    },
    {
        "UnrealScript",
        {"//", "/*", "*/"}
    },
    {
        "Coq",
        {"", "(*", "*)"}
    },
    {
        "VimL",
        {"\"", "", ""}
    },
    {
        "Vue",
        {"//", "/*", "*/"}
    },
    {
        "XML",
        {"", "<!--", "-->"}
    },
    {
        "YAML",
        {"#", "", ""}
    },
    {
        "Yacc",
        {"//", "/*", "*/"}
    },
    {
        "Zig",
        {"//", "", ""}
    },
    {
        "ZShell",
        {"#", "", ""}
    },
    {
        "Haxe",
        {"//", "/*", "*/"}
    },
    {
        "XAML",
        {"", "<!--", "-->"}
    }
};

#endif