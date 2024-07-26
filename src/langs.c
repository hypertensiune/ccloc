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

#define CCLOC_LANGS_DEFS

#include "../include/langs.h"

loc_extension extensions[EXTENSIONS_SIZE] =
{
    {"4th", Forth},
    {"HC", HolyC},
    {"MAC", HiCad},
    {"ZC", HolyC},
    {"abap", Abap},
    {"abnf", ABNF},
    {"ada", Ada},
    {"adb", Ada},
    {"adoc", AsciiDoc},
    {"ads", Ada},
    {"agda", Agda},
    {"ahk", AutoHotKey},
    {"als", Alloy},
    {"am", Automake},
    {"as", ActionScript},
    {"asa", Asp},
    {"asax", AspNet},
    {"asciidoc", AsciiDoc},
    {"ascx", AspNet},
    {"asd", Lisp},
    {"asm", Assembly},
    {"asmx", AspNet},
    {"asn1", Asn1},
    {"asp", Asp},
    {"aspx", AspNet},
    {"astro", Astro},
    {"atxt", Ats},
    {"au3", Autoit},
    {"awk", AWK},
    {"bas", VB6},
    {"bash", Bash},
    {"bat", Batch},
    {"bazel", Bazel},
    {"bb", Bitbake},
    {"bbappend", Bitbake},
    {"bbclass", Bitbake},
    {"bean", Bean},
    {"beancount", Bean},
    {"brs", BrightScript},
    {"btm", Batch},
    {"bzl", Bazel},
    {"c", C},
    {"c++", Cpp},
    {"cabal", Cabal},
    {"cassius", Cassius},
    {"cbl", Cobol},
    {"cc", Cpp},
    {"ccp", Cobol},
    {"cdxml", PowerShell},
    {"ceylon", Ceylon},
    {"cfc", ColdFusionScript},
    {"cfg", ForgeConfig},
    {"cfm", ColdFusion},
    {"cginc", ShaderLab},
    {"chpl", Chapel},
    {"circom", Circom},
    {"cjs", JavaScript},
    {"cjsx", CoffeeScript},
    {"ckt", Spice},
    {"clj", Clojure},
    {"cljc", ClojureC},
    {"cljs", ClojureScript},
    {"cls", VB6},
    {"cmake", CMake},
    {"cmd", Batch},
    {"cob", Cobol},
    {"cobol", Cobol},
    {"coffee", CoffeeScript},
    {"cogent", Cogent},
    {"comp", Glsl},
    {"conf", Bitbake},
    {"cpp", Cpp},
    {"cpy", Cobol},
    {"cr", Crystal},
    {"cs", CSharp},
    {"cs.st", Smalltalk},
    {"csh", CShell},
    {"cshtml", Razor},
    {"csproj", MsBuild},
    {"css", Css},
    {"csx", CSharp},
    {"cts", TypeScript},
    {"cu", Cuda},
    {"cxx", Cpp},
    {"d", D},
    {"daml", Daml},
    {"dart", Dart},
    {"dats", Ats},
    {"def", ModuleDef},
    {"dhall", Dhall},
    {"dm", DreamMaker},
    {"dme", DreamMaker},
    {"dockerfile", Dockerfile},
    {"dockerignore", Dockerfile},
    {"dts", DeviceTree},
    {"dtsi", DeviceTree},
    {"dust", Dust},
    {"e", SpecmanE},
    {"e4", Forth},
    {"ebuild", Ebuild},
    {"ec", C},
    {"eclass", Ebuild},
    {"ede", EmacsDevEnv},
    {"edgeql", EdgeQL},
    {"edn", Edn},
    {"el", Elisp},
    {"elm", Elm},
    {"elv", Elvish},
    {"emojic", Emojicode},
    {"erb", RubyHtml},
    {"erl", Erlang},
    {"esdl", ESDL},
    {"ex", Elixir},
    {"exs", Elixir},
    {"f", FortranLegacy},
    {"f03", FortranModern},
    {"f08", FortranModern},
    {"f77", FortranLegacy},
    {"f83", Forth},
    {"f90", FortranModern},
    {"f95", FortranModern},
    {"factor", Factor},
    {"fb", Forth},
    {"fbs", FlatBuffers},
    {"fea", OpenType},
    {"feature", Gherkin},
    {"fen", FEN},
    {"fish", Fish},
    {"fnl", Fennel},
    {"for", FortranLegacy},
    {"forth", Forth},
    {"fpm", Forth},
    {"fr", Forth},
    {"frag", Glsl},
    {"frm", VB6},
    {"frt", Forth},
    {"fs", FSharp},
    {"fsi", FSharp},
    {"fsproj", MsBuild},
    {"fsscript", FSharp},
    {"fst", Fstar},
    {"fsx", FSharp},
    {"ft", Forth},
    {"fth", Forth},
    {"ftl", FreeMarker},
    {"ftlh", FreeMarker},
    {"ftlx", FreeMarker},
    {"ftn", FortranLegacy},
    {"fut", Futhark},
    {"gd", GdScript},
    {"gdb", GDB},
    {"geom", Glsl},
    {"gleam", Gleam},
    {"glsl", Glsl},
    {"gml", Gml},
    {"go", Go},
    {"gohtml", Gohtml},
    {"gql", Graphql},
    {"graphql", Graphql},
    {"groovy", Groovy},
    {"grt", Groovy},
    {"gtpl", Groovy},
    {"gvy", Groovy},
    {"gw", Gwion},
    {"h", CHeader},
    {"ha", Headache},
    {"haml", Haml},
    {"hamlet", Hamlet},
    {"handlebars", Handlebars},
    {"hats", Ats},
    {"hbs", Handlebars},
    {"hc", HolyC},
    {"hcl", Hcl},
    {"hex", Hex},
    {"hh", CppHeader},
    {"hlean", Lean},
    {"hlsl", Hlsl},
    {"hpp", CppHeader},
    {"hrl", Erlang},
    {"hs", Haskell},
    {"htm", Html},
    {"html", Html},
    {"hx", Haxe},
    {"hxx", CppHeader},
    {"hy", Hy},
    {"i", Swig},
    {"idr", Idris},
    {"ihex", IntelHex},
    {"in", Autoconf},
    {"inc", Bitbake},
    {"ini", Ini},
    {"inl", CppHeader},
    {"ino", Arduino},
    {"ipp", CppHeader},
    {"ipynb", Jupyter},
    {"irunargs", VerilogArgsFile},
    {"j2", Jinja2},
    {"jai", Jai},
    {"janet", Janet},
    {"java", Java},
    {"jinja", Jinja2},
    {"jl", Julia},
    {"jq", Jq},
    {"js", JavaScript},
    {"json", Json},
    {"jsonnet", Jsonnet},
    {"jsx", Jsx},
    {"julius", Julius},
    {"k", K},
    {"kak", KakouneScript},
    {"ksh", Ksh},
    {"kt", Kotlin},
    {"kts", Kotlin},
    {"kv", KvLanguage},
    {"lalrpop", Lalrpop},
    {"ld", LinkerScript},
    {"lds", LinkerScript},
    {"lean", Lean},
    {"less", Less},
    {"lf", LinguaFranca},
    {"lgt", Logtalk},
    {"libsonnet", Jsonnet},
    {"lidr", Idris},
    {"liquid", Liquid},
    {"lisp", Lisp},
    {"ll", LLVM},
    {"logtalk", Logtalk},
    {"lol", LolCode},
    {"ls", LiveScript},
    {"lsp", Lisp},
    {"lua", Lua},
    {"luau", Lua},
    {"lucius", Lucius},
    {"ly", Happy},
    {"m", ObjectiveC},
    {"m4", M4},
    {"mac", HiCad},
    {"mad", Madlang},
    {"mak", Makefile},
    {"makefile", Makefile},
    {"markdown", Markdown},
    {"master", AspNet},
    {"maxpat", Max},
    {"mbt", MoonBit},
    {"md", Markdown},
    {"mesh", Glsl},
    {"metal", Metal},
    {"mint", Mint},
    {"mjs", JavaScript},
    {"mk", Makefile},
    {"ml", OCaml},
    {"mli", OCaml},
    {"mll", OCaml},
    {"mlt", Mlatu},
    {"mly", OCaml},
    {"mm", ObjectiveCpp},
    {"moon", MoonScript},
    {"mts", TypeScript},
    {"mustache", Mustache},
    {"nb", Wolfram},
    {"nextflow", Nextflow},
    {"nf", Nextflow},
    {"nim", Nim},
    {"nix", Nix},
    {"nqp", NotQuitePerl},
    {"nu", Nushell},
    {"odin", Odin},
    {"org", Org},
    {"oz", Oz},
    {"p", Prolog},
    {"p6", Raku},
    {"pad", Ada},
    {"pan", Pan},
    {"pas", Pascal},
    {"pcc", Cpp},
    {"pck.st", Smalltalk},
    {"pcss", PostCss},
    {"pde", Processing},
    {"pest", Pest},
    {"pfo", FortranLegacy},
    {"pgc", C},
    {"php", Php},
    {"pk", Poke},
    {"pl", Perl},
    {"pl6", Raku},
    {"pm", Perl},
    {"pm6", Raku},
    {"polly", Polly},
    {"pony", Pony},
    {"pp", Puppet},
    {"pro", Prolog},
    {"props", MsBuild},
    {"proto", Protobuf},
    {"prql", PRQL},
    {"ps1", PowerShell},
    {"ps1xml", PowerShell},
    {"psc1", PowerShell},
    {"psd1", PowerShell},
    {"psl", PSL},
    {"psm1", PowerShell},
    {"pssc", PowerShell},
    {"pug", Pug},
    {"purs", PureScript},
    {"pxd", Cython},
    {"pxi", Cython},
    {"py", Python},
    {"pyi", Python},
    {"pyw", Python},
    {"pyx", Cython},
    {"q", Q},
    {"qasm", OpenQasm},
    {"qcl", Qcl},
    {"ql", CodeQL},
    {"qll", CodeQL},
    {"qml", Qml},
    {"r", R},
    {"rahit", Glsl},
    {"rake", Rakefile},
    {"raku", Raku},
    {"rakumod", Raku},
    {"rakutest", Raku},
    {"razor", Razor},
    {"rb", Ruby},
    {"rcall", Glsl},
    {"rchit", Glsl},
    {"re", OCaml},
    {"reds", Redscript},
    {"rego", OpenPolicyAgent},
    {"rei", OCaml},
    {"res", ReScript},
    {"resi", ReScript},
    {"resx", DotNetResource},
    {"rgen", Glsl},
    {"rhtml", RubyHtml},
    {"rint", Glsl},
    {"rkt", Racket},
    {"rmiss", Glsl},
    {"ron", RON},
    {"rpy", Renpy},
    {"rs", Rust},
    {"rst", ReStructuredText},
    {"rules", Snakemake},
    {"rx", Forth},
    {"s", AssemblyGAS},
    {"sass", Sass},
    {"sats", Ats},
    {"sc", Scala},
    {"scad", OpenScad},
    {"scala", Scala},
    {"scm", Scheme},
    {"scrbl", Racket},
    {"scss", Sass},
    {"sh", Sh},
    {"shader", ShaderLab},
    {"sitemap", AspNet},
    {"slang", Slang},
    {"sln", VisualStudioSolution},
    {"smk", Snakemake},
    {"sml", Sml},
    {"sol", Solidity},
    {"spec", RPMSpecfile},
    {"sqf", Sqf},
    {"sql", Sql},
    {"srt", SRecode},
    {"ss", Scheme},
    {"sss", PostCss},
    {"stan", Stan},
    {"str", Stratego},
    {"sty", Tex},
    {"styl", Stylus},
    {"sv", SystemVerilog},
    {"svelte", Svelte},
    {"svg", Svg},
    {"svh", SystemVerilog},
    {"swg", Swig},
    {"swift", Swift},
    {"targets", MsBuild},
    {"task", Glsl},
    {"tcl", Tcl},
    {"tera", Tera},
    {"tesc", Glsl},
    {"tese", Glsl},
    {"tex", Tex},
    {"text", Text},
    {"tf", Hcl},
    {"tfvars", Hcl},
    {"thrift", Thrift},
    {"thy", Isabelle},
    {"toml", Toml},
    {"tpl", Pan},
    {"tpp", Cpp},
    {"ts", TypeScript},
    {"tsx", Tsx},
    {"ttcn", Ttcn},
    {"ttcn3", Ttcn},
    {"ttcnpp", Ttcn},
    {"twig", Twig},
    {"txt", Text},
    {"typ", Typst},
    {"u", Unison},
    {"uc", UnrealScript},
    {"uci", UnrealScript},
    {"udn", UnrealDeveloperMarkdown},
    {"umpl", UMPL},
    {"upkg", UnrealScript},
    {"uplugin", UnrealPlugin},
    {"uproject", UnrealProject},
    {"ur", UrWeb},
    {"urp", UrWebProject},
    {"urs", UrWeb},
    {"usf", UnrealShader},
    {"ush", UnrealShaderHeader},
    {"v", Coq},
    {"vala", Vala},
    {"vb", VisualBasic},
    {"vbproj", MsBuild},
    {"vbs", VBScript},
    {"vcproj", VisualStudioProject},
    {"vcxproj", VisualStudioProject},
    {"vert", Glsl},
    {"vg", Verilog},
    {"vh", Verilog},
    {"vhd", Vhdl},
    {"vhdl", Vhdl},
    {"vim", VimScript},
    {"vm", Velocity},
    {"vue", Vue},
    {"wast", WebAssembly},
    {"wat", WebAssembly},
    {"webinfo", AspNet},
    {"wgsl", WGSL},
    {"wl", Wolfram},
    {"wy", WenYan},
    {"x", Alex},
    {"xaml", Xaml},
    {"xcconfig", XcodeConfig},
    {"xml", Xml},
    {"xrunargs", VerilogArgsFile},
    {"xsl", XSL},
    {"xslt", XSL},
    {"xtend", Xtend},
    {"y", Happy},
    {"yaml", Yaml},
    {"yml", Yaml},
    {"zc", HolyC},
    {"zig", Zig},
    {"zok", Zokrates},
    {"zs", ZenCode},
    {"zsh", Zsh},
    {"🍇", Emojicode},
};

