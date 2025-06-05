/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    NUMBER = 259,                  /* NUMBER  */
    AND = 260,                     /* AND  */
    ARRAY = 261,                   /* ARRAY  */
    BEGIN_TOKEN = 262,             /* BEGIN_TOKEN  */
    TOKEN_BOOL = 263,              /* TOKEN_BOOL  */
    CALL = 264,                    /* CALL  */
    CASE = 265,                    /* CASE  */
    TOKEN_CHAR = 266,              /* TOKEN_CHAR  */
    CONSTANT = 267,                /* CONSTANT  */
    DIM = 268,                     /* DIM  */
    DO = 269,                      /* DO  */
    ELSE = 270,                    /* ELSE  */
    END = 271,                     /* END  */
    FALSE_TOKEN = 272,             /* FALSE_TOKEN  */
    FOR = 273,                     /* FOR  */
    IF = 274,                      /* IF  */
    TOKEN_INPUT = 275,             /* TOKEN_INPUT  */
    INTEGER = 276,                 /* INTEGER  */
    NOT = 277,                     /* NOT  */
    OF = 278,                      /* OF  */
    OR = 279,                      /* OR  */
    OUTPUT = 280,                  /* OUTPUT  */
    PROCEDURE = 281,               /* PROCEDURE  */
    PROGRAM = 282,                 /* PROGRAM  */
    READ = 283,                    /* READ  */
    REAL = 284,                    /* REAL  */
    REPEAT = 285,                  /* REPEAT  */
    SET = 286,                     /* SET  */
    STOP = 287,                    /* STOP  */
    THEN = 288,                    /* THEN  */
    TO = 289,                      /* TO  */
    TRUE_TOKEN = 290,              /* TRUE_TOKEN  */
    UNTIL = 291,                   /* UNTIL  */
    VAR = 292,                     /* VAR  */
    WHILE = 293,                   /* WHILE  */
    WRITE = 294,                   /* WRITE  */
    ASSIGN = 295,                  /* ASSIGN  */
    EQ = 296,                      /* EQ  */
    NE = 297,                      /* NE  */
    LT = 298,                      /* LT  */
    LE = 299,                      /* LE  */
    GT = 300,                      /* GT  */
    GE = 301,                      /* GE  */
    PLUS = 302,                    /* PLUS  */
    MINUS = 303,                   /* MINUS  */
    MULTIPLY = 304,                /* MULTIPLY  */
    DIVIDE = 305,                  /* DIVIDE  */
    LPAREN = 306,                  /* LPAREN  */
    RPAREN = 307,                  /* RPAREN  */
    LBRACKET = 308,                /* LBRACKET  */
    RBRACKET = 309,                /* RBRACKET  */
    LBRACE = 310,                  /* LBRACE  */
    RBRACE = 311,                  /* RBRACE  */
    SEMICOLON = 312,               /* SEMICOLON  */
    COLON = 313,                   /* COLON  */
    COMMA = 314,                   /* COMMA  */
    DOT = 315                      /* DOT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IDENTIFIER 258
#define NUMBER 259
#define AND 260
#define ARRAY 261
#define BEGIN_TOKEN 262
#define TOKEN_BOOL 263
#define CALL 264
#define CASE 265
#define TOKEN_CHAR 266
#define CONSTANT 267
#define DIM 268
#define DO 269
#define ELSE 270
#define END 271
#define FALSE_TOKEN 272
#define FOR 273
#define IF 274
#define TOKEN_INPUT 275
#define INTEGER 276
#define NOT 277
#define OF 278
#define OR 279
#define OUTPUT 280
#define PROCEDURE 281
#define PROGRAM 282
#define READ 283
#define REAL 284
#define REPEAT 285
#define SET 286
#define STOP 287
#define THEN 288
#define TO 289
#define TRUE_TOKEN 290
#define UNTIL 291
#define VAR 292
#define WHILE 293
#define WRITE 294
#define ASSIGN 295
#define EQ 296
#define NE 297
#define LT 298
#define LE 299
#define GT 300
#define GE 301
#define PLUS 302
#define MINUS 303
#define MULTIPLY 304
#define DIVIDE 305
#define LPAREN 306
#define RPAREN 307
#define LBRACKET 308
#define RBRACKET 309
#define LBRACE 310
#define RBRACE 311
#define SEMICOLON 312
#define COLON 313
#define COMMA 314
#define DOT 315

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 192 "simple.y"

    char* str;
    struct {
        char* addr;
        void* estate;
    } expr;
    void* estate_ptr;

#line 196 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
