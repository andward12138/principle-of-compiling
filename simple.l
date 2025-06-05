%{
#include <iostream>
#include <string>
#include <map>
#include <cstring>
using namespace std;

#include "y.tab.h"

extern map<string, int> Store_Identifier;
extern map<string, int> Store_String;
extern map<string, int> Store_Int;

int currRow = 1;

map<string, int> sampleDictionary;

void sampleDictionaryInit() {
    sampleDictionary["and"] = 1;
    sampleDictionary["array"] = 2;
    sampleDictionary["begin"] = 3;
    sampleDictionary["bool"] = 4;
    sampleDictionary["call"] = 5;
    sampleDictionary["case"] = 6;
    sampleDictionary["char"] = 7;
    sampleDictionary["constant"] = 8;
    sampleDictionary["dim"] = 9;
    sampleDictionary["do"] = 10;
    sampleDictionary["else"] = 11;
    sampleDictionary["end"] = 12;
    sampleDictionary["false"] = 13;
    sampleDictionary["for"] = 14;
    sampleDictionary["if"] = 15;
    sampleDictionary["input"] = 16;
    sampleDictionary["integer"] = 17;
    sampleDictionary["not"] = 18;
    sampleDictionary["of"] = 19;
    sampleDictionary["or"] = 20;
    sampleDictionary["output"] = 21;
    sampleDictionary["procedure"] = 22;
    sampleDictionary["program"] = 23;
    sampleDictionary["read"] = 24;
    sampleDictionary["real"] = 25;
    sampleDictionary["repeat"] = 26;
    sampleDictionary["set"] = 27;
    sampleDictionary["stop"] = 28;
    sampleDictionary["then"] = 29;
    sampleDictionary["to"] = 30;
    sampleDictionary["true"] = 31;
    sampleDictionary["until"] = 32;
    sampleDictionary["var"] = 33;
    sampleDictionary["while"] = 34;
    sampleDictionary["write"] = 35;
}

%}

%option noyywrap

%%

[ \t]+                   { /* ignore whitespace */ }
\n                       { currRow++; }

"and"                    { return AND; }
"array"                  { return ARRAY; }
"begin"                  { return BEGIN_TOKEN; }
"bool"                   { return TOKEN_BOOL; }
"call"                   { return CALL; }
"case"                   { return CASE; }
"char"                   { return TOKEN_CHAR; }
"constant"               { return CONSTANT; }
"dim"                    { return DIM; }
"do"                     { return DO; }
"else"                   { return ELSE; }
"end"                    { return END; }
"false"                  { return FALSE_TOKEN; }
"for"                    { return FOR; }
"if"                     { return IF; }
"input"                  { return TOKEN_INPUT; }
"integer"                { return INTEGER; }
"not"                    { return NOT; }
"of"                     { return OF; }
"or"                     { return OR; }
"output"                 { return OUTPUT; }
"procedure"              { return PROCEDURE; }
"program"                { return PROGRAM; }
"read"                   { return READ; }
"real"                   { return REAL; }
"repeat"                 { return REPEAT; }
"set"                    { return SET; }
"stop"                   { return STOP; }
"then"                   { return THEN; }
"to"                     { return TO; }
"true"                   { return TRUE_TOKEN; }
"until"                  { return UNTIL; }
"var"                    { return VAR; }
"while"                  { return WHILE; }
"write"                  { return WRITE; }

[a-zA-Z][a-zA-Z0-9]*     { 
    yylval.str = strdup(yytext); 
    return IDENTIFIER; 
}

[0-9]+                   { 
    yylval.str = strdup(yytext); 
    return NUMBER; 
}

":="                     { return ASSIGN; }
"="                      { return EQ; }
"<>"                     { return NE; }
"<"                      { return LT; }
"<="                     { return LE; }
">"                      { return GT; }
">="                     { return GE; }
"+"                      { return PLUS; }
"-"                      { return MINUS; }
"*"                      { return MULTIPLY; }
"/"                      { return DIVIDE; }
"("                      { return LPAREN; }
")"                      { return RPAREN; }
"["                      { return LBRACKET; }
"]"                      { return RBRACKET; }
"{"                      { return LBRACE; }
"}"                      { return RBRACE; }
";"                      { return SEMICOLON; }
":"                      { return COLON; }
","                      { return COMMA; }
"."                      { return DOT; }

.                        { /* ignore other characters */ }

%%

void yyerror(const char* s) {
    cerr << "Error: " << s << " at line " << currRow << endl;
} 