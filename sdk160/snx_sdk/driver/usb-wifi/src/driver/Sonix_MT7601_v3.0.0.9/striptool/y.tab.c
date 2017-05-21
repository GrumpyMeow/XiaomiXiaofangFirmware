
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

#include <stdio.h>
#include <string.h>
typedef enum {
    IFDEF_IFDEF,
    IFDEF_IFNDEF,
    IFDEF_IF,
} IFDEF_TYPE;
typedef enum {
    EXPR_SCALAR,
    EXPR_FUNC,
    EXPR_UNARY,
    EXPR_BINARY,
    EXPR_TRINARY,
} EXPR_TYPE; 

typedef enum {
    OP_DEFINED,
    OP_PLUS,
    OP_MINUS,
    OP_MUL,
    OP_DIV,
    OP_LEFT_SHIFT,
    OP_RIGHT_SHIFT,
    OP_MOD,
    OP_AND,
    OP_OR,
    OP_NOT,
    OP_BIT_AND,
    OP_BIT_OR,
    OP_BIT_NOT,
    OP_INCLUSIVE,
    OP_EXCLUSIVE,
    OP_LESS,
    OP_GREAT,
    OP_EQUAL,
    OP_LE,
    OP_GE,
    OP_NOT_EQUAL,
} OP_TYPE;

typedef struct expr
{
    EXPR_TYPE type;
    OP_TYPE op;
    int value;
	int defined;
	int specified;
    struct expr *left;
    struct expr *right;
    struct expr *tri;
} EXPR;

typedef struct _symbol
{
	int  defined;
    char *name;
    char *defined_filename;
    int   defined_lineno;
    EXPR *expr;
    struct _symbol *next;
} SYMBOL;
SYMBOL *symbol_define_list = NULL;
SYMBOL *symbol_not_define_list = NULL;

typedef enum
{
    STMT_STRING,
    STMT_IFDEF,
} StatementType;

typedef struct statement
{
    StatementType type;
    struct ifdef_statement *ifdef;
    char *string;
    char *fname;
    int   lineno;
    struct statement *next;
} Statement;
Statement *g_first_stmt = 0;

typedef struct ifdef_statement
{
	int specified; // specified in xxx.conf or not
    int condition;
    IFDEF_TYPE type;
    char *ifdef_string;
    char *else_string;
    char *endif_string;
    Statement *true_stmt;
    Statement *false_stmt;
    char *fname;
    int  lineno;
} IFDEFstatement;

EXPR *symbol_get_expr(char *name);
EXPR *create_defined_expr(char *name);
void clean_ifdef(IFDEFstatement *ifdef);
void clean(Statement *stmt);
void change_file();
EXPR *create_scalar_expr(int value);
EXPR *create_unary_expr(OP_TYPE op, EXPR *_expr);
EXPR *create_binary_expr(EXPR *expr1, OP_TYPE op, EXPR *expr2);
EXPR *create_trinary_expr(EXPR *expr1, EXPR *expr2, EXPR *expr3);
int evaluate_func(OP_TYPE op, EXPR *expr);
int evaluate_unary(OP_TYPE op, EXPR *expr);
int evaluate_binary(EXPR *left, OP_TYPE op, EXPR *right);
int evaluate_trinary(EXPR *expr1, EXPR *expr2, EXPR *expr3);
int expr_evaluate(EXPR *expr);
Statement *create_statement(char *string, IFDEFstatement *ifdef);
IFDEFstatement *create_ifdef_statement(IFDEF_TYPE type, EXPR *expr, Statement *s1, Statement *s2, int has_else);
Statement *add_statement_list(Statement *list, Statement *s);
void dump_ifdef_all(FILE *fp, IFDEFstatement *ifdef);
void dump(FILE *fp, Statement *s);
void output_file(FILE *fout);

extern char *pop_ifdef_string();
extern char *pop_else_string();
extern char *pop_endif_string();
extern int  ifdef_remove;
extern int  evaluate_num;



/* Line 189 of yacc.c  */
#line 199 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     STRING_LITERAL = 259,
     STRING = 260,
     CONSTANT = 261,
     NL = 262,
     SIZEOF = 263,
     PTR_OP = 264,
     INC_OP = 265,
     DEC_OP = 266,
     LEFT_OP = 267,
     RIGHT_OP = 268,
     LE_OP = 269,
     GE_OP = 270,
     EQ_OP = 271,
     NE_OP = 272,
     AND_OP = 273,
     OR_OP = 274,
     MUL_ASSIGN = 275,
     DIV_ASSIGN = 276,
     MOD_ASSIGN = 277,
     ADD_ASSIGN = 278,
     SUB_ASSIGN = 279,
     LEFT_ASSIGN = 280,
     RIGHT_ASSIGN = 281,
     AND_ASSIGN = 282,
     XOR_ASSIGN = 283,
     OR_ASSIGN = 284,
     TYPE_NAME = 285,
     ELLIPSIS = 286,
     IFDEF = 287,
     IFNDEF = 288,
     ENDIF = 289,
     DEFINE = 290,
     DEFINED = 291,
     UNDEFINE = 292,
     IF2 = 293,
     ELSE2 = 294,
     INCLUDE = 295,
     OTHER_WORD = 296,
     MACRO_CONCAT = 297
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define STRING_LITERAL 259
#define STRING 260
#define CONSTANT 261
#define NL 262
#define SIZEOF 263
#define PTR_OP 264
#define INC_OP 265
#define DEC_OP 266
#define LEFT_OP 267
#define RIGHT_OP 268
#define LE_OP 269
#define GE_OP 270
#define EQ_OP 271
#define NE_OP 272
#define AND_OP 273
#define OR_OP 274
#define MUL_ASSIGN 275
#define DIV_ASSIGN 276
#define MOD_ASSIGN 277
#define ADD_ASSIGN 278
#define SUB_ASSIGN 279
#define LEFT_ASSIGN 280
#define RIGHT_ASSIGN 281
#define AND_ASSIGN 282
#define XOR_ASSIGN 283
#define OR_ASSIGN 284
#define TYPE_NAME 285
#define ELLIPSIS 286
#define IFDEF 287
#define IFNDEF 288
#define ENDIF 289
#define DEFINE 290
#define DEFINED 291
#define UNDEFINE 292
#define IF2 293
#define ELSE2 294
#define INCLUDE 295
#define OTHER_WORD 296
#define MACRO_CONCAT 297




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 127 "parser.y"

    char *string;
    int  num;
    double real;
    void *ptr;



