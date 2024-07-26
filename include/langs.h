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

#ifndef LANGS_H
#define LANGS_H

#ifdef CCLOC_LANGS_DEFS
    #define Abap 0
    #define ABNF 1
    #define ActionScript 2
    #define Ada 3
    #define Agda 4
    #define Alex 5
    #define Alloy 6
    #define Arduino 7
    #define AsciiDoc 8
    #define Asn1 9
    #define Asp 10
    #define AspNet 11
    #define Assembly 12
    #define AssemblyGAS 13
    #define Astro 14
    #define Ats 15
    #define Autoconf 16
    #define Autoit 17
    #define AutoHotKey 18
    #define Automake 19
    #define AWK 20
    #define Bash 21
    #define Batch 22
    #define Bazel 23
    #define Bean 24
    #define Bitbake 25
    #define BrightScript 26
    #define C 27
    #define Cabal 28
    #define Cassius 29
    #define Ceylon 30
    #define Chapel 31
    #define CHeader 32
    #define Circom 33
    #define Clojure 34
    #define ClojureC 35
    #define ClojureScript 36
    #define CMake 37
    #define Cobol 38
    #define CodeQL 39
    #define CoffeeScript 40
    #define Cogent 41
    #define ColdFusion 42
    #define ColdFusionScript 43
    #define Coq 44
    #define Cpp 45
    #define CppHeader 46
    #define Crystal 47
    #define CSharp 48
    #define CShell 49
    #define Css 50
    #define Cuda 51
    #define Cython 52
    #define D 53
    #define Daml 54
    #define Dart 55
    #define DeviceTree 56
    #define Dhall 57
    #define Dockerfile 58
    #define DotNetResource 59
    #define DreamMaker 60
    #define Dust 61
    #define Ebuild 62
    #define EdgeQL 63
    #define ESDL 64
    #define Edn 65
    #define Elisp 66
    #define Elixir 67
    #define Elm 68
    #define Elvish 69
    #define EmacsDevEnv 70
    #define Emojicode 71
    #define Erlang 72
    #define Factor 73
    #define FEN 74
    #define Fennel 75
    #define Fish 76
    #define FlatBuffers 77
    #define ForgeConfig 78
    #define Forth 79
    #define FortranLegacy 80
    #define FortranModern 81
    #define FreeMarker 82
    #define FSharp 83
    #define Fstar 84
    #define Futhark 85
    #define GDB 86
    #define GdScript 87
    #define Gherkin 88
    #define Gleam 89
    #define Glsl 90
    #define Gml 91
    #define Go 92
    #define Gohtml 93
    #define Graphql 94
    #define Groovy 95
    #define Gwion 96
    #define Haml 97
    #define Hamlet 98
    #define Happy 99
    #define Handlebars 100
    #define Haskell 101
    #define Haxe 102
    #define Hcl 103
    #define Headache 104
    #define Hex 105
    #define HiCad 106
    #define Hlsl 107
    #define HolyC 108
    #define Html 109
    #define Hy 110
    #define Idris 111
    #define Ini 112
    #define IntelHex 113
    #define Isabelle 114
    #define Jai 115
    #define Janet 116
    #define Java 117
    #define JavaScript 118
    #define Jinja2 119
    #define Jq 120
    #define Json 121
    #define Jsonnet 122
    #define Jsx 123
    #define Julia 124
    #define Julius 125
    #define Jupyter 126
    #define K 127
    #define KakouneScript 128
    #define Kotlin 129
    #define Ksh 130
    #define Lalrpop 131
    #define KvLanguage 132
    #define Lean 133
    #define Less 134
    #define Liquid 135
    #define LinguaFranca 136
    #define LinkerScript 137
    #define Lisp 138
    #define LiveScript 139
    #define LLVM 140
    #define Logtalk 141
    #define LolCode 142
    #define Lua 143
    #define Lucius 144
    #define M4 145
    #define Madlang 146
    #define Makefile 147
    #define Markdown 148
    #define Max 149
    #define Meson 150
    #define Metal 151
    #define Mint 152
    #define Mlatu 153
    #define ModuleDef 154
    #define MoonBit 155
    #define MoonScript 156
    #define MsBuild 157
    #define Mustache 158
    #define Nextflow 159
    #define Nim 160
    #define Nix 161
    #define NotQuitePerl 162
    #define NuGetConfig 163
    #define Nushell 164
    #define ObjectiveC 165
    #define ObjectiveCpp 166
    #define OCaml 167
    #define Odin 168
    #define OpenScad 169
    #define OpenPolicyAgent 170
    #define OpenQasm 171
    #define OpenType 172
    #define Org 173
    #define Oz 174
    #define PacmanMakepkg 175
    #define Pan 176
    #define Pascal 177
    #define Perl 178
    #define Pest 179
    #define Php 180
    #define Poke 181
    #define Polly 182
    #define Pony 183
    #define PostCss 184
    #define PowerShell 185
    #define Processing 186
    #define Prolog 187
    #define PSL 188
    #define Protobuf 189
    #define Pug 190
    #define Puppet 191
    #define PureScript 192
    #define Python 193
    #define PRQL 194
    #define Q 195
    #define Qcl 196
    #define Qml 197
    #define R 198
    #define Racket 199
    #define Rakefile 200
    #define Raku 201
    #define Razor 202
    #define Redscript 203
    #define Renpy 204
    #define ReScript 205
    #define ReStructuredText 206
    #define RON 207
    #define RPMSpecfile 208
    #define Ruby 209
    #define RubyHtml 210
    #define Rust 211
    #define Sass 212
    #define Scala 213
    #define Scheme 214
    #define Scons 215
    #define Sh 216
    #define ShaderLab 217
    #define Slang 218
    #define Sml 219
    #define Smalltalk 220
    #define Snakemake 221
    #define Solidity 222
    #define SpecmanE 223
    #define Spice 224
    #define Sql 225
    #define Sqf 226
    #define SRecode 227
    #define Stan 228
    #define Stratego 229
    #define Stylus 230
    #define Svelte 231
    #define Svg 232
    #define Swift 233
    #define Swig 234
    #define SystemVerilog 235
    #define Tcl 236
    #define Tera 237
    #define Tex 238
    #define Text 239
    #define Thrift 240
    #define Toml 241
    #define Tsx 242
    #define Ttcn 243
    #define Twig 244
    #define TypeScript 245
    #define Typst 246
    #define UMPL 247
    #define Unison 248
    #define UnrealDeveloperMarkdown 249
    #define UnrealPlugin 250
    #define UnrealProject 251
    #define UnrealScript 252
    #define UnrealShader 253
    #define UnrealShaderHeader 254
    #define UrWeb 255
    #define UrWebProject 256
    #define Vala 257
    #define VB6 258
    #define VBScript 259
    #define Velocity 260
    #define Verilog 261
    #define VerilogArgsFile 262
    #define Vhdl 263
    #define VisualBasic 264
    #define VisualStudioProject 265
    #define VisualStudioSolution 266
    #define VimScript 267
    #define Vue 268
    #define WebAssembly 269
    #define WenYan 270
    #define WGSL 271
    #define Wolfram 272
    #define Xaml 273
    #define XcodeConfig 274
    #define Xml 275
    #define XSL 276
    #define Xtend 277
    #define Yaml 278
    #define ZenCode 279
    #define Zig 280
    #define Zokrates 281
    #define Zsh 282
    #define TOTAL 283
#endif

#define EXTENSIONS_SIZE 451
#define LANGUAGES_SIZE 284

typedef struct
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
} loc_language;

#endif