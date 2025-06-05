/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "simple.y"

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

extern int yylex();
extern void yyerror(const char* s);
extern FILE* yyin;

map<string, int> Store_Identifier;
map<string, int> Store_String;
map<string, int> Store_Int;
int total_Count = 0;

// Global variables
int _curr_index = 0;
int _curr_T = 0;
string program_name = "";

// Utility functions
string ToString(int a) {
    if (a == 0) return "0";
    string ret = "";
    while (a > 0) {
        char temp = (char)(a % 10 + '0');
        ret = temp + ret;
        a /= 10;
    }
    return ret;
}

int ToInt(string a) {
    int ret = 0;
    for(int i = 0; i < a.length(); i++) {
        if (a[i] >= '0' && a[i] <= '9') {
            ret = ret * 10 + a[i] - '0';
        }
    }
    return ret;
}

// Quaternion structure
struct Quaternion {
    string v1, v2, v3, v4;
    int index;
    Quaternion(int _index, string _v1 = "-", string _v2 = "-", string _v3 = "-", string _v4 = "-") {
        index = _index;
        v1 = _v1;
        v2 = _v2;
        v3 = _v3;
        v4 = _v4;
    }
};

vector<Quaternion> Quaternions;

// E-state for boolean expressions
struct EState {
    int selfpos;
    int _true;
    int _false;
    bool isCorrect;
    EState* _trueList;
    EState* _falseList;
    
    EState(int _index) {
        selfpos = _index;
        _true = -1;
        _false = -1;
        _trueList = NULL;
        _falseList = NULL;
        isCorrect = false;
    }
    
    EState*& GetTlist() {
        if (_trueList == NULL)
            return _trueList;
        else
            return _trueList->GetTlist();
    }
    
    EState*& GetFlist() {
        if (_falseList == NULL)
            return _falseList;
        else
            return _falseList->GetFlist();
    }
    
    void backpatch_T(int exit) {
        _true = exit;
        if (selfpos > 0 && !isCorrect) {
            Quaternions[selfpos].v4 = ToString(exit);
        }
        if (_trueList == NULL)
            return;
        else
            _trueList->backpatch_T(exit);
    }
    
    void backpatch_F(int exit) {
        _false = exit;
        if (selfpos > 0 && !isCorrect) {
            Quaternions[selfpos].v4 = ToString(exit);
        }
        if (_falseList == NULL)
            return;
        else
            _falseList->backpatch_F(exit);
    }
};

// Control flow states
struct if_State {
    EState* E;
    int pos_ElseQ;
    if_State(EState* _temp) {
        E = _temp;
        pos_ElseQ = -1;
    }
    void backpatch_T(int exit) {
        E->backpatch_T(exit);
    }
    void backpatch_F(int exit) {
        E->backpatch_F(exit);
    }
};

struct while_State {
    int Enter;
    EState* E;
    void backpatch_T(int exit) {
        E->backpatch_T(exit);
    }
    void backpatch_F(int exit) {
        E->backpatch_F(exit);
    }
    while_State(EState* _temp, int _enter) {
        E = _temp;
        Enter = _enter;
    }
};

struct repeat_State {
    int Enter;
    EState* E;
    repeat_State(int _enter) {
        Enter = _enter;
        E = NULL;
    }
    void backpatch_T(int exit) {
        if (E) E->backpatch_T(exit);
    }
    void backpatch_F(int exit) {
        if (E) E->backpatch_F(exit);
    }
};

// Stacks for control flow
stack<if_State> if_stack;
stack<while_State> while_stack;
stack<repeat_State> repeat_stack;

// Storage for EStates
vector<EState*> e_Storage;

// Variable generators
string newTemp() {
    return "T" + ToString(++_curr_T);
}

void PrintQuaternions() {
    cout << "Generated Quaternions:" << endl;
    for (int i = 0; i < Quaternions.size(); i++) {
        cout << "(" << (i < 10 ? " " : "") << i << ")  (" << Quaternions[i].v1 << ", " 
             << Quaternions[i].v2 << ", " << Quaternions[i].v3 << ", " 
             << Quaternions[i].v4 << ")" << endl;
    }
}

void addQuaternion(string op, string arg1 = "-", string arg2 = "-", string result = "-") {
    Quaternions.push_back(Quaternion(_curr_index++, op, arg1, arg2, result));
}