/* Line 214 of yacc.c  */
#line 328 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 340 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   246

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  137

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,     2,     2,    53,    46,     2,
      43,    44,    47,    48,    45,    49,     2,    52,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    59,     2,
      54,     2,    55,    58,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    56,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    57,     2,    50,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    12,    14,    17,    21,    23,
      28,    30,    34,    36,    39,    42,    45,    48,    51,    54,
      57,    60,    63,    65,    67,    71,    75,    79,    81,    85,
      89,    91,    95,    99,   101,   105,   109,   113,   117,   119,
     123,   127,   129,   133,   135,   139,   141,   145,   147,   151,
     153,   157,   159,   165,   167,   169,   171,   172,   174,   176,
     179,   183,   188,   193,   199,   205,   212,   216,   221,   226,
     232,   238,   245,   249,   254,   259,   265,   271
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      79,     0,    -1,     3,    -1,     6,    -1,    36,    43,     3,
      44,    -1,     4,    -1,    43,    44,    -1,    43,    77,    44,
      -1,    61,    -1,    62,    43,    63,    44,    -1,    76,    -1,
      63,    45,    76,    -1,    62,    -1,    10,    64,    -1,    11,
      64,    -1,    46,    65,    -1,    47,    65,    -1,    48,    65,
      -1,    49,    65,    -1,    50,    65,    -1,    51,    65,    -1,
       8,    64,    -1,    64,    -1,    65,    -1,    66,    47,    65,
      -1,    66,    52,    65,    -1,    66,    53,    65,    -1,    66,
      -1,    67,    48,    66,    -1,    67,    49,    66,    -1,    67,
      -1,    68,    12,    67,    -1,    68,    13,    67,    -1,    68,
      -1,    69,    54,    68,    -1,    69,    55,    68,    -1,    69,
      14,    68,    -1,    69,    15,    68,    -1,    69,    -1,    70,
      16,    69,    -1,    70,    17,    69,    -1,    70,    -1,    71,
      46,    70,    -1,    71,    -1,    72,    56,    71,    -1,    72,
      -1,    73,    57,    72,    -1,    73,    -1,    74,    18,    73,
      -1,    74,    -1,    75,    19,    74,    -1,    75,    -1,    75,
      58,    77,    59,    76,    -1,    76,    -1,    81,    -1,     5,
      -1,    -1,    80,    -1,    78,    -1,    80,    78,    -1,    38,
      77,    34,    -1,    38,    77,    80,    34,    -1,    38,    77,
      39,    34,    -1,    38,    77,    80,    39,    34,    -1,    38,
      77,    39,    80,    34,    -1,    38,    77,    80,    39,    80,
      34,    -1,    32,    77,    34,    -1,    32,    77,    80,    34,
      -1,    32,    77,    39,    34,    -1,    32,    77,    80,    39,
      34,    -1,    32,    77,    39,    80,    34,    -1,    32,    77,
      80,    39,    80,    34,    -1,    33,    77,    34,    -1,    33,
      77,    80,    34,    -1,    33,    77,    39,    34,    -1,    33,
      77,    80,    39,    34,    -1,    33,    77,    39,    80,    34,
      -1,    33,    77,    80,    39,    80,    34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   181,   181,   183,   185,   187,   189,   191,   197,   199,
     217,   218,   226,   228,   230,   232,   234,   236,   238,   240,
     242,   244,   254,   263,   265,   267,   269,   274,   276,   278,
     283,   285,   287,   292,   294,   296,   298,   300,   305,   307,
     309,   314,   316,   321,   323,   328,   330,   335,   337,   342,
     344,   349,   351,   378,   645,   647,   664,   666,   670,   672,
     717,   719,   721,   723,   725,   727,   729,   731,   733,   735,
     737,   739,   741,   743,   745,   747,   749,   751
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING_LITERAL", "STRING",
  "CONSTANT", "NL", "SIZEOF", "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP",
  "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP",
  "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN",
  "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN",
  "TYPE_NAME", "ELLIPSIS", "IFDEF", "IFNDEF", "ENDIF", "DEFINE", "DEFINED",
  "UNDEFINE", "IF2", "ELSE2", "INCLUDE", "OTHER_WORD", "MACRO_CONCAT",
  "'('", "')'", "','", "'&'", "'*'", "'+'", "'-'", "'~'", "'!'", "'/'",
  "'%'", "'<'", "'>'", "'^'", "'|'", "'?'", "':'", "$accept",
  "primary_expression", "postfix_expression", "argument_expression_list",
  "unary_expression", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression", "expression",
  "precompile", "start_point", "precompile_list", "ifdef_statement", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,    40,    41,    44,    38,    42,    43,    45,
     126,    33,    47,    37,    60,    62,    94,   124,    63,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    61,    61,    61,    61,    61,    62,    62,
      63,    63,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    65,    66,    66,    66,    66,    67,    67,    67,
      68,    68,    68,    69,    69,    69,    69,    69,    70,    70,
      70,    71,    71,    72,    72,    73,    73,    74,    74,    75,
      75,    76,    76,    77,    78,    78,    79,    79,    80,    80,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     4,     1,     2,     3,     1,     4,
       1,     3,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     1,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     5,     1,     1,     1,     0,     1,     1,     2,
       3,     4,     4,     5,     5,     6,     3,     4,     4,     5,
       5,     6,     3,     4,     4,     5,     5,     6
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      56,    55,     0,     0,     0,    58,     0,    57,    54,     2,
       5,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,    12,    22,    23,    27,    30,    33,
      38,    41,    43,    45,    47,    49,    51,    53,     0,     0,
       0,     1,    59,    21,    13,    14,     0,     6,     0,    15,
      16,    17,    18,    19,    20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    66,     0,     0,    72,     0,
       0,    60,     0,     0,     0,     7,     0,    10,    24,    25,
      26,    28,    29,    31,    32,    36,    37,    34,    35,    39,
      40,    42,    44,    46,    48,    50,     0,    68,     0,    67,
       0,    74,     0,    73,     0,    62,     0,    61,     0,     4,
       9,     0,     0,    70,    69,     0,    76,    75,     0,    64,
      63,     0,    11,    52,    71,    77,    65
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    23,    24,    86,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,     5,     6,
       7,     8
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -55
static const yytype_int16 yypact[] =
{
      78,   -55,    14,    14,    14,   -55,    10,    78,   -55,   -55,
     -55,   -55,    14,    14,    14,   -31,     5,    14,    14,    14,
      14,    14,    14,   -55,   -29,   -55,   -55,   -26,   -11,    46,
      17,    68,   -23,   -17,   -15,    27,   -14,   -55,    61,    64,
      74,   -55,   -55,   -55,   -55,   -55,    44,   -55,    31,   -55,
     -55,   -55,   -55,   -55,   -55,    14,    14,    14,    14,    14,
      14,    14,    14,    14,    14,    14,    14,    14,    14,    14,
      14,    14,    14,    14,    14,   -55,   123,    99,   -55,   130,
     109,   -55,   144,   112,    48,   -55,    36,   -55,   -55,   -55,
     -55,   -26,   -26,   -11,   -11,    46,    46,    46,    46,    17,
      17,    68,   -23,   -17,   -15,    27,    56,   -55,   147,   -55,
     154,   -55,   161,   -55,   164,   -55,   178,   -55,   185,   -55,
     -55,    14,    14,   -55,   -55,   195,   -55,   -55,   198,   -55,
     -55,   208,   -55,   -55,   -55,   -55,   -55
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -55,   -55,   -55,   -55,    16,    69,    60,    92,   -30,    55,
      65,    59,    87,    58,    63,   -55,   -54,     3,    -7,   -55,
     -36,   -55
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      42,    87,    77,    80,    83,    73,    39,    40,     9,    10,
      41,    11,    46,    12,    55,    13,    14,     9,    10,    48,
      11,    56,    12,    69,    13,    14,    57,    58,    43,    44,
      45,    63,    64,    95,    96,    97,    98,    59,    60,    70,
     108,    15,    71,   112,    74,    72,   116,    84,    16,    47,
      15,    17,    18,    19,    20,    21,    22,    16,    61,    62,
      17,    18,    19,    20,    21,    22,     1,   132,   133,     1,
      42,    65,    66,    42,   125,    85,    42,   106,   128,     1,
     120,   121,   131,     1,    67,    68,    49,    50,    51,    52,
      53,    54,   119,     2,     3,    75,     2,     3,    78,     4,
      76,    42,     4,    79,     1,    42,     2,     3,    81,    42,
       2,     3,     4,    82,     1,   122,     4,     1,    42,    91,
      92,    42,    99,   100,    42,    88,    89,    90,     1,   102,
     104,     2,     3,   109,   101,     1,   105,     4,   110,     0,
       0,     2,     3,   113,     2,     3,   117,     4,   114,     1,
       4,   118,     1,    93,    94,     2,     3,   107,   103,     1,
       0,     4,     2,     3,   111,     0,     1,     0,     4,     1,
       0,     0,     0,     0,     0,     0,     2,     3,   115,     2,
       3,   123,     4,     1,     0,     4,     2,     3,   124,     0,
       1,     0,     4,     2,     3,   126,     2,     3,   127,     4,
       1,     0,     4,     1,     0,     0,     0,     0,     0,     0,
       2,     3,   129,     1,     0,     0,     4,     2,     3,   130,
       0,     0,     0,     4,     0,     0,     0,     2,     3,   134,
       2,     3,   135,     4,     0,     0,     4,     0,     0,     0,
       2,     3,   136,     0,     0,     0,     4
};