loc_language languages[LANGUAGES_SIZE] =
{
    {
	    "ABAP",
	    {"*", "", ""}
    },
    {
        "ABNF",
        {";", "", ""}
    },
    {
        "ActionScript",
        {"//", "/*", "*/"}
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
        "Alex",
        {"", "", ""}
    },
    {
        "Alloy",
        {"--", "/*", "*/"}
    },
    {
        "Arduino C++",
        {"//", "/*", "*/"}
    },
    {
        "AsciiDoc",
        {"//", "////", "////"}
    },
    {
        "ASN.1",
        {"--", "/*", "*/"}
    },
    {
        "ASP",
        {"'", "", ""}
    },
    {
        "ASP.NET",
        {"", "<!--", "-->"}
    },
    {
        "Assembly",
        {";", "", ""}
    },
    {
        "GNU Style Assembly",
        {"//", "/*", "*/"}
    },
    {
        "Astro",
        {"//", "/*", "*/"}
    },
    {
        "ATS",
        {"//", "(*", "*)"}
    },
    {
        "Autoconf",
        {"#", "", ""}
    },
    {
        "Autoit",
        {";", "#comments-start", "#comments-end"}
    },
    {
        "AutoHotKey",
        {";", "/*", "*/"}
    },
    {
        "Automake",
        {"#", "", ""}
    },
    {
        "AWK",
        {"#", "", ""}
    },
    {
        "BASH",
        {"#", "", ""}
    },
    {
        "Batch",
        {"REM", "", ""}
    },
    {
        "Bazel",
        {"#", "", ""}
    },
    {
        "Bean",
        {";", "", ""}
    },
    {
        "Bitbake",
        {"#", "", ""}
    },
    {
        "BrightScript",
        {"'", "", ""}
    },
    {
        "C",
        {"//", "/*", "*/"}
    },
    {
        "Cabal",
        {"--", "{-", "-}"}
    },
    {
        "Cassius",
        {"//", "/*", "*/"}
    },
    {
        "Ceylon",
        {"//", "/*", "*/"}
    },
    {
        "Chapel",
        {"//", "/*", "*/"}
    },
    {
        "C Header",
        {"//", "/*", "*/"}
    },
    {
        "Circom",
        {"//", "/*", "*/"}
    },
    {
        "Clojure",
        {";", "", ""}
    },
    {
        "ClojureC",
        {";", "", ""}
    },
    {
        "ClojureScript",
        {";", "", ""}
    },
    {
        "CMake",
        {"#", "", ""}
    },
    {
        "COBOL",
        {"*", "", ""}
    },
    {
        "CodeQL",
        {"//", "/*", "*/"}
    },
    {
        "CoffeeScript",
        {"#", "###", "###"}
    },
    {
        "Cogent",
        {"--", "", ""}
    },
    {
        "ColdFusion",
        {"", "<!---", "--->"}
    },
    {
        "ColdFusion CFScript",
        {"//", "/*", "*/"}
    },
    {
        "Coq",
        {"", "(*", "*)"}
    },
    {
        "C++",
        {"//", "/*", "*/"}
    },
    {
        "C++ Header",
        {"//", "/*", "*/"}
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
        "C Shell",
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
        "Cython",
        {"#", "", ""}
    },
    {
        "D",
        {"//", "/*", "*/"}
    },
    {
        "DAML",
        {"-- ", "{-", "-}"}
    },
    {
        "Dart",
        {"//", "/*", "*/"}
    },
    {
        "Device Tree",
        {"//", "/*", "*/"}
    },
    {
        "Dhall",
        {"--", "{-", "-}"}
    },
    {
        "Dockerfile",
        {"#", "", ""}
    },
    {
        ".NET Resource",
        {"", "<!--", "-->"}
    },
    {
        "Dream Maker",
        {"//", "/*", "*/"}
    },
    {
        "Dust.js",
        {"", "{!", "!}"}
    },
    {
        "Ebuild",
        {"#", "", ""}
    },
    {
        "EdgeQL",
        {"#", "", ""}
    },
    {
        "EdgeDB Schema Definition",
        {"#", "", ""}
    },
    {
        "Edn",
        {";", "", ""}
    },
    {
        "Emacs Lisp",
        {";", "", ""}
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
        "Elvish",
        {"#", "", ""}
    },
    {
        "Emacs Dev Env",
        {";", "", ""}
    },
    {
        "Emojicode",
        {"💭", "💭🔜", "🔚💭"}
    },
    {
        "Erlang",
        {"%", "", ""}
    },
    {
        "Factor",
        {"!", "/*", "*/"}
    },
    {
        "FEN",
        {"", "", ""}
    },
    {
        "Fennel",
        {";", "", ""}
    },
    {
        "Fish",
        {"#", "", ""}
    },
    {
        "FlatBuffers Schema",
        {"//", "/*", "*/"}
    },
    {
        "Forge Config",
        {"#", "", ""}
    },
    {
        "Forth",
        {"\\", "( ", ")"}
    },
    {
        "FORTRAN Legacy",
        {"c", "", ""}
    },
    {
        "FORTRAN Modern",
        {"!", "", ""}
    },
    {
        "FreeMarker",
        {"", "<#--", "-->"}
    },
    {
        "F#",
        {"//", "(*", "*)"}
    },
    {
        "F*",
        {"//", "(*", "*)"}
    },
    {
        "Futhark",
        {"--", "", ""}
    },
    {
        "GDB Script",
        {"#", "", ""}
    },
    {
        "GDScript",
        {"#", "", ""}
    },
    {
        "Gherkin (Cucumber)",
        {"#", "", ""}
    },
    {
        "Gleam",
        {"//", "", ""}
    },
    {
        "GLSL",
        {"//", "/*", "*/"}
    },
    {
        "Gml",
        {"//", "/*", "*/"}
    },
    {
        "Go",
        {"//", "/*", "*/"}
    },
    {
        "Go HTML",
        {"", "<!--", "-->"}
    },
    {
        "GraphQL",
        {"#", "", ""}
    },
    {
        "Groovy",
        {"//", "/*", "*/"}
    },
    {
        "Gwion",
        {"#!", "", ""}
    },
    {
        "Haml",
        {"-#", "", ""}
    },
    {
        "Hamlet",
        {"", "<!--", "-->"}
    },
    {
        "Happy",
        {"", "", ""}
    },
    {
        "Handlebars",
        {"", "<!--", "-->"}
    },
    {
        "Haskell",
        {"--", "{-", "-}"}
    },
    {
        "Haxe",
        {"//", "/*", "*/"}
    },
    {
        "HCL",
        {"#", "/*", "*/"}
    },
    {
        "Headache",
        {"//", "/*", "*/"}
    },
    {
        "HEX",
        {"", "", ""}
    },
    {
        "HICAD",
        {"REM", "", ""}
    },
    {
        "HLSL",
        {"//", "/*", "*/"}
    },
    {
        "HolyC",
        {"//", "/*", "*/"}
    },
    {
        "HTML",
        {"", "<!--", "-->"}
    },
    {
        "Hy",
        {";", "", ""}
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
        "Intel HEX",
        {"", "", ""}
    },
    {
        "Isabelle",
        {"--", "{*", "*}"}
    },
    {
        "JAI",
        {"//", "/*", "*/"}
    },
    {
        "Janet",
        {"#", "", ""}
    },
    {
        "Java",
        {"//", "/*", "*/"}
    },
    {
        "JavaScript",
        {"//", "/*", "*/"}
    },
    {
        "Jinja2",
        {"", "{#", "#}"}
    },
    {
        "jq",
        {"#", "", ""}
    },
    {
        "JSON",
        {"", "", ""}
    },
    {
        "Jsonnet",
        {"//", "/*", "*/"}
    },
    {
        "JSX",
        {"//", "/*", "*/"}
    },
    {
        "Julia",
        {"#", "#=", "=#"}
    },
    {
        "Julius",
        {"//", "/*", "*/"}
    },
    {
        "Jupyter Notebooks",
        {"", "", ""}
    },
    {
        "K",
        {"/", "", ""}
    },
    {
        "Kakoune script",
        {"#", "", ""}
    },
    {
        "Kotlin",
        {"//", "/*", "*/"}
    },
    {
        "Korn shell",
        {"#", "", ""}
    },
    {
        "LALRPOP",
        {"//", "", ""}
    },
    {
        "KV Language",
        {"# ", "", ""}
    },
    {
        "Lean",
        {"--", "/-", "-/"}
    },
    {
        "LESS",
        {"//", "/*", "*/"}
    },
    {
        "Liquid",
        {"", "<!--", "-->"}
    },
    {
        "Lingua Franca",
        {"//", "/*", "*/"}
    },
    {
        "LD Script",
        {"", "/*", "*/"}
    },
    {
        "Common Lisp",
        {";", "#|", "|#"}
    },
    {
        "LiveScript",
        {"#", "/*", "*/"}
    },
    {
        "LLVM",
        {";", "", ""}
    },
    {
        "Logtalk",
        {"%", "/*", "*/"}
    },
    {
        "LOLCODE",
        {"BTW", "OBTW", "TLDR"}
    },
    {
        "Lua",
        {"--", "--[[", "]]"}
    },
    {
        "Lucius",
        {"//", "/*", "*/"}
    },
    {
        "M4",
        {"#", "", ""}
    },
    {
        "Madlang",
        {"#", "{#", "#}"}
    },
    {
        "Makefile",
        {"#", "", ""}
    },
    {
        "Markdown",
        {"", "", ""}
    },
    {
        "Max",
        {"", "", ""}
    },
    {
        "Meson",
        {"#", "", ""}
    },
    {
        "Metal Shading Language",
        {"//", "/*", "*/"}
    },
    {
        "Mint",
        {"", "", ""}
    },
    {
        "Mlatu",
        {"//", "", ""}
    },
    {
        "Module-Definition",
        {";", "", ""}
    },
    {
        "MoonBit",
        {"//", "", ""}
    },
    {
        "MoonScript",
        {"--", "", ""}
    },
    {
        "MSBuild",
        {"", "<!--", "-->"}
    },
    {
        "Mustache",
        {"", "{{!", "}}"}
    },
    {
        "Nextflow",
        {"//", "/*", "*/"}
    },
    {
        "Nim",
        {"#", "", ""}
    },
    {
        "Nix",
        {"#", "/*", "*/"}
    },
    {
        "Not Quite Perl",
        {"#", "=begin", "=end"}
    },
    {
        "NuGet Config",
        {"", "<!--", "-->"}
    },
    {
        "Nushell",
        {"#", "", ""}
    },
    {
        "Objective-C",
        {"//", "/*", "*/"}
    },
    {
        "Objective-C++",
        {"//", "/*", "*/"}
    },
    {
        "OCaml",
        {"", "(*", "*)"}
    },
    {
        "Odin",
        {"//", "/*", "*/"}
    },
    {
        "OpenSCAD",
        {"//", "/*", "*/"}
    },
    {
        "Open Policy Agent",
        {"#", "", ""}
    },
    {
        "OpenQASM",
        {"//", "/*", "*/"}
    },
    {
        "OpenType Feature File",
        {"#", "", ""}
    },
    {
        "Org",
        {"# ", "", ""}
    },
    {
        "Oz",
        {"%", "/*", "*/"}
    },
    {
        "Pacman's makepkg",
        {"#", "", ""}
    },
    {
        "Pan",
        {"#", "", ""}
    },
    {
        "Pascal",
        {"//", "{", "}"}
    },
    {
        "Perl",
        {"#", "=pod", "=cut"}
    },
    {
        "Pest",
        {"//", "", ""}
    },
    {
        "PHP",
        {"#", "/*", "*/"}
    },
    {
        "Poke",
        {"", "/*", "*/"}
    },
    {
        "Polly",
        {"", "<!--", "-->"}
    },
    {
        "Pony",
        {"//", "/*", "*/"}
    },
    {
        "PostCSS",
        {"//", "/*", "*/"}
    },
    {
        "PowerShell",
        {"#", "<#", "#>"}
    },
    {
        "Processing",
        {"//", "/*", "*/"}
    },
    {
        "Prolog",
        {"%", "/*", "*/"}
    },
    {
        "PSL Assertion",
        {"//", "/*", "*/"}
    },
    {
        "Protocol Buffers",
        {"//", "", ""}
    },
    {
        "Pug",
        {"//", "", ""}
    },
    {
        "Puppet",
        {"#", "", ""}
    },
    {
        "PureScript",
        {"--", "{-", "-}"}
    },
    {
        "Python",
        {"#", "\"\"\"", "\"\"\""}
    },
    {
        "PRQL",
        {"#", "", ""}
    },
    {
        "Q",
        {"/", "", ""}
    },
    {
        "QCL",
        {"//", "/*", "*/"}
    },
    {
        "QML",
        {"//", "/*", "*/"}
    },
    {
        "R",
        {"#", "", ""}
    },
    {
        "Racket",
        {";", "#|", "|#"}
    },
    {
        "Rakefile",
        {"#", "=begin", "=end"}
    },
    {
        "Raku",
        {"#", "#`(", ")"}
    },
    {
        "Razor",
        {"//", "<!--", "-->"}
    },
    {
        "Redscript",
        {"//", "/*", "*/"}
    },
    {
        "Ren'Py",
        {"#", "", ""}
    },
    {
        "ReScript",
        {"//", "/*", "*/"}
    },
    {
        "ReStructuredText",
        {"", "", ""}
    },
    {
        "Rusty Object Notation",
        {"//", "/*", "*/"}
    },
    {
        "RPM Specfile",
        {"#", "", ""}
    },
    {
        "Ruby",
        {"#", "=begin", "=end"}
    },
    {
        "Ruby HTML",
        {"", "<!--", "-->"}
    },
    {
        "Rust",
        {"//", "/*", "*/"}
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
        "Scheme",
        {";", "#|", "|#"}
    },
    {
        "Scons",
        {"#", "", ""}
    },
    {
        "Shell",
        {"#", "", ""}
    },
    {
        "ShaderLab",
        {"//", "/*", "*/"}
    },
    {
        "Slang",
        {"//", "/*", "*/"}
    },
    {
        "Standard ML (SML)",
        {"", "(*", "*)"}
    },
    {
        "Smalltalk",
        {"", "\"", "\""}
    },
    {
        "Snakemake",
        {"#", "", ""}
    },
    {
        "Solidity",
        {"//", "/*", "*/"}
    },
    {
        "Specman e",
        {"--", "'>", "<'"}
    },
    {
        "Spice Netlist",
        {"*", "", ""}
    },
    {
        "SQL",
        {"--", "/*", "*/"}
    },
    {
        "SQF",
        {"//", "/*", "*/"}
    },
    {
        "SRecode Template",
        {";;", "", ""}
    },
    {
        "Stan",
        {"//", "/*", "*/"}
    },
    {
        "Stratego/XT",
        {"//", "/*", "*/"}
    },
    {
        "Stylus",
        {"//", "/*", "*/"}
    },
    {
        "Svelte",
        {"", "<!--", "-->"}
    },
    {
        "SVG",
        {"", "<!--", "-->"}
    },
    {
        "Swift",
        {"//", "/*", "*/"}
    },
    {
        "SWIG",
        {"//", "/*", "*/"}
    },
    {
        "SystemVerilog",
        {"//", "/*", "*/"}
    },
    {
        "TCL",
        {"#", "", ""}
    },
    {
        "Tera",
        {"", "<!--", "-->"}
    },
    {
        "TeX",
        {"%", "", ""}
    },
    {
        "Plain Text",
        {"", "", ""}
    },
    {
        "Thrift",
        {"#", "/*", "*/"}
    },
    {
        "TOML",
        {"#", "", ""}
    },
    {
        "TSX",
        {"//", "/*", "*/"}
    },
    {
        "TTCN-3",
        {"//", "/*", "*/"}
    },
    {
        "Twig",
        {"", "<!--", "-->"}
    },
    {
        "TypeScript",
        {"//", "/*", "*/"}
    },
    {
        "Typst",
        {"//", "/*", "*/"}
    },
    {
        "UMPL",
        {"!", "", ""}
    },
    {
        "Unison",
        {"--", "{-", "-}"}
    },
    {
        "Unreal Markdown",
        {"", "", ""}
    },
    {
        "Unreal Plugin",
        {"", "", ""}
    },
    {
        "Unreal Project",
        {"", "", ""}
    },
    {
        "Unreal Script",
        {"//", "/*", "*/"}
    },
    {
        "Unreal Shader",
        {"//", "/*", "*/"}
    },
    {
        "Unreal Shader Header",
        {"//", "/*", "*/"}
    },
    {
        "Ur/Web",
        {"", "(*", "*)"}
    },
    {
        "Ur/Web Project",
        {"#", "", ""}
    },
    {
        "Vala",
        {"//", "/*", "*/"}
    },
    {
        "VB6",
        {"'", "", ""}
    },
    {
        "VBScript",
        {"'", "", ""}
    },
    {
        "Apache Velocity",
        {"##", "#*", "*#"}
    },
    {
        "Verilog",
        {"//", "/*", "*/"}
    },
    {
        "Verilog Args File",
        {"", "", ""}
    },
    {
        "VHDL",
        {"--", "/*", "*/"}
    },
    {
        "Visual Basic",
        {"'", "", ""}
    },
    {
        "Visual Studio Project",
        {"", "<!--", "-->"}
    },
    {
        "Visual Studio Solution",
        {"", "", ""}
    },
    {
        "Vim Script",
        {"\"", "", ""}
    },
    {
        "Vue",
        {"//", "<!--", "-->"}
    },
    {
        "WebAssembly",
        {";;", "", ""}
    },
    {
        "The WenYan Programming Language",
        {"", "批曰。", "。"}
    },
    {
        "WebGPU Shader Language",
        {"//", "", ""}
    },
    {
        "Wolfram",
        {"", "(*", "*)"}
    },
    {
        "XAML",
        {"", "<!--", "-->"}
    },
    {
        "Xcode Config",
        {"//", "", ""}
    },
    {
        "XML",
        {"", "<!--", "-->"}
    },
    {
        "XSL",
        {"", "<!--", "-->"}
    },
    {
        "Xtend",
        {"//", "/*", "*/"}
    },
    {
        "YAML",
        {"#", "", ""}
    },
    {
        "ZenCode",
        {"//", "/*", "*/"}
    },
    {
        "Zig",
        {"//", "", ""}
    },
    {
        "ZoKrates",
        {"//", "/*", "*/"}
    },
    {
        "Zsh",
        {"#", "", ""}
    },
    {
        "TOTAL",
        {"", "", ""}
    }
};