#line 262 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 444 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_NUMBER = 4,                     /* NUMBER  */
  YYSYMBOL_AND = 5,                        /* AND  */
  YYSYMBOL_ARRAY = 6,                      /* ARRAY  */
  YYSYMBOL_BEGIN_TOKEN = 7,                /* BEGIN_TOKEN  */
  YYSYMBOL_TOKEN_BOOL = 8,                 /* TOKEN_BOOL  */
  YYSYMBOL_CALL = 9,                       /* CALL  */
  YYSYMBOL_CASE = 10,                      /* CASE  */
  YYSYMBOL_TOKEN_CHAR = 11,                /* TOKEN_CHAR  */
  YYSYMBOL_CONSTANT = 12,                  /* CONSTANT  */
  YYSYMBOL_DIM = 13,                       /* DIM  */
  YYSYMBOL_DO = 14,                        /* DO  */
  YYSYMBOL_ELSE = 15,                      /* ELSE  */
  YYSYMBOL_END = 16,                       /* END  */
  YYSYMBOL_FALSE_TOKEN = 17,               /* FALSE_TOKEN  */
  YYSYMBOL_FOR = 18,                       /* FOR  */
  YYSYMBOL_IF = 19,                        /* IF  */
  YYSYMBOL_TOKEN_INPUT = 20,               /* TOKEN_INPUT  */
  YYSYMBOL_INTEGER = 21,                   /* INTEGER  */
  YYSYMBOL_NOT = 22,                       /* NOT  */
  YYSYMBOL_OF = 23,                        /* OF  */
  YYSYMBOL_OR = 24,                        /* OR  */
  YYSYMBOL_OUTPUT = 25,                    /* OUTPUT  */
  YYSYMBOL_PROCEDURE = 26,                 /* PROCEDURE  */
  YYSYMBOL_PROGRAM = 27,                   /* PROGRAM  */
  YYSYMBOL_READ = 28,                      /* READ  */
  YYSYMBOL_REAL = 29,                      /* REAL  */
  YYSYMBOL_REPEAT = 30,                    /* REPEAT  */
  YYSYMBOL_SET = 31,                       /* SET  */
  YYSYMBOL_STOP = 32,                      /* STOP  */
  YYSYMBOL_THEN = 33,                      /* THEN  */
  YYSYMBOL_TO = 34,                        /* TO  */
  YYSYMBOL_TRUE_TOKEN = 35,                /* TRUE_TOKEN  */
  YYSYMBOL_UNTIL = 36,                     /* UNTIL  */
  YYSYMBOL_VAR = 37,                       /* VAR  */
  YYSYMBOL_WHILE = 38,                     /* WHILE  */
  YYSYMBOL_WRITE = 39,                     /* WRITE  */
  YYSYMBOL_ASSIGN = 40,                    /* ASSIGN  */
  YYSYMBOL_EQ = 41,                        /* EQ  */
  YYSYMBOL_NE = 42,                        /* NE  */
  YYSYMBOL_LT = 43,                        /* LT  */
  YYSYMBOL_LE = 44,                        /* LE  */
  YYSYMBOL_GT = 45,                        /* GT  */
  YYSYMBOL_GE = 46,                        /* GE  */
  YYSYMBOL_PLUS = 47,                      /* PLUS  */
  YYSYMBOL_MINUS = 48,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 49,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 50,                    /* DIVIDE  */
  YYSYMBOL_LPAREN = 51,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 52,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 53,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 54,                  /* RBRACKET  */
  YYSYMBOL_LBRACE = 55,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 56,                    /* RBRACE  */
  YYSYMBOL_SEMICOLON = 57,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 58,                     /* COLON  */
  YYSYMBOL_COMMA = 59,                     /* COMMA  */
  YYSYMBOL_DOT = 60,                       /* DOT  */
  YYSYMBOL_YYACCEPT = 61,                  /* $accept  */
  YYSYMBOL_program = 62,                   /* program  */
  YYSYMBOL_63_1 = 63,                      /* $@1  */
  YYSYMBOL_var_declarations = 64,          /* var_declarations  */
  YYSYMBOL_var_declaration_list = 65,      /* var_declaration_list  */
  YYSYMBOL_var_declaration = 66,           /* var_declaration  */
  YYSYMBOL_identifier_list = 67,           /* identifier_list  */
  YYSYMBOL_type = 68,                      /* type  */
  YYSYMBOL_compound_statement = 69,        /* compound_statement  */
  YYSYMBOL_70_2 = 70,                      /* $@2  */
  YYSYMBOL_statement_list = 71,            /* statement_list  */
  YYSYMBOL_statement = 72,                 /* statement  */
  YYSYMBOL_assignment_statement = 73,      /* assignment_statement  */
  YYSYMBOL_assignment_target = 74,         /* assignment_target  */
  YYSYMBOL_if_statement = 75,              /* if_statement  */
  YYSYMBOL_76_3 = 76,                      /* $@3  */
  YYSYMBOL_else_part = 77,                 /* else_part  */
  YYSYMBOL_78_4 = 78,                      /* $@4  */
  YYSYMBOL_while_statement = 79,           /* while_statement  */
  YYSYMBOL_80_5 = 80,                      /* $@5  */
  YYSYMBOL_81_6 = 81,                      /* $@6  */
  YYSYMBOL_repeat_statement = 82,          /* repeat_statement  */
  YYSYMBOL_83_7 = 83,                      /* $@7  */
  YYSYMBOL_condition = 84,                 /* condition  */
  YYSYMBOL_85_8 = 85,                      /* $@8  */
  YYSYMBOL_86_9 = 86,                      /* $@9  */
  YYSYMBOL_expression = 87,                /* expression  */
  YYSYMBOL_term = 88,                      /* term  */
  YYSYMBOL_factor = 89                     /* factor  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   96

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  101

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   315


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   224,   224,   224,   234,   236,   240,   241,   245,   249,
     250,   254,   254,   254,   254,   258,   258,   267,   268,   272,
     273,   274,   275,   276,   277,   281,   289,   296,   296,   327,
     329,   329,   340,   342,   340,   370,   370,   382,   403,   421,
     439,   457,   475,   493,   493,   527,   527,   557,   570,   576,
     584,   592,   598,   606,   614,   620,   625,   630
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER", "NUMBER",
  "AND", "ARRAY", "BEGIN_TOKEN", "TOKEN_BOOL", "CALL", "CASE",
  "TOKEN_CHAR", "CONSTANT", "DIM", "DO", "ELSE", "END", "FALSE_TOKEN",
  "FOR", "IF", "TOKEN_INPUT", "INTEGER", "NOT", "OF", "OR", "OUTPUT",
  "PROCEDURE", "PROGRAM", "READ", "REAL", "REPEAT", "SET", "STOP", "THEN",
  "TO", "TRUE_TOKEN", "UNTIL", "VAR", "WHILE", "WRITE", "ASSIGN", "EQ",
  "NE", "LT", "LE", "GT", "GE", "PLUS", "MINUS", "MULTIPLY", "DIVIDE",
  "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "LBRACE", "RBRACE",
  "SEMICOLON", "COLON", "COMMA", "DOT", "$accept", "program", "$@1",
  "var_declarations", "var_declaration_list", "var_declaration",
  "identifier_list", "type", "compound_statement", "$@2", "statement_list",
  "statement", "assignment_statement", "assignment_target", "if_statement",
  "$@3", "else_part", "$@4", "while_statement", "$@5", "$@6",
  "repeat_statement", "$@7", "condition", "$@8", "$@9", "expression",
  "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-51)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -10,    19,    29,   -48,   -51,   -51,    -3,    39,    37,   -51,
      39,   -51,   -33,   -51,   -13,   -51,     7,    51,     5,   -51,
     -51,   -51,   -51,   -51,    13,   -51,   -51,    -1,   -51,   -51,
     -51,    -6,   -51,   -51,    16,   -51,   -51,   -51,   -51,   -51,
     -51,    -1,    -1,     6,    47,   -18,   -51,     5,    -1,   -51,
       5,     1,   -51,    -4,    35,   -51,   -51,   -51,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,   -20,     9,
     -51,     1,    10,   -51,   -51,    -1,    -1,     5,    10,    10,
      10,    10,    10,    10,   -18,   -18,   -51,   -51,    -1,   -51,
      21,   -51,    56,    57,    14,     5,   -51,   -51,   -51,     5,
     -51
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     2,     4,     0,     0,     9,
       5,     6,     0,    15,     0,     7,     0,     0,    24,     3,
      13,    14,    11,    12,     0,    10,    26,     0,    35,    32,
      20,     0,    17,    19,     0,    21,    22,    23,     8,    55,
      56,     0,     0,     0,     0,    51,    54,    24,     0,    16,
      24,     0,    47,     0,     0,    43,    45,    27,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,     0,    25,    48,    57,     0,     0,    24,    37,    38,
      39,    40,    41,    42,    49,    50,    52,    53,     0,    33,
       0,    44,    46,    29,    36,    24,    30,    28,    34,    24,
      31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -51,   -51,   -51,   -51,   -51,    61,   -51,   -51,    66,   -51,
      49,   -50,   -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,
     -51,   -51,   -51,   -35,   -51,   -51,     4,    -5,    18
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     6,     8,    10,    11,    12,    24,    30,    18,
      31,    32,    33,    34,    35,    77,    97,    99,    36,    48,
      95,    37,    47,    43,    75,    76,    44,    45,    46
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      70,    55,    39,    40,    39,    40,    52,    53,    26,     5,
      49,    55,    13,    69,    55,    20,    88,     1,    21,    55,
      56,    41,     3,    89,    27,    16,    17,    93,    22,     4,
      56,    66,    67,    56,     7,    28,    23,    50,    56,    57,
      91,    92,     9,    29,    13,    98,    54,    19,    73,   100,
      42,    50,    71,    94,    25,    72,    51,    64,    65,    84,
      85,    55,    78,    79,    80,    81,    82,    83,    64,    65,
      38,    15,    96,    74,    14,    90,    58,    59,    60,    61,
      62,    63,    64,    65,    86,    87,     0,    74,    58,    59,
      60,    61,    62,    63,    64,    65,    68
};

static const yytype_int8 yycheck[] =
{
      50,     5,     3,     4,     3,     4,    41,    42,     3,    57,
      16,     5,     7,    48,     5,     8,    36,    27,    11,     5,
      24,    22,     3,    14,    19,    58,    59,    77,    21,     0,
      24,    49,    50,    24,    37,    30,    29,    57,    24,    33,
      75,    76,     3,    38,     7,    95,    42,    60,    52,    99,
      51,    57,    51,    88,     3,    51,    40,    47,    48,    64,
      65,     5,    58,    59,    60,    61,    62,    63,    47,    48,
      57,    10,    15,    52,     8,    71,    41,    42,    43,    44,
      45,    46,    47,    48,    66,    67,    -1,    52,    41,    42,
      43,    44,    45,    46,    47,    48,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    27,    62,     3,     0,    57,    63,    37,    64,     3,
      65,    66,    67,     7,    69,    66,    58,    59,    70,    60,
       8,    11,    21,    29,    68,     3,     3,    19,    30,    38,
      69,    71,    72,    73,    74,    75,    79,    82,    57,     3,
       4,    22,    51,    84,    87,    88,    89,    83,    80,    16,
      57,    40,    84,    84,    87,     5,    24,    33,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    71,    84,
      72,    51,    87,    52,    52,    85,    86,    76,    87,    87,
      87,    87,    87,    87,    88,    88,    89,    89,    36,    14,
      87,    84,    84,    72,    84,    81,    15,    77,    72,    78,
      72
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    61,    63,    62,    64,    64,    65,    65,    66,    67,
      67,    68,    68,    68,    68,    70,    69,    71,    71,    72,
      72,    72,    72,    72,    72,    73,    74,    76,    75,    77,
      78,    77,    80,    81,    79,    83,    82,    84,    84,    84,
      84,    84,    84,    85,    84,    86,    84,    84,    84,    87,
      87,    87,    88,    88,    88,    89,    89,    89
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     7,     0,     2,     1,     2,     4,     1,
       3,     1,     1,     1,     1,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     0,     3,     1,     0,     6,     0,
       0,     3,     0,     0,     6,     0,     5,     3,     3,     3,
       3,     3,     3,     0,     4,     0,     4,     2,     3,     3,
       3,     1,     3,     3,     1,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 224 "simple.y"
                                 {
        program_name = string((yyvsp[-1].str));
        free((yyvsp[-1].str));
    }
#line 1587 "y.tab.c"
    break;

  case 3: /* program: PROGRAM IDENTIFIER SEMICOLON $@1 var_declarations compound_statement DOT  */