static const yytype_int16 yycheck[] =
{
       7,    55,    38,    39,    40,    19,     3,     4,     3,     4,
       0,     6,    43,     8,    43,    10,    11,     3,     4,    16,
       6,    47,     8,    46,    10,    11,    52,    53,    12,    13,
      14,    14,    15,    63,    64,    65,    66,    48,    49,    56,
      76,    36,    57,    79,    58,    18,    82,     3,    43,    44,
      36,    46,    47,    48,    49,    50,    51,    43,    12,    13,
      46,    47,    48,    49,    50,    51,     5,   121,   122,     5,
      77,    54,    55,    80,   110,    44,    83,    74,   114,     5,
      44,    45,   118,     5,    16,    17,    17,    18,    19,    20,
      21,    22,    44,    32,    33,    34,    32,    33,    34,    38,
      39,   108,    38,    39,     5,   112,    32,    33,    34,   116,
      32,    33,    38,    39,     5,    59,    38,     5,   125,    59,
      60,   128,    67,    68,   131,    56,    57,    58,     5,    70,
      72,    32,    33,    34,    69,     5,    73,    38,    39,    -1,
      -1,    32,    33,    34,    32,    33,    34,    38,    39,     5,
      38,    39,     5,    61,    62,    32,    33,    34,    71,     5,
      -1,    38,    32,    33,    34,    -1,     5,    -1,    38,     5,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,    32,
      33,    34,    38,     5,    -1,    38,    32,    33,    34,    -1,
       5,    -1,    38,    32,    33,    34,    32,    33,    34,    38,
       5,    -1,    38,     5,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    33,    34,     5,    -1,    -1,    38,    32,    33,    34,
      -1,    -1,    -1,    38,    -1,    -1,    -1,    32,    33,    34,
      32,    33,    34,    38,    -1,    -1,    38,    -1,    -1,    -1,
      32,    33,    34,    -1,    -1,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    32,    33,    38,    78,    79,    80,    81,     3,
       4,     6,     8,    10,    11,    36,    43,    46,    47,    48,
      49,    50,    51,    61,    62,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    77,
      77,     0,    78,    64,    64,    64,    43,    44,    77,    65,
      65,    65,    65,    65,    65,    43,    47,    52,    53,    48,
      49,    12,    13,    14,    15,    54,    55,    16,    17,    46,
      56,    57,    18,    19,    58,    34,    39,    80,    34,    39,
      80,    34,    39,    80,     3,    44,    63,    76,    65,    65,
      65,    66,    66,    67,    67,    68,    68,    68,    68,    69,
      69,    70,    71,    72,    73,    74,    77,    34,    80,    34,
      39,    34,    80,    34,    39,    34,    80,    34,    39,    44,
      44,    45,    59,    34,    34,    80,    34,    34,    80,    34,
      34,    80,    76,    76,    34,    34,    34
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 182 "parser.y"
    { (yyval.ptr) = symbol_get_expr((yyvsp[(1) - (1)].string)); }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 184 "parser.y"
    { (yyval.ptr) = create_scalar_expr((yyvsp[(1) - (1)].num)); }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 186 "parser.y"
    { (yyval.ptr) = create_defined_expr((yyvsp[(3) - (4)].string)); }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 188 "parser.y"
    { (yyval.ptr) = 0; }
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 190 "parser.y"
    { (yyval.ptr) = 0; }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 192 "parser.y"
    { (yyval.ptr) = (yyvsp[(2) - (3)].ptr); }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 198 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 200 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (4)].ptr); }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 227 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 229 "parser.y"
    { (yyval.ptr) = 0; }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 231 "parser.y"
    { (yyval.ptr) = 0; }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 233 "parser.y"
    { (yyval.ptr) = 0; }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 235 "parser.y"
    { (yyval.ptr) = 0; }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 237 "parser.y"
    { (yyval.ptr) = create_unary_expr(OP_PLUS, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 239 "parser.y"
    { (yyval.ptr) = create_unary_expr(OP_MINUS, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 241 "parser.y"
    { (yyval.ptr) = create_unary_expr(OP_BIT_NOT, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 243 "parser.y"
    { (yyval.ptr) = create_unary_expr(OP_NOT, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 245 "parser.y"
    { (yyval.ptr) = 0; }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 255 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 264 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 266 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_MUL, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 268 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_DIV, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 270 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_MOD, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 275 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 277 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_PLUS, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 279 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_MINUS, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 284 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 286 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_LEFT_SHIFT, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 288 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_RIGHT_SHIFT, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 293 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 295 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_LESS, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 297 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_GREAT, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 299 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_LE, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 301 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_GE, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 306 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 308 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_EQUAL, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 310 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_NOT_EQUAL, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 315 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 317 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_BIT_AND, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 322 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 324 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_EXCLUSIVE, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 329 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 331 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_INCLUSIVE, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 336 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 338 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_AND, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 343 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 345 "parser.y"
    { (yyval.ptr) = create_binary_expr((yyvsp[(1) - (3)].ptr), OP_OR, (yyvsp[(3) - (3)].ptr)); }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 350 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 352 "parser.y"
    { (yyval.ptr) = create_trinary_expr((yyvsp[(1) - (5)].ptr), (yyvsp[(3) - (5)].ptr), (yyvsp[(5) - (5)].ptr)); }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 379 "parser.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 646 "parser.y"
    { (yyval.ptr) = create_statement(0, (yyvsp[(1) - (1)].ptr)); }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 648 "parser.y"
    { (yyval.ptr) = create_statement((yyvsp[(1) - (1)].string), 0); }
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 667 "parser.y"
    { g_first_stmt = (yyvsp[(1) - (1)].ptr); }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 671 "parser.y"
    { (yyval.ptr) = add_statement_list(0, (yyvsp[(1) - (1)].ptr)); }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 673 "parser.y"
    { (yyval.ptr) = add_statement_list((yyvsp[(1) - (2)].ptr), (yyvsp[(2) - (2)].ptr)); }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 718 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IF, (yyvsp[(2) - (3)].ptr), 0, 0, 0); }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 720 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IF, (yyvsp[(2) - (4)].ptr), (yyvsp[(3) - (4)].ptr), 0, 0); }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 722 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IF, (yyvsp[(2) - (4)].ptr), 0, 0, 1); }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 724 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IF, (yyvsp[(2) - (5)].ptr), (yyvsp[(3) - (5)].ptr), 0, 1); }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 726 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IF, (yyvsp[(2) - (5)].ptr), 0, (yyvsp[(4) - (5)].ptr), 1); }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 728 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IF, (yyvsp[(2) - (6)].ptr), (yyvsp[(3) - (6)].ptr), (yyvsp[(5) - (6)].ptr), 1); }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 730 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IFDEF, (yyvsp[(2) - (3)].ptr), 0, 0, 0); }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 732 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IFDEF, (yyvsp[(2) - (4)].ptr), (yyvsp[(3) - (4)].ptr), 0, 0); }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 734 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IFDEF, (yyvsp[(2) - (4)].ptr), 0, 0, 1); }
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 736 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IFDEF, (yyvsp[(2) - (5)].ptr), (yyvsp[(3) - (5)].ptr), 0, 1); }
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 738 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IFDEF, (yyvsp[(2) - (5)].ptr), 0, (yyvsp[(4) - (5)].ptr), 1); }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 740 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IFDEF, (yyvsp[(2) - (6)].ptr), (yyvsp[(3) - (6)].ptr), (yyvsp[(5) - (6)].ptr), 1); }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 742 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IFNDEF, (yyvsp[(2) - (3)].ptr), 0, 0, 0); }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 744 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IFNDEF, (yyvsp[(2) - (4)].ptr), (yyvsp[(3) - (4)].ptr), 0, 0); }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 746 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IFNDEF, (yyvsp[(2) - (4)].ptr), 0, 0, 1); }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 748 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IFNDEF, (yyvsp[(2) - (5)].ptr), (yyvsp[(3) - (5)].ptr), 0, 1); }
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 750 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IFNDEF, (yyvsp[(2) - (5)].ptr), 0, (yyvsp[(4) - (5)].ptr), 1); }
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 752 "parser.y"
    { (yyval.ptr) = create_ifdef_statement(IFDEF_IFNDEF, (yyvsp[(2) - (6)].ptr), (yyvsp[(3) - (6)].ptr), (yyvsp[(5) - (6)].ptr), 1); }
    break;



/* Line 1455 of yacc.c  */
#line 2197 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 843 "parser.y"

#include <stdio.h>

extern char yytext[];
extern FILE *yyin;
extern int column;
extern int lineno;
extern int process_include_file(char *fname);
extern char *current_file_name();

yyerror(s)
char *s;
{
    fflush(stderr);
    fprintf(stderr, "\n%*s\n%*s\n", column, "^", column, s);
    if (!current_file_name())
        return;

    fprintf(stderr, "==>%s: at line [%d]\n", 
            current_file_name(), lineno);
}
SYMBOL *symbol_lookup(char *name)
{
    SYMBOL *symbol = 0;
    //printf("===> symbol_lookup, name=%s, at L(%d)\n", name, lineno);
    for (symbol = symbol_define_list; symbol; symbol = symbol->next)
    {
        if (!strcmp(name, symbol->name))
        {
            //printf("find symbol:%s, value=%p\n", symbol->name, symbol->expr);
            return symbol;
        }
    }
    for (symbol = symbol_not_define_list; symbol; symbol = symbol->next)
    {
        if (!strcmp(name, symbol->name))
        {
            //printf("find symbol:%s, value=%p\n", symbol->name, symbol->expr);
            return symbol;
        }
    }

    //printf("Symbol(%s) not found\n", name);
    return 0;
}