#line 227 "simple.y"
                                              {
        cout << "Program parsed successfully!" << endl;
        addQuaternion("sys");
        PrintQuaternions();
    }
#line 1597 "y.tab.c"
    break;

  case 9: /* identifier_list: IDENTIFIER  */
#line 249 "simple.y"
               { free((yyvsp[0].str)); }
#line 1603 "y.tab.c"
    break;

  case 10: /* identifier_list: identifier_list COMMA IDENTIFIER  */
#line 250 "simple.y"
                                       { free((yyvsp[0].str)); }
#line 1609 "y.tab.c"
    break;

  case 15: /* $@2: %empty  */
#line 258 "simple.y"
                {
        // Add program quaternion at the beginning
        if (_curr_index == 0) {
            addQuaternion("program", program_name, "-", "-");
        }
    }
#line 1620 "y.tab.c"
    break;

  case 25: /* assignment_statement: assignment_target ASSIGN expression  */
#line 281 "simple.y"
                                        {
        addQuaternion(":=", (yyvsp[0].expr).addr, "-", (yyvsp[-2].str));
        free((yyvsp[-2].str));
        free((yyvsp[0].expr).addr);
    }
#line 1630 "y.tab.c"
    break;

  case 26: /* assignment_target: IDENTIFIER  */