void remove_symbol(char *name)
{
    SYMBOL *symbol = NULL, *prev = NULL;
    printf("===> remove_lookup\n");
    for (symbol = symbol_define_list; symbol; symbol = symbol->next)
    {
        if (!strcmp(name, symbol->name))
        {
            if (prev) 
                prev->next = symbol->next;
            else
                symbol_define_list = symbol->next;

            symbol->next = NULL;
            free(symbol->name);
            free(symbol);
            break;
        }
        prev = symbol;
    }
    printf("ERROR! can't undef symbol:%s\n", name);
    printf("<=== remove_lookup\n");

}

SYMBOL *create_symbol(char *name, int defined)
{
    SYMBOL *symbol;

    if (!name) return 0;
    symbol = symbol_lookup(name);
    if (symbol)
    {
        printf("ERROR! symbol (%s) redefined at L%d, original at L%d\n",
                name, lineno, symbol->defined_lineno);
        return NULL;
    }
    symbol = malloc(sizeof(SYMBOL));
    symbol->name = strdup(name);
    symbol->defined_lineno   = lineno;
    symbol->defined_filename = current_file_name();
    symbol->expr = 0;
	symbol->defined = defined;
	
	if (defined)
	{
		symbol->next = symbol_define_list;
		symbol_define_list = symbol;
	}
	else
	{
		symbol->next = symbol_not_define_list;
		symbol_not_define_list = symbol;
	}

    return symbol;
}

void assign_symbol(char *name, EXPR *expr)
{
    SYMBOL *symbol = create_symbol(name, 1); 

    if (!symbol)
	{
        printf("ERROR! assign null symbol(%s).\n", name);
        return;
	}
    symbol->expr = expr;
}

EXPR default_specified_expr = {
	.specified = 1,
	.defined   = 0,
    .type  = EXPR_SCALAR,
    .op    = OP_EQUAL,
    .value = 1,
    .left  = 0,
    .right = 0,
    .tri   = 0,
};

EXPR default_not_specified_expr = {
	.specified = 0,
	.defined   = 1,
    .type  = EXPR_SCALAR,
    .op    = OP_EQUAL,
    .value = 1,
    .left  = 0,
    .right = 0,
    .tri   = 0,
};


EXPR *symbol_get_expr(char *name)
{
    SYMBOL *symbol = symbol_lookup(name);
	EXPR *expr = 0;
    //printf("===> symbol_get_expr:%s\n", name);


    if (symbol)
	{
		if (!symbol->expr)
	        expr = &default_specified_expr;
		else
			expr = symbol->expr;

		expr->defined = symbol->defined;
        symbol->expr = expr;
	}
	else
	{
	    expr = &default_not_specified_expr;
	}

    return expr;
}

/*
int symbol_evaluate(char *name)
{
    SYMBOL *symbol;

    symbol = symbol_lookup(name);

    if (!symbol)
    {
        printf("ERROR! symbol %s not defined at L%d.\n", name, lineno);
        return 0;
    }
    if (!symbol->expr)
        return 0;

    return expr_evaluate(symbol->expr);
}
*/

EXPR *create_defined_expr(char *name)
{
    EXPR *expr = malloc(sizeof(EXPR));
	memset(expr, 0, sizeof(EXPR));
	//printf("create defined expr: %s\n", name);
    expr->type = EXPR_FUNC;
    expr->op = OP_DEFINED;
    expr->left = symbol_get_expr(name);
	expr->specified = expr->left->specified;
	expr->defined   = expr->left->defined;
    expr->value = 0;
    return expr;
}


EXPR *create_scalar_expr(int value)
{
    EXPR *expr = malloc(sizeof(EXPR));
	memset(expr, 0, sizeof(EXPR));
    expr->type = EXPR_SCALAR;
    expr->value = value;
	expr->defined = 1;
	if (evaluate_num)
	    expr->specified = 1;
	else
	    expr->specified = 0;
    return expr;
}

EXPR *create_unary_expr(OP_TYPE op, EXPR *_expr)
{
    EXPR *expr = (EXPR *)malloc(sizeof(EXPR));
	memset(expr, 0, sizeof(EXPR));
    expr->type = EXPR_UNARY;
    expr->op = op;
    expr->left = _expr;
	expr->specified = expr->left->specified;
	expr->defined   = expr->left->defined;
    return expr;
}

EXPR *create_binary_expr(EXPR *expr1, OP_TYPE op, EXPR *expr2)
{
    EXPR *expr = 0;

	if (!expr1 && !expr2)
	{
		printf("ERROR, invalid binary expr, at %s, L(%d)\n",
				current_file_name(), lineno);
		return 0;
	}
	expr = malloc(sizeof(EXPR));
	memset(expr, 0, sizeof(EXPR));
    expr->type = EXPR_BINARY;
    expr->op = op;
    expr->left = expr1;
    expr->right= expr2;

	if (!expr1)
	{
		expr->defined = expr2->defined;
		expr->specified = expr2->specified;
	}
	else if (!expr2)
	{
		expr->defined = expr1->defined;
		expr->specified = expr1->specified;
	}
	else
	{
		expr->defined = (expr1->defined) && (expr2->defined);
		expr->specified = (expr1->specified) && (expr2->specified);
	}
    return expr;
}

EXPR *create_trinary_expr(EXPR *expr1, EXPR *expr2, EXPR *expr3)
{
    EXPR *expr = 0;
	if (!expr1 || (!expr2 && !expr3))
	{
		printf("ERROR, invalid tri expr, at %s, L(%d)\n",
				current_file_name(), lineno);
	}
	expr = malloc(sizeof(EXPR));
	memset(expr, 0, sizeof(EXPR));
    expr->type = EXPR_TRINARY;
    expr->left = expr1;
    expr->right= expr2;
    expr->tri = expr3;
	if (!expr3)
	{
		expr->defined = expr2->defined;
		expr->specified = expr2->specified;
	}
	else if (!expr2)
	{
		expr->defined = expr3->defined;
		expr->specified = expr3->specified;
	}
	else
	{
		expr->defined = (expr2->defined) && (expr3->defined);
		expr->specified = (expr2->specified) && (expr3->specified);
	}
    return expr;
}

int evaluate_func(OP_TYPE op, EXPR *expr)
{
    int value;
    if (!expr)
    {
        printf("Invalid function evaluate (op=%d) at L%d\n", op, lineno);
        return 0;
    }

    value = expr_evaluate(expr);
    switch(op)
    {
        case OP_DEFINED:
            return expr->defined;
        default:
            printf("ERROR! unknown function op:%d, at L%d\n", (int)op, lineno);
    }
	return 0;
}

int evaluate_unary(OP_TYPE op, EXPR *expr)
{
    int value;
    if (!expr)
    {
        printf("Invalid unary evaluate (op=%d) at L%d\n", op, lineno);
        return 0;
    }

    value = expr_evaluate(expr);
    switch(op)
    {
        case OP_PLUS:
            return value;
        case OP_MINUS:
            return -value;
        case OP_NOT:
            return !value;;
        case OP_BIT_NOT:
            return ~value;
        default:
            printf("ERROR! unknown unary op:%d, at L%d\n", (int)op, lineno);
    }
}