#line 289 "simple.y"
               {
        (yyval.str) = strdup((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1639 "y.tab.c"
    break;

  case 27: /* $@3: %empty  */
#line 296 "simple.y"
                      {
        if_State new_if((EState*)(yyvsp[-1].estate_ptr));
        new_if.backpatch_T(_curr_index);
        if_stack.push(new_if);
    }
#line 1649 "y.tab.c"
    break;

  case 28: /* if_statement: IF condition THEN $@3 statement else_part  */
#line 300 "simple.y"
                          {
        if (!if_stack.empty()) {
            if_State& top_if = if_stack.top(); 

            if (top_if.pos_ElseQ == -1) { // No ELSE: 'IF condition THEN statement'
                int condition_false_target;
                if (!while_stack.empty() && program_name != "") { // Check program_name to ensure it's not during global var processing if any
                    condition_false_target = while_stack.top().Enter;
                } else {
                    condition_false_target = _curr_index;
                }
                top_if.backpatch_F(condition_false_target);
            } else { // Has ELSE: 'IF condition THEN statement ELSE statement'
                // top_if.pos_ElseQ is the quadruple for jumping from end of THEN over ELSE body
                int jump_over_else_target;
                if (!while_stack.empty() && program_name != "") {
                    jump_over_else_target = while_stack.top().Enter;
                } else {
                    jump_over_else_target = _curr_index; // _curr_index is after ELSE body
                }
                Quaternions[top_if.pos_ElseQ].v4 = ToString(jump_over_else_target);
            }
            if_stack.pop();
        }
    }
#line 1679 "y.tab.c"
    break;

  case 30: /* $@4: %empty  */
#line 329 "simple.y"
           {
        if (!if_stack.empty()) {
            if_State& top_if = if_stack.top();
            top_if.pos_ElseQ = _curr_index;
            addQuaternion("j", "-", "-", "-1");
            top_if.backpatch_F(_curr_index);
        }
    }
#line 1692 "y.tab.c"
    break;

  case 32: /* $@5: %empty  */
#line 340 "simple.y"
          {
        while_stack.push(while_State(NULL, _curr_index));
    }
#line 1700 "y.tab.c"
    break;

  case 33: /* $@6: %empty  */
#line 342 "simple.y"
                   {
        while_stack.top().E = (EState*)(yyvsp[-1].estate_ptr);
        while_stack.top().backpatch_T(_curr_index);
    }
#line 1709 "y.tab.c"
    break;

  case 34: /* while_statement: WHILE $@5 condition DO $@6 statement  */
#line 345 "simple.y"
                {
        addQuaternion("j", "-", "-", ToString(while_stack.top().Enter));
        
        // Determine the target for the FALSE exit of this while loop's condition.
        int false_target_addr;
        while_State this_while_attrs = while_stack.top(); 
        while_stack.pop(); // Temporarily pop current while to peek

        if (!while_stack.empty()) {
            // Nested while: false exit of current (inner) while jumps to start of OUTER while.
            false_target_addr = while_stack.top().Enter;
        } else {
            // Not nested (or outermost): false exit jumps to instruction after this loop's own jump-back.
            // _curr_index is already at this position (after the addQuaternion above).
            false_target_addr = _curr_index;
        }
        
        while_stack.push(this_while_attrs); // Restore stack before using its EState

        while_stack.top().E->backpatch_F(false_target_addr);
        while_stack.pop(); // Finally, pop this while_State.
    }
#line 1736 "y.tab.c"
    break;

  case 35: /* $@7: %empty  */
#line 370 "simple.y"
           {
        repeat_State new_repeat(_curr_index);
        repeat_stack.push(new_repeat);
    }
#line 1745 "y.tab.c"
    break;

  case 36: /* repeat_statement: REPEAT $@7 statement_list UNTIL condition  */
#line 373 "simple.y"
                                     {
        repeat_stack.top().E = (EState*)(yyvsp[0].estate_ptr);
        repeat_stack.top().backpatch_F(repeat_stack.top().Enter);
        repeat_stack.top().backpatch_T(_curr_index);
        repeat_stack.pop();
    }
#line 1756 "y.tab.c"
    break;

  case 37: /* condition: expression EQ expression  */
#line 382 "simple.y"
                             {
        // Create the main E-state container
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        // Create true jump (conditional jump)
        EState* lastT = new EState(_curr_index);
        e_Storage.push_back(lastT);
        addQuaternion("j=", (yyvsp[-2].expr).addr, (yyvsp[0].expr).addr, "-1");
        p->_trueList = lastT;
        
        // Create false jump (unconditional jump)
        EState* lastF = new EState(_curr_index);
        e_Storage.push_back(lastF);
        addQuaternion("j", "-", "-", "-1");
        p->_falseList = lastF;
        
        (yyval.estate_ptr) = (void*)p;
        free((yyvsp[-2].expr).addr);
        free((yyvsp[0].expr).addr);
    }
#line 1782 "y.tab.c"
    break;

  case 38: /* condition: expression NE expression  */
#line 403 "simple.y"
                               {
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        EState* lastT = new EState(_curr_index);
        e_Storage.push_back(lastT);
        addQuaternion("j<>", (yyvsp[-2].expr).addr, (yyvsp[0].expr).addr, "-1");
        p->_trueList = lastT;
        
        EState* lastF = new EState(_curr_index);
        e_Storage.push_back(lastF);
        addQuaternion("j", "-", "-", "-1");
        p->_falseList = lastF;
        
        (yyval.estate_ptr) = (void*)p;
        free((yyvsp[-2].expr).addr);
        free((yyvsp[0].expr).addr);
    }
#line 1805 "y.tab.c"
    break;

  case 39: /* condition: expression LT expression  */
#line 421 "simple.y"
                               {
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        EState* lastT = new EState(_curr_index);
        e_Storage.push_back(lastT);
        addQuaternion("j<", (yyvsp[-2].expr).addr, (yyvsp[0].expr).addr, "-1");
        p->_trueList = lastT;
        
        EState* lastF = new EState(_curr_index);
        e_Storage.push_back(lastF);
        addQuaternion("j", "-", "-", "-1");
        p->_falseList = lastF;
        
        (yyval.estate_ptr) = (void*)p;
        free((yyvsp[-2].expr).addr);
        free((yyvsp[0].expr).addr);
    }
#line 1828 "y.tab.c"
    break;

  case 40: /* condition: expression LE expression  */
#line 439 "simple.y"
                               {
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        EState* lastT = new EState(_curr_index);
        e_Storage.push_back(lastT);
        addQuaternion("j<=", (yyvsp[-2].expr).addr, (yyvsp[0].expr).addr, "-1");
        p->_trueList = lastT;
        
        EState* lastF = new EState(_curr_index);
        e_Storage.push_back(lastF);
        addQuaternion("j", "-", "-", "-1");
        p->_falseList = lastF;
        
        (yyval.estate_ptr) = (void*)p;
        free((yyvsp[-2].expr).addr);
        free((yyvsp[0].expr).addr);
    }
#line 1851 "y.tab.c"
    break;

  case 41: /* condition: expression GT expression  */
#line 457 "simple.y"
                               {
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        EState* lastT = new EState(_curr_index);
        e_Storage.push_back(lastT);
        addQuaternion("j>", (yyvsp[-2].expr).addr, (yyvsp[0].expr).addr, "-1");
        p->_trueList = lastT;
        
        EState* lastF = new EState(_curr_index);
        e_Storage.push_back(lastF);
        addQuaternion("j", "-", "-", "-1");
        p->_falseList = lastF;
        
        (yyval.estate_ptr) = (void*)p;
        free((yyvsp[-2].expr).addr);
        free((yyvsp[0].expr).addr);
    }
#line 1874 "y.tab.c"
    break;

  case 42: /* condition: expression GE expression  */
#line 475 "simple.y"
                               {
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        EState* lastT = new EState(_curr_index);
        e_Storage.push_back(lastT);
        addQuaternion("j>=", (yyvsp[-2].expr).addr, (yyvsp[0].expr).addr, "-1");
        p->_trueList = lastT;
        
        EState* lastF = new EState(_curr_index);
        e_Storage.push_back(lastF);
        addQuaternion("j", "-", "-", "-1");
        p->_falseList = lastF;
        
        (yyval.estate_ptr) = (void*)p;
        free((yyvsp[-2].expr).addr);
        free((yyvsp[0].expr).addr);
    }
#line 1897 "y.tab.c"
    break;

  case 43: /* $@8: %empty  */
#line 493 "simple.y"
                    {
        // For AND: backpatch first condition's true to current position
        EState* left = (EState*)(yyvsp[-1].estate_ptr);
        if (left->_trueList) {
            left->_trueList->isCorrect = true;
            Quaternions[left->_trueList->selfpos].v4 = ToString(_curr_index);
        }
    }
#line 1910 "y.tab.c"
    break;

  case 44: /* condition: condition AND $@8 condition  */
#line 500 "simple.y"
                {
        EState* left = (EState*)(yyvsp[-3].estate_ptr);
        EState* right = (EState*)(yyvsp[0].estate_ptr);
        
        // Create new combined E-state
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        // For AND: true when both are true (use right's true)
        p->_trueList = right->_trueList;
        p->_true = right->_true;
        
        // For AND: false when either is false (chain false lists properly)
        p->_falseList = left->_falseList;
        if (left->_falseList) {
            EState* current = left->_falseList;
            while (current->_falseList != NULL) {
                current = current->_falseList;
            }
            current->_falseList = right->_falseList;
        } else {
            p->_falseList = right->_falseList;
        }
        p->_false = left->_false;
        
        (yyval.estate_ptr) = (void*)p;
    }
#line 1942 "y.tab.c"
    break;

  case 45: /* $@9: %empty  */
#line 527 "simple.y"
                   {
        // For OR: backpatch first condition's false to current position  
        EState* left = (EState*)(yyvsp[-1].estate_ptr);
        if (left->_falseList) {
            left->_falseList->isCorrect = true;
            Quaternions[left->_falseList->selfpos].v4 = ToString(_curr_index);
        }
    }
#line 1955 "y.tab.c"
    break;

  case 46: /* condition: condition OR $@9 condition  */
#line 534 "simple.y"
                {
        EState* left = (EState*)(yyvsp[-3].estate_ptr);
        EState* right = (EState*)(yyvsp[0].estate_ptr);
        
        // Create new combined E-state
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        // For OR: true when either is true (chain true lists)
        p->_trueList = left->_trueList;
        if (left->_trueList && right->_trueList) {
            left->_trueList->_trueList = right->_trueList;
        } else if (!left->_trueList) {
            p->_trueList = right->_trueList;
        }
        p->_true = left->_true;
        
        // For OR: false when both are false (use right's false)
        p->_falseList = right->_falseList;
        p->_false = right->_false;
        
        (yyval.estate_ptr) = (void*)p;
    }
#line 1983 "y.tab.c"
    break;

  case 47: /* condition: NOT condition  */
#line 557 "simple.y"
                    {
        EState* orig = (EState*)(yyvsp[0].estate_ptr);
        EState* new_state = new EState(-1);
        e_Storage.push_back(new_state);
        
        // Swap true and false
        new_state->_true = orig->_false;
        new_state->_false = orig->_true;
        new_state->_trueList = orig->_falseList;
        new_state->_falseList = orig->_trueList;
        
        (yyval.estate_ptr) = (void*)new_state;
    }
#line 2001 "y.tab.c"
    break;

  case 48: /* condition: LPAREN condition RPAREN  */
#line 570 "simple.y"
                              {
        (yyval.estate_ptr) = (yyvsp[-1].estate_ptr);
    }
#line 2009 "y.tab.c"
    break;

  case 49: /* expression: expression PLUS term  */
#line 576 "simple.y"
                         {
        string temp = newTemp();
        addQuaternion("+", (yyvsp[-2].expr).addr, (yyvsp[0].expr).addr, temp);
        (yyval.expr).addr = strdup(temp.c_str());
        (yyval.expr).estate = NULL;
        free((yyvsp[-2].expr).addr);
        free((yyvsp[0].expr).addr);
    }
#line 2022 "y.tab.c"
    break;

  case 50: /* expression: expression MINUS term  */
#line 584 "simple.y"
                            {
        string temp = newTemp();
        addQuaternion("-", (yyvsp[-2].expr).addr, (yyvsp[0].expr).addr, temp);
        (yyval.expr).addr = strdup(temp.c_str());
        (yyval.expr).estate = NULL;
        free((yyvsp[-2].expr).addr);
        free((yyvsp[0].expr).addr);
    }
#line 2035 "y.tab.c"
    break;

  case 51: /* expression: term  */
#line 592 "simple.y"
           {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 2043 "y.tab.c"
    break;

  case 52: /* term: term MULTIPLY factor  */
#line 598 "simple.y"
                         {
        string temp = newTemp();
        addQuaternion("*", (yyvsp[-2].expr).addr, (yyvsp[0].expr).addr, temp);
        (yyval.expr).addr = strdup(temp.c_str());
        (yyval.expr).estate = NULL;
        free((yyvsp[-2].expr).addr);
        free((yyvsp[0].expr).addr);
    }
#line 2056 "y.tab.c"
    break;

  case 53: /* term: term DIVIDE factor  */
#line 606 "simple.y"
                         {
        string temp = newTemp();
        addQuaternion("/", (yyvsp[-2].expr).addr, (yyvsp[0].expr).addr, temp);
        (yyval.expr).addr = strdup(temp.c_str());
        (yyval.expr).estate = NULL;
        free((yyvsp[-2].expr).addr);
        free((yyvsp[0].expr).addr);
    }
#line 2069 "y.tab.c"
    break;

  case 54: /* term: factor  */
#line 614 "simple.y"
             {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 2077 "y.tab.c"
    break;

  case 55: /* factor: IDENTIFIER  */
#line 620 "simple.y"
               {
        (yyval.expr).addr = strdup((yyvsp[0].str));
        (yyval.expr).estate = NULL;
        free((yyvsp[0].str));
    }
#line 2087 "y.tab.c"
    break;

  case 56: /* factor: NUMBER  */
#line 625 "simple.y"
             {
        (yyval.expr).addr = strdup((yyvsp[0].str));
        (yyval.expr).estate = NULL;
        free((yyvsp[0].str));
    }
#line 2097 "y.tab.c"
    break;

  case 57: /* factor: LPAREN expression RPAREN  */
#line 630 "simple.y"
                               {
        (yyval.expr) = (yyvsp[-1].expr);
    }
#line 2105 "y.tab.c"
    break;


#line 2109 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 635 "simple.y"


int main(int argc, char** argv) {
    // a) Output author's information
    cout << "姓名: 郑炜诗" << endl;
    cout << "班级: 计科二班" << endl;
    cout << "学号: 202330452392" << endl;
    cout << endl; // Add a blank line for separation

    // b) Request input test program name
    char filename[256];
    if (argc > 1) { // If filename is provided as command line argument
        strncpy(filename, argv[1], sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0'; // Ensure null termination
    } else { // Otherwise, prompt user for filename
        cout << "请输入测试程序名 (例如 TEST4): ";
        cin.getline(filename, sizeof(filename));
    }

    yyin = fopen(filename, "r");
    if (!yyin) {
        cerr << "错误: 无法打开文件 " << filename << endl;
        return 1;
    }
    
    cout << "开始编译程序: " << filename << endl << endl;

    int result = yyparse();
    
    // Clean up allocated EStates
    for (auto* state : e_Storage) {
        delete state;
    }
    
    return result;
} 