int evaluate_binary(EXPR *left, OP_TYPE op, EXPR *right)
{
    int value, lvalue, rvalue;
    if (!left || !right)
    {
        printf("Invalid binary evaluate (op=%d) at L%d\n", op, lineno);
        return 0;
    }

    switch(op)
    {
        case OP_PLUS:
            return expr_evaluate(left) + expr_evaluate(right);
        case OP_MINUS:
            return expr_evaluate(left) - expr_evaluate(right);
        case OP_MUL:
            return expr_evaluate(left) * expr_evaluate(right);
        case OP_DIV:
            value = expr_evaluate(right);
            if (!value)
            {
                printf("ERROR! divided by zero at L%d\n", lineno);
                return 0;
            }
            return expr_evaluate(left) / value;
        case OP_LEFT_SHIFT:
            return expr_evaluate(left) << expr_evaluate(right);
        case OP_RIGHT_SHIFT:
            return expr_evaluate(left) >> expr_evaluate(right);
        case OP_MOD:
            return expr_evaluate(left) % expr_evaluate(right);
        case OP_AND:
            return expr_evaluate(left) && expr_evaluate(right);
        case OP_OR:
            return expr_evaluate(left) || expr_evaluate(right);
        case OP_BIT_AND:
            return expr_evaluate(left) & expr_evaluate(right);
        case OP_BIT_OR:
        case OP_INCLUSIVE:
            return expr_evaluate(left) | expr_evaluate(right);
        case OP_EXCLUSIVE:
            return expr_evaluate(left) ^ expr_evaluate(right);
        case OP_LESS:
            return expr_evaluate(left) < expr_evaluate(right) ? 1 : 0;
        case OP_GREAT:
			/*
			lvalue = expr_evaluate(left);
			rvalue = expr_evaluate(right);
			printf("OP_GREAT left=%d, right=%d\n", lvalue, rvalue);
			*/
            return expr_evaluate(left) > expr_evaluate(right) ? 1 : 0;
        case OP_EQUAL:
            return expr_evaluate(left) == expr_evaluate(right) ? 1 : 0;
        case OP_LE:
            return expr_evaluate(left) <= expr_evaluate(right) ? 1 : 0;
        case OP_GE:
            return expr_evaluate(left) >= expr_evaluate(right) ? 1 : 0;
        case OP_NOT_EQUAL:
            return expr_evaluate(left) != expr_evaluate(right) ? 1 : 0;
        default:
            printf("ERROR, unknown binary op:%d, at L%d\n", op, lineno);
    }

}

int evaluate_trinary(EXPR *expr1, EXPR *expr2, EXPR *expr3)
{
    int value;

    if (!expr1 || !expr2 || !expr3)
    {
        printf("Invalid trinary evaluate at L%d\n", lineno);
        return 0;
    }
    value = expr_evaluate(expr1);

    if (value != 0)
        return expr_evaluate(expr2);

    return expr_evaluate(expr3);
}

int expr_evaluate(EXPR *expr)
{
    if (!expr)
    {
        printf("Invalid expr evaluate at L%d\n", lineno);
        return 0;
    }

    switch(expr->type)
    {
        case EXPR_SCALAR:
            return expr->value;
        case EXPR_FUNC:
            return evaluate_func(expr->op, expr->left);
        case EXPR_UNARY:
            return evaluate_unary(expr->op, expr->left);
        case EXPR_BINARY:
            return evaluate_binary(expr->left, expr->op, expr->right);
        case EXPR_TRINARY:
            return evaluate_trinary(expr->left, expr->right, expr->tri);
        default:
            printf("ERROR, unknown expr type: %d, at L%d\n",expr->type, lineno); 
            return 0;
    }   
    return 0;
} 

IFDEFstatement *create_ifdef_statement(IFDEF_TYPE type, EXPR *expr, Statement *s1, Statement *s2, int has_else)
{
    IFDEFstatement *ifdef = malloc(sizeof(IFDEFstatement));

    ifdef->type = type;
    ifdef->specified = expr->specified;

	switch(type)
	{
		case IFDEF_IFDEF:
            ifdef->condition = expr->defined;
			break;
		case IFDEF_IFNDEF:
            ifdef->condition = !expr->defined;
			break;
		case IFDEF_IF:
            ifdef->condition = expr_evaluate(expr);
			break;
	}

    ifdef->true_stmt = s1;
    ifdef->false_stmt = s2;
    ifdef->ifdef_string    = pop_ifdef_string();
    if (has_else)
        ifdef->else_string = pop_else_string();
    else
        ifdef->else_string = 0;
    ifdef->endif_string    = pop_endif_string();
    ifdef->fname = current_file_name();
    ifdef->lineno = lineno;
    //printf("create ifdef: lineno=%d, endif=%s\n", lineno, ifdef->endif_string);
    return ifdef;
}

Statement *create_statement(char *string, IFDEFstatement *ifdef)
{
    Statement *stmt = malloc(sizeof(Statement));
    if (string)
    {
        stmt->type   = STMT_STRING;
        stmt->string = string;
        stmt->ifdef  = 0;
        //printf("create stmt L(%d): %s\n", lineno, stmt->string);
    }
    else
    {
        stmt->type   = STMT_IFDEF;
        stmt->string = 0;
        stmt->ifdef  = ifdef;
        //printf("create stmt L(%d): type=ifdef\n", lineno);
    }
    stmt->next = 0;
    stmt->fname = current_file_name();
    stmt->lineno = lineno;
    return stmt;
}
#if 0
char *merge_string(char *s1, char *s2)
{
    char *buf;
    if (!s1) return s2;
    if (!s2) return s1;

    buf = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(buf, s1);
    strcpy((char *)(buf+strlen(s1)), s2);
    printf("\nmerged [%s]+[%s]=%s\n", s1, s2, buf);
    free(s1);
    free(s2);
    return buf;
}
#endif

Statement *add_statement_list(Statement *list, Statement *s)
{
    Statement *tail = list, *pre = list;
    if (!list)
    {
#if 0
        if (!g_first_stmt) 
        {
            g_first_stmt = s;
            printf("first stmt=%s\n", s->string);
        }
        else
            printf("ERROR! no list, but has g_first_stmt\n");
#endif
        return s;
    }
#if 0
    if (list->string)
    {
        printf("[%s] add ", list->string);
        if (s->string)
            printf("[%s]\n", s->string);
        else
            printf("non string stmt\n");
    }
#endif
    // find the tail of stmts list
    while(tail)
    {
        pre  = tail;
        tail = tail->next;
    }
    pre->next = s;
    return list;
}


void dump_ifdef_all(FILE *fp, IFDEFstatement *ifdef)
{
	if (!ifdef->ifdef_string)
		printf("ERROR, no ifdef_string at %s, L(%d)\n", ifdef->fname, ifdef->lineno);
	fprintf(fp, "%s", ifdef->ifdef_string);
	dump(fp, ifdef->true_stmt);

	if (ifdef->else_string)
	{
		fprintf(fp, "%s", ifdef->else_string);
	    dump(fp, ifdef->false_stmt);
	}

	if (!ifdef->endif_string)
		printf("ERROR, no endif_string at %s, L(%d)\n", ifdef->fname, ifdef->lineno);
	fprintf(fp, "%s", ifdef->endif_string);
}

void dump(FILE *fp, Statement *s)
{
    IFDEFstatement *ifdef;
    if (!fp) return;

    while(s)
    {
        switch(s->type)
        {
            case STMT_STRING:
                if (!s->string)
                    printf("ERROR, no statement string at %s, L(%d)\n", s->fname, s->lineno);
                fprintf(fp, "%s", s->string);
                break;
            case STMT_IFDEF:
                ifdef = s->ifdef;
				if (!ifdef->specified) // not specified in xxx.conf
				{
					// keep all dumped
					dump_ifdef_all(fp, ifdef);
				}
				else
				{
					// specified => use condition to judge dump or not

					if (ifdef->condition)
					{
						if (!ifdef->ifdef_string)
							printf("ERROR, no ifdef_string at %s, L(%d)\n", ifdef->fname, ifdef->lineno);
						if (!ifdef_remove)
							fprintf(fp, "%s", ifdef->ifdef_string);

						dump(fp, ifdef->true_stmt);

						if (!ifdef->endif_string)
							printf("ERROR, no endif_string at %s, L(%d)\n", ifdef->fname, ifdef->lineno);
						if (!ifdef_remove)
							fprintf(fp, "%s", ifdef->endif_string);
					}
					else
					{
						//if (ifdef->else_string)
						{
							if (!ifdef->ifdef_string)
								 printf("ERROR, no not ifdef_string at %s, L(%d)\n", ifdef->fname, ifdef->lineno);
							if (!ifdef_remove)
								fprintf(fp, "%s", ifdef->ifdef_string);

							if (ifdef->else_string && !ifdef_remove)
							{
								fprintf(fp, "%s", ifdef->else_string);
							}
							dump(fp, ifdef->false_stmt);
							if (!ifdef->endif_string)
								 printf("ERROR, no not endif_string at %s, L(%d)\n", ifdef->fname, ifdef->lineno);
							if (!ifdef_remove)
								fprintf(fp, "%s", ifdef->endif_string);
						}
					} // of if(condition) else...
				} // of speficied

                break;
        }
        s = s->next;
    }
}

void clean_ifdef(IFDEFstatement *ifdef)
{
    if (!ifdef)
        return;
    //printf("clean ifdef L(%d)...\n", ifdef->lineno);
    clean(ifdef->true_stmt);
    clean(ifdef->false_stmt);

    if (ifdef->ifdef_string)
        free(ifdef->ifdef_string);
    if (ifdef->else_string)
        free(ifdef->else_string);
    if (ifdef->endif_string)
        free(ifdef->endif_string);
}

void clean(Statement *stmt)
{
	Statement *next;

    if (!stmt)
        return;
    clean_ifdef(stmt->ifdef);

    //printf("clean string(%p): L(%d)...\n", stmt->string, stmt->lineno);

    if (stmt->string)
    {
        //printf("free(%d) %s...\n", stmt->lineno, stmt->string);
        free(stmt->string);
    }
	next = stmt->next;
    //printf("clean stmt(%p) done...\n", stmt);
	free(stmt);

    clean(next);

}

void output_file(FILE *fout)
{
    //printf("\n======== DUMP ==========\n");
    dump(fout, g_first_stmt);
    clean(g_first_stmt);
    //printf("\n======= CLEAN done ====\n");
    g_first_stmt = 0;
}

main()
{
#if 0
    if (!process_file("STDIN"))
    {
        yyerror("STDIN"); // 1st include file
        return;
    }
#endif
    do {
        yyparse();
        change_file();
    } while(yyin);
    //} while(!feof(yyin));
} 


