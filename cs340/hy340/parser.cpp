/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parserFINALNOCONFLICTS.y" /* yacc.c:339  */
 
	#include "target_code.hpp"    
	using namespace std;  

#line 71 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    WHILE = 260,
    FOR = 261,
    FUNCTION = 262,
    RETURN = 263,
    BREAK = 264,
    CONTINUE = 265,
    AND = 266,
    NOT = 267,
    OR = 268,
    LOCAL = 269,
    TRUE = 270,
    FALSE = 271,
    NIL = 272,
    ISON = 273,
    PLUS = 274,
    MINUS = 275,
    STAR = 276,
    SLASH = 277,
    PERCENT = 278,
    EQUAL = 279,
    NOT_EQUAL = 280,
    PLUS_PLUS = 281,
    MINUS_MINUS = 282,
    GREATER = 283,
    LESS = 284,
    GREATER_EQUAL = 285,
    LESS_EQUAL = 286,
    INTCONST = 287,
    REALCONST = 288,
    STRING = 289,
    LEFT_BRACE = 290,
    RIGHT_BRACE = 291,
    LEFT_BRACKET = 292,
    RIGHT_BRACKET = 293,
    ARISTERI_PARENTHESI = 294,
    DEXIA_PARENTHESI = 295,
    SEMICOLON = 296,
    COMMA = 297,
    COLON = 298,
    COLON_COLON = 299,
    DOT = 300,
    DOT_DOT = 301,
    ID = 302,
    SINGLECOMMENT = 303,
    MULTICOMMENT = 304,
    UMINUS = 305
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define FOR 261
#define FUNCTION 262
#define RETURN 263
#define BREAK 264
#define CONTINUE 265
#define AND 266
#define NOT 267
#define OR 268
#define LOCAL 269
#define TRUE 270
#define FALSE 271
#define NIL 272
#define ISON 273
#define PLUS 274
#define MINUS 275
#define STAR 276
#define SLASH 277
#define PERCENT 278
#define EQUAL 279
#define NOT_EQUAL 280
#define PLUS_PLUS 281
#define MINUS_MINUS 282
#define GREATER 283
#define LESS 284
#define GREATER_EQUAL 285
#define LESS_EQUAL 286
#define INTCONST 287
#define REALCONST 288
#define STRING 289
#define LEFT_BRACE 290
#define RIGHT_BRACE 291
#define LEFT_BRACKET 292
#define RIGHT_BRACKET 293
#define ARISTERI_PARENTHESI 294
#define DEXIA_PARENTHESI 295
#define SEMICOLON 296
#define COMMA 297
#define COLON 298
#define COLON_COLON 299
#define DOT 300
#define DOT_DOT 301
#define ID 302
#define SINGLECOMMENT 303
#define MULTICOMMENT 304
#define UMINUS 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 6 "parserFINALNOCONFLICTS.y" /* yacc.c:355  */
   
	struct expr *exprValue; 
	char* strValue;
	bool Boolean;   
	long double intValue; 
	long double realValue;

#line 219 "parser.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 234 "parser.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  69
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   443

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  115
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  204

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   109,   109,   120,   121,   124,   135,   138,   139,   140,
     141,   148,   154,   155,   156,   159,   164,   193,   220,   253,
     268,   283,   298,   314,   327,   340,   353,   366,   379,   392,
     397,   397,   535,   539,   545,   564,   583,   601,   619,   636,
     641,   642,   643,   644,   647,   651,   691,   723,   733,   739,
     757,   775,   818,   833,   846,   901,   917,   918,   923,   923,
     926,   926,   967,   967,  1003,  1007,  1007,  1041,  1044,  1050,
    1055,  1078,  1083,  1086,  1089,  1089,  1113,  1113,  1127,  1127,
    1142,  1163,  1142,  1182,  1182,  1200,  1200,  1182,  1219,  1222,
    1225,  1228,  1231,  1234,  1238,  1238,  1253,  1256,  1256,  1271,
    1274,  1312,  1312,  1400,  1405,  1408,  1446,  1446,  1516,  1544,
    1557,  1557,  1614,  1614,  1625,  1625
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "FOR", "FUNCTION",
  "RETURN", "BREAK", "CONTINUE", "AND", "NOT", "OR", "LOCAL", "TRUE",
  "FALSE", "NIL", "ISON", "PLUS", "MINUS", "STAR", "SLASH", "PERCENT",
  "EQUAL", "NOT_EQUAL", "PLUS_PLUS", "MINUS_MINUS", "GREATER", "LESS",
  "GREATER_EQUAL", "LESS_EQUAL", "INTCONST", "REALCONST", "STRING",
  "LEFT_BRACE", "RIGHT_BRACE", "LEFT_BRACKET", "RIGHT_BRACKET",
  "ARISTERI_PARENTHESI", "DEXIA_PARENTHESI", "SEMICOLON", "COMMA", "COLON",
  "COLON_COLON", "DOT", "DOT_DOT", "ID", "SINGLECOMMENT", "MULTICOMMENT",
  "UMINUS", "$accept", "program", "stmt_list", "stmt", "expr",
  "assignexpr", "$@1", "term", "primary", "lvalue", "member", "call",
  "callsuffix", "normcall", "$@2", "methodcall", "$@3", "elist", "$@4",
  "expr2", "$@5", "objectdef", "objectdef_2", "indexed",
  "indexedelem_temp", "indexedelem", "$@6", "block", "$@7", "$@8",
  "funcdef", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14", "const",
  "idlist", "$@15", "idlist_temp", "$@16", "ifstmt", "ifstart", "$@17",
  "ifstmt_temp", "whilestmt", "whilestart", "$@18", "forstmt", "forstart2",
  "forstart", "$@19", "returnstmt", "$@20", "$@21", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

#define YYPACT_NINF -182

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-182)))

#define YYTABLE_NINF -113

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-113)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     102,  -182,  -182,  -182,   -31,    -6,     2,    12,   193,   -36,
    -182,  -182,  -182,   193,   -10,   -10,  -182,  -182,  -182,    -3,
    -182,   141,  -182,     7,  -182,    55,  -182,   102,   247,  -182,
    -182,  -182,    -1,  -182,   -27,  -182,   167,  -182,  -182,  -182,
    -182,    20,  -182,    21,  -182,    22,    35,  -182,    39,    40,
      42,  -182,    36,    41,   193,  -182,  -182,  -182,  -182,  -182,
      77,   -30,   -27,   -30,    49,   102,   293,    46,  -182,  -182,
    -182,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,  -182,  -182,  -182,  -182,   193,  -182,
      43,    45,  -182,  -182,  -182,   193,   193,    47,  -182,   378,
      51,    57,    54,   102,   102,   102,   193,   193,   193,   193,
      56,  -182,  -182,   270,    53,  -182,   102,  -182,    63,   399,
     399,     9,     9,  -182,  -182,  -182,   412,   412,    28,    28,
      28,    28,   193,   315,   193,  -182,  -182,   336,    64,  -182,
     193,    71,  -182,  -182,    80,  -182,   116,  -182,  -182,  -182,
     378,   378,    82,  -182,    81,    86,  -182,    63,    91,   193,
     378,  -182,    90,    92,  -182,  -182,   222,   193,  -182,    54,
     102,  -182,   193,    96,  -182,  -182,  -182,    93,  -182,   193,
     193,   378,  -182,  -182,   378,    95,  -182,   105,    56,  -182,
     104,   357,    71,  -182,  -182,   107,  -182,  -182,  -182,    96,
    -182,  -182,   105,  -182
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,   101,   106,   110,    83,   114,     0,     0,     0,     0,
      92,    93,    91,     0,     0,     0,    88,    89,    90,    78,
      70,     0,    14,     0,    45,     0,     2,     4,     0,    15,
      29,    39,    40,    48,    41,    42,    64,    12,    13,    44,
       6,     0,     7,     0,     8,     0,     0,     9,     0,     0,
       0,    80,     0,     0,     0,    10,    11,    34,    46,    33,
       0,    35,     0,    37,     0,     0,     0,     0,    47,     1,
       3,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,    30,    36,    38,     0,    58,
       0,     0,    54,    56,    57,     0,    64,     0,    74,    62,
       0,     0,    73,     0,     0,     0,    64,     0,     0,    64,
      96,    84,   113,     0,     0,    77,     4,    32,    43,    16,
      17,    18,    19,    20,    21,    22,    27,    28,    23,    25,
      24,    26,     0,     0,    64,    49,    60,     0,     0,    51,
       0,    67,    68,    69,     0,    71,   104,   105,   108,   109,
     102,   107,     0,    94,     0,     0,   115,     0,     0,    64,
      31,    50,     0,     0,    52,    53,     0,     0,    63,    73,
       0,   100,     0,    99,    81,    85,    79,     0,    59,    64,
       0,    65,    72,   103,   111,     0,    95,     0,    96,    55,
       0,     0,    67,    97,    82,     0,    61,    75,    66,    99,
      86,    98,     0,    87
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -182,  -182,   -25,   -64,    -8,  -182,  -182,  -182,  -182,     5,
    -182,     8,  -182,  -182,  -182,  -182,  -182,   -82,  -182,   -47,
    -182,  -182,  -182,  -182,   -19,    10,  -182,  -181,  -182,  -182,
     -18,  -182,  -182,  -182,  -182,  -182,  -182,  -182,   -28,  -182,
     -37,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,    29,   132,    30,    31,    32,
      33,    34,    92,    93,   134,    94,   163,   100,   141,   168,
     192,    35,    36,   101,   145,   102,   140,    37,    64,    65,
      38,   110,   187,    52,   155,   188,   202,    39,   154,   173,
     186,   199,    40,    41,    48,   171,    42,    43,    49,    44,
      45,    46,    50,    47,    53,    54
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      57,   116,    70,    67,     9,    59,   194,    88,    51,    89,
      95,    58,    96,    66,   138,    90,    91,    85,    97,    61,
      63,   203,    62,    62,   149,    86,    87,   152,    99,    60,
      75,    76,    77,   -76,    23,  -112,    88,    24,    89,   146,
     147,   148,   114,    55,    90,    91,   113,    73,    74,    75,
      76,    77,   162,    56,    68,    69,  -113,  -113,  -113,  -113,
     103,   104,   105,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   106,   177,   107,   108,
     133,   109,   112,   111,     4,   115,   118,   137,    99,   142,
     135,   158,   136,   157,   139,   143,   144,   190,    99,   150,
     151,    99,   159,   153,   165,     1,   183,     2,     3,     4,
       5,     6,     7,   167,     8,    98,     9,    10,    11,    12,
     170,   174,    13,   172,   160,   175,    99,   176,    14,    15,
     178,   179,   166,   189,    16,    17,    18,    19,   185,    20,
      19,    21,   193,    22,   196,   198,    23,   200,     4,    24,
     182,    99,     0,     8,   169,     9,    10,    11,    12,   181,
     195,    13,   201,     0,   184,     0,     0,    14,    15,     0,
       0,    99,   191,    16,    17,    18,     0,     0,    20,     8,
      21,     9,    10,    11,    12,    23,     0,    13,    24,     0,
       0,     0,     0,    14,    15,     0,     0,     0,     0,    16,
      17,    18,    98,     0,    20,     8,    21,     9,    10,    11,
      12,    23,     0,    13,    24,     0,     0,     0,     0,    14,
      15,     0,     0,     0,     0,    16,    17,    18,     0,     0,
      20,     0,    21,    71,     0,    72,     0,    23,     0,     0,
      24,    73,    74,    75,    76,    77,    78,    79,     0,     0,
      80,    81,    82,    83,     0,     0,     0,     0,    71,     0,
      72,     0,     0,     0,     0,   180,    73,    74,    75,    76,
      77,    78,    79,     0,     0,    80,    81,    82,    83,     0,
       0,    71,     0,    72,     0,     0,     0,     0,    84,    73,
      74,    75,    76,    77,    78,    79,     0,     0,    80,    81,
      82,    83,     0,     0,    71,     0,    72,     0,     0,     0,
       0,   156,    73,    74,    75,    76,    77,    78,    79,     0,
       0,    80,    81,    82,    83,     0,    71,     0,    72,     0,
       0,     0,     0,   117,    73,    74,    75,    76,    77,    78,
      79,     0,     0,    80,    81,    82,    83,    71,     0,    72,
       0,     0,     0,   161,     0,    73,    74,    75,    76,    77,
      78,    79,     0,     0,    80,    81,    82,    83,    71,     0,
      72,     0,     0,     0,   164,     0,    73,    74,    75,    76,
      77,    78,    79,     0,     0,    80,    81,    82,    83,    71,
       0,    72,     0,   197,     0,     0,     0,    73,    74,    75,
      76,    77,    78,    79,     0,     0,    80,    81,    82,    83,
    -113,     0,  -113,     0,     0,     0,     0,     0,    73,    74,
      75,    76,    77,    78,    79,     0,     0,    80,    81,    82,
      83,    73,    74,    75,    76,    77,  -113,  -113,     0,     0,
      80,    81,    82,    83
};

static const yytype_int16 yycheck[] =
{
       8,    65,    27,    21,    14,    13,   187,    37,    39,    39,
      37,    47,    39,    21,    96,    45,    46,    18,    45,    14,
      15,   202,    14,    15,   106,    26,    27,   109,    36,    39,
      21,    22,    23,    36,    44,    41,    37,    47,    39,   103,
     104,   105,    60,    41,    45,    46,    54,    19,    20,    21,
      22,    23,   134,    41,    47,     0,    28,    29,    30,    31,
      40,    40,    40,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    41,   159,    39,    39,
      88,    39,    41,    47,     7,    36,    40,    95,    96,    38,
      47,   116,    47,    40,    47,    38,    42,   179,   106,   107,
     108,   109,    39,    47,    40,     3,   170,     5,     6,     7,
       8,     9,    10,    42,    12,    35,    14,    15,    16,    17,
       4,    40,    20,    41,   132,    39,   134,    36,    26,    27,
      40,    39,   140,    40,    32,    33,    34,    35,    42,    37,
      35,    39,    47,    41,    40,   192,    44,    40,     7,    47,
     169,   159,    -1,    12,   144,    14,    15,    16,    17,   167,
     188,    20,   199,    -1,   172,    -1,    -1,    26,    27,    -1,
      -1,   179,   180,    32,    33,    34,    -1,    -1,    37,    12,
      39,    14,    15,    16,    17,    44,    -1,    20,    47,    -1,
      -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    -1,    37,    12,    39,    14,    15,    16,
      17,    44,    -1,    20,    47,    -1,    -1,    -1,    -1,    26,
      27,    -1,    -1,    -1,    -1,    32,    33,    34,    -1,    -1,
      37,    -1,    39,    11,    -1,    13,    -1,    44,    -1,    -1,
      47,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    11,    -1,
      13,    -1,    -1,    -1,    -1,    43,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    -1,
      -1,    11,    -1,    13,    -1,    -1,    -1,    -1,    41,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    -1,    -1,    11,    -1,    13,    -1,    -1,    -1,
      -1,    41,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    -1,    11,    -1,    13,    -1,
      -1,    -1,    -1,    40,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    11,    -1,    13,
      -1,    -1,    -1,    38,    -1,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    11,    -1,
      13,    -1,    -1,    -1,    38,    -1,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    11,
      -1,    13,    -1,    36,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      11,    -1,    13,    -1,    -1,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,     8,     9,    10,    12,    14,
      15,    16,    17,    20,    26,    27,    32,    33,    34,    35,
      37,    39,    41,    44,    47,    52,    53,    54,    55,    56,
      58,    59,    60,    61,    62,    72,    73,    78,    81,    88,
      93,    94,    97,    98,   100,   101,   102,   104,    95,    99,
     103,    39,    84,   105,   106,    41,    41,    55,    47,    55,
      39,    60,    62,    60,    79,    80,    55,    81,    47,     0,
      53,    11,    13,    19,    20,    21,    22,    23,    24,    25,
      28,    29,    30,    31,    41,    18,    26,    27,    37,    39,
      45,    46,    63,    64,    66,    37,    39,    45,    35,    55,
      68,    74,    76,    40,    40,    40,    41,    39,    39,    39,
      82,    47,    41,    55,    81,    36,    54,    40,    40,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    57,    55,    65,    47,    47,    55,    68,    47,
      77,    69,    38,    38,    42,    75,    54,    54,    54,    68,
      55,    55,    68,    47,    89,    85,    41,    40,    53,    39,
      55,    38,    68,    67,    38,    40,    55,    42,    70,    76,
       4,    96,    41,    90,    40,    39,    36,    68,    40,    39,
      43,    55,    75,    54,    55,    42,    91,    83,    86,    40,
      68,    55,    71,    47,    78,    89,    40,    36,    70,    92,
      40,    91,    87,    78
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      57,    56,    58,    58,    58,    58,    58,    58,    58,    58,
      59,    59,    59,    59,    59,    60,    60,    60,    60,    61,
      61,    61,    61,    62,    62,    62,    63,    63,    65,    64,
      67,    66,    69,    68,    68,    71,    70,    70,    72,    72,
      73,    74,    75,    75,    77,    76,    79,    78,    80,    78,
      82,    83,    81,    84,    85,    86,    87,    81,    88,    88,
      88,    88,    88,    88,    90,    89,    89,    92,    91,    91,
      93,    95,    94,    96,    96,    97,    99,    98,   100,   101,
     103,   102,   105,   104,   106,   104
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       0,     4,     3,     2,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     3,     1,     1,     2,     2,     1,     3,
       4,     3,     4,     4,     2,     6,     1,     1,     0,     4,
       0,     6,     0,     3,     0,     0,     4,     0,     3,     3,
       1,     2,     3,     0,     0,     6,     0,     3,     0,     5,
       0,     0,     7,     0,     0,     0,     0,    10,     1,     1,
       1,     1,     1,     1,     0,     3,     0,     0,     4,     0,
       4,     0,     4,     2,     0,     3,     0,     4,     3,     3,
       0,     6,     0,     3,     0,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 2:
#line 109 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				for(int i=0; i<quads.size(); i++)
				{
					if(quads[i].label==-1)
					{
						quads[i].label=last_jump+1;
					}
				}
				std::cout<<"program <-- stmt_list"<<std::endl;}
#line 1523 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 120 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {std::cout<<"stmt_list <-- stmt stmt_list\n";}
#line 1529 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 121 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {std::cout<<"stmt_list <-- empty"<<std::endl;}
#line 1535 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 124 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				expression_semicolon=true;
				if(if_flag)  
				{
					insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
					(yyval.exprValue) = new expr(constnum_e, "", 0, "", false, NULL);
					end_iflist.push_back(currQuad);
				}
				if(number_of_elses==0)
					if_flag=false;
				std::cout<<"stmt <-- expr;\n"; }
#line 1551 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 135 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				std::cout<<"stmt <-- ifstmt\n";
			 }
#line 1559 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 138 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {  loop_start=false;    std::cout<<"stmt <-- whilestmt\n";}
#line 1565 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 139 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {  loop_start=false;       std::cout<<"stmt <-- forstmt\n";  }
#line 1571 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 140 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {        std::cout<<"stmt <-- returnstmt\n";}
#line 1577 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 141 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				if(!loop_start)
					std::cout << "\033[1;31mERROR\033[0m" << ": Cannot use break outside a loop!" << std::endl;
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
				breaklist.push_back(currQuad);
				std::cout<<"stmt <-- BREAK SEMICOLON\n";
			}
#line 1589 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 148 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				if(!loop_start &&!for_index)
					std::cout << "\033[1;31mERROR\033[0m" << ": Cannot use continue outside a loop!" << std::endl;
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
				continuelist.push_back(currQuad);
				std::cout<<"stmt <-- CONTINUE SEMICOLON\n";}
#line 1600 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 154 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {              std::cout<<"stmt <-- block\n";	}
#line 1606 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 155 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {        std::cout<<"stmt <-- funcdef\n";}
#line 1612 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 156 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {        std::cout<<"stmt <-- ;\n";  }
#line 1618 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 159 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				(yyval.exprValue) = new expr(assignexpr_e, (yyvsp[0].exprValue)->sym, (yyvsp[0].exprValue)->numConst, (yyvsp[0].exprValue)->strConst, (yyvsp[0].exprValue)->boolConst, NULL);	    
				(yyval.exprValue)->list=(yyvsp[0].exprValue)->list;
				std::cout<<"expr <-- assignexpr\n";  
			}
#line 1628 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 164 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				if((yyvsp[-2].exprValue)->sym.size()==1 && (yyvsp[0].exprValue)->sym.size()==1)
				{
					insert_quads(new quad(if_eq, (yyvsp[-2].exprValue), new expr(constbool_e, "", 0, "", true, NULL), NULL, currQuad+2, ++currQuad));
					(yyvsp[-2].exprValue)->whilelist.push_back(currQuad);
					insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
					insert_quads(new quad(if_eq, (yyvsp[0].exprValue), new expr(constbool_e, "", 0, "", true, NULL), NULL, currQuad+2, ++currQuad));
					insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
					logic_flag2=true;
				}
				else{
				(yyval.exprValue)=new expr(boolexpr_e, "", 0, "", (yyvsp[-2].exprValue)->boolConst && (yyvsp[0].exprValue)->boolConst, NULL);
				(yyval.exprValue)->boolConst = (yyvsp[-2].exprValue)->boolConst && (yyvsp[0].exprValue)->boolConst;
				for(int i = 0; i < (yyvsp[-2].exprValue)->truelist.size(); i++){
					backpatch((yyvsp[-2].exprValue)->truelist[i], (yyvsp[-2].exprValue)->truelist[i] + 2);
				}
				(yyval.exprValue)->truelist = (yyvsp[0].exprValue)->truelist;
				for(int i=0; i<(yyvsp[-2].exprValue)->falselist.size(); i++)  //merge $1->falselist & $3->falselist
				{
					(yyval.exprValue)->falselist.push_back((yyvsp[-2].exprValue)->falselist[i]);
				}
				for(int i=0; i<(yyvsp[0].exprValue)->falselist.size(); i++)
				{
					(yyval.exprValue)->falselist.push_back((yyvsp[0].exprValue)->falselist[i]);
				}
				logic_flag=true;
				}
				std::cout<<"expr <-- expr AND expr\n";
			}
#line 1662 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 193 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {	
				if((yyvsp[-2].exprValue)->sym.size()==1 && (yyvsp[0].exprValue)->sym.size()==1)
				{
					insert_quads(new quad(if_eq, (yyvsp[-2].exprValue), new expr(constbool_e, "", 0, "", true, NULL), NULL, currQuad+2, ++currQuad));
					insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
					insert_quads(new quad(if_eq, (yyvsp[0].exprValue), new expr(constbool_e, "", 0, "", true, NULL), NULL, currQuad+2, ++currQuad));
					insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
					logic_flag2=true;	
				}
				else{	    
				(yyval.exprValue)=new expr(boolexpr_e, "", 0, "", (yyvsp[-2].exprValue)->boolConst || (yyvsp[0].exprValue)->boolConst, NULL);
				(yyval.exprValue)->boolConst = (yyvsp[-2].exprValue)->boolConst || (yyvsp[0].exprValue)->boolConst;

				for(int i = 0; i < (yyvsp[-2].exprValue)->falselist.size(); i++){
					backpatch((yyvsp[-2].exprValue)->falselist[i], (yyvsp[-2].exprValue)->falselist[i] + 1);
				}
				for(int i = 0; i < (yyvsp[-2].exprValue)->truelist.size(); i++){  //merge $1->falselist & $3->falselist
					(yyval.exprValue)->truelist.push_back((yyvsp[-2].exprValue)->truelist[i]);
				}
				for(int i = 0; i < (yyvsp[0].exprValue)->truelist.size(); i++){
					(yyval.exprValue)->truelist.push_back((yyvsp[0].exprValue)->truelist[i]);
				}	
				(yyval.exprValue)->falselist = (yyvsp[0].exprValue)->falselist;	  
				logic_flag=true;
				}
				std::cout<<"expr <-- expr OR expr\n"; 
			}
#line 1694 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 220 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
				if((yyvsp[-2].exprValue)->type == conststring_e && (yyvsp[0].exprValue)->type == conststring_e){
					cout << "***string(str) + string(str)***" << endl;
					cout<<"::"<<(yyvsp[-2].exprValue)->strConst + (yyvsp[0].exprValue)->strConst<<endl;
					(yyval.exprValue)=new expr(arithexpr_e, temp_str_1, 0, (yyvsp[-2].exprValue)->strConst + (yyvsp[0].exprValue)->strConst, false, NULL);
				}
				else if((yyvsp[-2].exprValue)->type == constnum_e && (yyvsp[0].exprValue)->type == constnum_e){
					cout << "***num(num) + num(num)***" << endl;
					(yyval.exprValue)=new expr(arithexpr_e, temp_str_1, (yyvsp[-2].exprValue)->numConst + (yyvsp[0].exprValue)->numConst, "", false, NULL);
				}
				else if((yyvsp[-2].exprValue)->type == assignexpr_e || (yyvsp[0].exprValue)->type == assignexpr_e || (yyvsp[-2].exprValue)->type == var_e || (yyvsp[0].exprValue)->type == var_e){
					if((yyvsp[-2].exprValue)->strConst.compare("") && (yyvsp[0].exprValue)->strConst.compare("")){
						cout << "***string(var) + string(var)***" << endl;
						(yyval.exprValue)=new expr(arithexpr_e, temp_str_1, 0, (yyvsp[-2].exprValue)->strConst + (yyvsp[0].exprValue)->strConst, false, NULL);
					} 
					else{
						cout << "***num(var) + num(var)***" << endl;
						(yyval.exprValue)=new expr(arithexpr_e, temp_str_1, (yyvsp[-2].exprValue)->numConst + (yyvsp[0].exprValue)->numConst, "", false, NULL);
					}
				}

				insert_quads(new quad(add, (yyval.exprValue), (yyvsp[-2].exprValue), (yyvsp[0].exprValue), -2, ++currQuad));
				std::cout<<"expr <-- expr + expr\n"; 
			 }
#line 1732 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 253 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {  
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
				(yyval.exprValue)=new expr(arithexpr_e, temp_str_1, (yyvsp[-2].exprValue)->numConst - (yyvsp[0].exprValue)->numConst, "", false, NULL);
				(yyval.exprValue)->numConst = (yyvsp[-2].exprValue)->numConst - (yyvsp[0].exprValue)->numConst;
				insert_quads(new quad(sub, (yyval.exprValue), (yyvsp[-2].exprValue), (yyvsp[0].exprValue), -2, ++currQuad));
				std::cout<<"expr <-- expr - expr\n"; 
			 }
#line 1752 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 268 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
				(yyval.exprValue)=new expr(arithexpr_e, temp_str_1, (yyvsp[-2].exprValue)->numConst * (yyvsp[0].exprValue)->numConst, "", false, NULL);
				(yyval.exprValue)->numConst = (yyvsp[-2].exprValue)->numConst * (yyvsp[0].exprValue)->numConst;
				insert_quads(new quad(mul, (yyval.exprValue), (yyvsp[-2].exprValue), (yyvsp[0].exprValue), -2, ++currQuad));	
			    std::cout<<"expr <-- expr * expr\n";  
			}
#line 1772 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 283 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {   
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
				(yyval.exprValue)=new expr(arithexpr_e, temp_str_1, (yyvsp[-2].exprValue)->numConst / (yyvsp[0].exprValue)->numConst, "", false, NULL);
				(yyval.exprValue)->numConst = (yyvsp[-2].exprValue)->numConst / (yyvsp[0].exprValue)->numConst;
				insert_quads(new quad(_div, (yyval.exprValue), (yyvsp[-2].exprValue), (yyvsp[0].exprValue), -2, ++currQuad));	
				std::cout<<"expr <-- expr / expr\n";  
			}
#line 1792 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 298 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {    
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
				int i = (int)(yyvsp[-2].exprValue)->numConst;
				int j = (int)(yyvsp[0].exprValue)->numConst;
				(yyval.exprValue)=new expr(arithexpr_e, temp_str_1, 0, "", false, NULL);
				insert_quads(new quad(mod, (yyval.exprValue), (yyvsp[-2].exprValue), (yyvsp[0].exprValue), -2, ++currQuad));
				std::cout<<"expr <-- expr % expr\n";  
			}
#line 1813 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 314 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				temp_metavlhth=true;
				(yyval.exprValue)=new expr(boolexpr_e, "", 0, "", (yyvsp[-2].exprValue)->numConst > (yyvsp[0].exprValue)->numConst, NULL);
				(yyval.exprValue)->boolConst = (yyvsp[-2].exprValue)->numConst > (yyvsp[0].exprValue)->numConst;
				(yyval.exprValue)->truelist.push_back(++currQuad);
				insert_quads(new quad(if_greatereq, (yyvsp[-2].exprValue), (yyvsp[0].exprValue), NULL, -1, currQuad));
				(yyval.exprValue)->falselist.push_back(++currQuad);
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				if((while_flag || for_flag) && !if_flag){
					while_startlist.push_back(currQuad-1);
				}
				std::cout<<"expr <-- expr > expr\n";  
			}
#line 1831 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 327 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				temp_metavlhth=true;
				(yyval.exprValue)=new expr(boolexpr_e, "", 0, "", (yyvsp[-2].exprValue)->numConst >= (yyvsp[0].exprValue)->numConst, NULL);
				(yyval.exprValue)->boolConst = (yyvsp[-2].exprValue)->numConst >= (yyvsp[0].exprValue)->numConst;
				(yyval.exprValue)->truelist.push_back(++currQuad);
				insert_quads(new quad(if_greatereq, (yyvsp[-2].exprValue), (yyvsp[0].exprValue), NULL, -1, currQuad));
				(yyval.exprValue)->falselist.push_back(++currQuad);
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				if((while_flag || for_flag) && !if_flag){
					while_startlist.push_back(currQuad-1);
				}
				std::cout<<"expr <-- expr >= expr\n"; 
			}
#line 1849 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 340 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				temp_metavlhth=true;
				(yyval.exprValue)=new expr(boolexpr_e, "", 0, "", (yyvsp[-2].exprValue)->numConst < (yyvsp[0].exprValue)->numConst, NULL);
				(yyval.exprValue)->boolConst = (yyvsp[-2].exprValue)->numConst < (yyvsp[0].exprValue)->numConst;
				(yyval.exprValue)->truelist.push_back(++currQuad);
				insert_quads(new quad(if_less, (yyvsp[-2].exprValue), (yyvsp[0].exprValue), NULL, -1, currQuad));
				(yyval.exprValue)->falselist.push_back(++currQuad);
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				if((while_flag || for_flag) && !if_flag){
					while_startlist.push_back(currQuad-1);
				}
				std::cout<<"expr <-- expr < expr\n";
			 }
#line 1867 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 353 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    { 
				temp_metavlhth=true;	
				(yyval.exprValue)=new expr(boolexpr_e, "", 0, "", (yyvsp[-2].exprValue)->numConst <= (yyvsp[0].exprValue)->numConst, NULL);
				(yyval.exprValue)->boolConst = (yyvsp[-2].exprValue)->numConst <= (yyvsp[0].exprValue)->numConst;
				(yyval.exprValue)->truelist.push_back(++currQuad);
				insert_quads(new quad(if_lesseq, (yyvsp[-2].exprValue), (yyvsp[0].exprValue), NULL, -1, currQuad));
				(yyval.exprValue)->falselist.push_back(++currQuad);
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				if((while_flag || for_flag) && !if_flag){
					while_startlist.push_back(currQuad-1);
				}
				std::cout<<"expr <-- expr <= expr\n"; 
			}
#line 1885 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 366 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {  
				temp_metavlhth=true;
				(yyval.exprValue)=new expr(boolexpr_e, "", 0, "", (yyvsp[-2].exprValue)->numConst == (yyvsp[0].exprValue)->numConst, NULL);
				(yyval.exprValue)->boolConst = (yyvsp[-2].exprValue)->numConst == (yyvsp[0].exprValue)->numConst;
				(yyval.exprValue)->truelist.push_back(++currQuad);
				insert_quads(new quad(if_eq, (yyvsp[-2].exprValue), (yyvsp[0].exprValue), NULL, -1, currQuad));
				(yyval.exprValue)->falselist.push_back(++currQuad);
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				if((while_flag || for_flag) && !if_flag){
					while_startlist.push_back(currQuad-1);
				}
				std::cout<<"expr <-- expr == expr\n"; 
			}
#line 1903 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 379 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				temp_metavlhth=true;
				(yyval.exprValue)=new expr(boolexpr_e, "", 0, "", (yyvsp[-2].exprValue)->numConst != (yyvsp[0].exprValue)->numConst, NULL);
				(yyval.exprValue)->boolConst = (yyvsp[-2].exprValue)->numConst != (yyvsp[0].exprValue)->numConst;
				(yyval.exprValue)->truelist.push_back(++currQuad);
				insert_quads(new quad(if_noteq, (yyvsp[-2].exprValue), (yyvsp[0].exprValue), NULL, -1, currQuad));
				(yyval.exprValue)->falselist.push_back(++currQuad);
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				if((while_flag || for_flag) && !if_flag){
					while_startlist.push_back(currQuad-1);
				}
				std::cout<<"expr <-- expr != expr\n"; 
			}
#line 1921 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 392 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				(yyval.exprValue) = (yyvsp[0].exprValue);
				std::cout<<"expr <-- term\n";}
#line 1929 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 397 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {if(accessed_lib){
							std::cout << "\033[1;31mERROR\033[0m"<<": Cannot access LIBRARY FUNCTION as a variable"<< std::endl;
							accessed_lib = 0;
						}
						ison = true;
						cout << "***ISON***" <<endl;
					}
#line 1941 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 403 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
						
						std::cout << "assignexpr <-- lvalue = expr" << std::endl;		
				if(!member_flag && !logic_flag && !member_flag_set && !member_flag_get){
					std::string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}
					(yyval.exprValue)=new expr(assignexpr_e, temp_str_1, (yyvsp[0].exprValue)->numConst, "", (yyvsp[0].exprValue)->boolConst, NULL);
					insert_quads(new quad(_assign, (yyval.exprValue), (yyvsp[0].exprValue), NULL, -1, ++currQuad));
					currQuad++;
					insert_quads(new quad(_assign, (yyvsp[-3].exprValue), (yyval.exprValue), NULL, -1, currQuad));
					ison = false;
				}
				else if(member_flag && !logic_flag && !member_flag_set && !member_flag_get){ 
					std::string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}		
					std::vector<std::string> result;	
					boost::split(result, string_member, boost::is_any_of("."));
					(yyval.exprValue)=new expr(tableitem_e, temp_str_1, 0, "", false, NULL);
					struct expr *ex_1 = new expr(tableitem_e, result[0], 0, "", false, NULL);
					std::ostringstream out;
					out << result[1];
					struct expr *ex_2 = new expr(conststring_e, "", 0, out.str(), false, NULL);
					cout<<" ::"<<(yyvsp[0].exprValue)->numConst<<endl;
					currQuad++;
					insert_quads(new quad(tablesetelem, ex_1, ex_2, (yyvsp[0].exprValue), -2, currQuad));
					currQuad++;
					insert_quads(new quad(tablegetelem, (yyval.exprValue), ex_1, ex_2, -2, currQuad));
					member_flag = false; 

				}
				else if(!member_flag && logic_flag && !member_flag_set && !member_flag_get){	
					int trueLabel = ++currQuad;
					int falseLabel = trueLabel + 2;
					for(int i = 0; i < (yyvsp[0].exprValue)->truelist.size(); i++){
						for(int j = 0; j < quads.size(); j++){
							if((yyvsp[0].exprValue)->truelist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = trueLabel;
							}
						}
					}
					for(int i = 0; i < (yyvsp[0].exprValue)->falselist.size(); i++){
						for(int j = 0; j < quads.size(); j++){
							if((yyvsp[0].exprValue)->falselist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = falseLabel;
							}
						}
					}
					std::string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}	
					(yyval.exprValue)=new expr(assignexpr_e, temp_str_1, 0, "", false, NULL);
					insert_quads(new quad(_assign, (yyvsp[-3].exprValue), new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, -1, trueLabel));
					currQuad++;
					cout<<"test"<<endl;
					insert_quads(new quad(jump, NULL, NULL, NULL, currQuad + 2, trueLabel + 1));
					currQuad++;
					insert_quads(new quad(_assign, (yyval.exprValue), new expr(assignexpr_e, "FALSE", 0, "", false, NULL), NULL, -1, falseLabel));
					currQuad++;
					insert_quads(new quad(_assign, (yyvsp[-3].exprValue), (yyval.exprValue), NULL, -1, currQuad));
					logic_flag = false;					
				}
				else if(!member_flag && !logic_flag && member_flag_set && !member_flag_get){
					std::string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}
					(yyval.exprValue) = new expr(tableitem_e, (yyvsp[-3].exprValue)->sym, 0, "", false, NULL);
					currQuad++;
						cout << "***SETELEM*** " << (yyvsp[0].exprValue)->type << endl;
					
					if(table_str_index.compare(""))
						insert_quads(new quad(tablesetelem, new expr(tableitem_e, (yyvsp[-3].exprValue)->sym, 0, "", false, NULL),
					new expr(conststring_e, table_str_index, table_index, "", false, NULL),(yyvsp[0].exprValue), -2, currQuad));
					else
						insert_quads(new quad(tablesetelem, new expr(tableitem_e, (yyvsp[-3].exprValue)->sym, 0, "", false, NULL),
					new expr(constnum_e, table_str_index, table_index, "", false, NULL),(yyvsp[0].exprValue), -2, currQuad));						
					
					member_flag_set = false;
				}
				else if(!member_flag && !logic_flag && member_flag_get && !member_flag_set){
					std::string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}
					(yyval.exprValue) = new expr(tableitem_e, temp_str_1, 0, "", false, NULL);
					insert_quads(new quad(tablesetelem, (yyvsp[-3].exprValue), new expr(constnum_e, "", table_index, "", false, NULL), new expr(constnum_e, (yyvsp[0].exprValue)->strConst, (yyvsp[0].exprValue)->numConst, "", false, NULL), -2,++currQuad));
					insert_quads(new quad(tablegetelem, (yyval.exprValue), (yyvsp[-3].exprValue), new expr(constnum_e, (yyvsp[0].exprValue)->strConst, table_index, "", false, NULL), -2,++currQuad));
					temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}	
					member_flag_get = false;
					ison = false;
				}
				(yyval.exprValue)->list.push_back(currQuad);
			}
#line 2077 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 535 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				(yyval.exprValue) = (yyvsp[-1].exprValue);
				std::cout <<"term <-- (expr)\n"; 
			}
#line 2086 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 539 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {   	
				(yyval.exprValue) = (yyvsp[0].exprValue);
				(yyval.exprValue)->numConst = -((yyvsp[0].exprValue)->numConst);
				insert_quads(new quad(uminus, (yyval.exprValue), new expr(constnum_e, "", -1, "", false, NULL), (yyvsp[0].exprValue), -2, ++currQuad));
			    std::cout <<"term <-- -expr\n";  
			}
#line 2097 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 545 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {  
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
				(yyval.exprValue)=new expr(boolexpr_e, temp_str_1, 0, "", !((yyvsp[0].exprValue)->boolConst), NULL);
				(yyval.exprValue)->boolConst = !((yyvsp[0].exprValue)->boolConst);
				insert_quads(new quad(if_eq, (yyvsp[0].exprValue), new expr(constbool_e, "", 0, "", false, NULL), NULL, -1, ++currQuad));
				(yyval.exprValue)->truelist.push_back(currQuad);
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
				(yyval.exprValue)->falselist.push_back(currQuad);
				logic_flag=true;
				std::cout <<"term <-- !expr\n";  
			}
#line 2121 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 564 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    { 
				assign_flag=true;
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
				(yyval.exprValue) = (yyvsp[0].exprValue);
				(yyval.exprValue)->numConst = ((yyvsp[0].exprValue)->numConst) + 1;				
				insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), (yyval.exprValue),NULL, -1, ++currQuad));
				assign_quads.push_back(currQuad);
				currQuad++;
				insert_quads(new quad(add, (yyvsp[0].exprValue), (yyvsp[0].exprValue), new expr(constnum_e, "", 1, "", false, NULL), -2, currQuad));				
				std::cout <<"term <-- ++lvalue\n";
			}
#line 2145 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 583 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {    
				(yyval.exprValue)=(yyvsp[-1].exprValue);
				assign_flag=true;
				std::string temp_str_1=new_temp_name();	
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}			
				insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), (yyval.exprValue), NULL, -1, ++currQuad));
				assign_quads.push_back(currQuad);
				currQuad++;
				insert_quads(new quad(add, (yyvsp[-1].exprValue), (yyvsp[-1].exprValue), new expr(constnum_e, "", 1, "", false, NULL), -2, currQuad));
				std::cout <<"term <-- lvalue++\n"; 
			}
#line 2168 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 601 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				assign_flag=true;
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
				(yyval.exprValue) = (yyvsp[0].exprValue);
				(yyval.exprValue)->numConst = ((yyvsp[0].exprValue)->numConst) - 1;				
				insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), (yyval.exprValue),NULL, -1, ++currQuad));
				assign_quads.push_back(currQuad);
				currQuad++;
				insert_quads(new quad(sub, (yyvsp[0].exprValue), (yyvsp[0].exprValue), new expr(constnum_e, "", 1, "", false, NULL), -2, currQuad));
				std::cout <<"term <== --lvalue\n"; }
#line 2191 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 619 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {    
				assign_flag=true;         
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
				(yyval.exprValue)=(yyvsp[-1].exprValue);						
				insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), (yyval.exprValue), NULL, -1, ++currQuad));
				assign_quads.push_back(currQuad);
				currQuad++;
				insert_quads(new quad(sub, (yyvsp[-1].exprValue), (yyvsp[-1].exprValue), new expr(constnum_e, "", 1, "", false, NULL), -2, currQuad));
				std::cout <<"term <== lvalue--\n"; }
#line 2213 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 636 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {          
							(yyval.exprValue) = (yyvsp[0].exprValue);
							std::cout<<"term <-- primary\n";    }
#line 2221 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 641 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {	    (yyval.exprValue)=(yyvsp[0].exprValue);				std::cout<<"primary <-- lvalue\n";}
#line 2227 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 642 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {		 (yyval.exprValue)=(yyvsp[0].exprValue);   		   std::cout<<"primary <-- call\n";}
#line 2233 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 643 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {  (yyval.exprValue)=(yyvsp[0].exprValue);   		  std::cout<<"primary <-- objectdef\n";}
#line 2239 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 644 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				(yyval.exprValue)=(yyvsp[-1].exprValue);
				std::cout<<"primary <-- (funcdef)\n";}
#line 2247 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 647 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {		 (yyval.exprValue)=(yyvsp[0].exprValue);	
					      std::cout<<"primary <-- const\n";}
#line 2254 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 651 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {	
					if(SymTable_LIBRARY_contains(yylval.strValue)){
						accessed_lib = 1;
						(yyval.exprValue) = new expr(var_e, yylval.strValue, 0, "", false, NULL);
					} 
					else if(SymTable_LOCAL_all_prev_scope_isActive_contains(yylval.strValue)){
						std::cout<<"current scope: "<<scope;
						std::cout << "\033[1;31mERROR\033[0m"<<": Cannot access local variable " << yylval.strValue << std::endl;
					}
					else if(scope == 0 && !SymTable_contains(yylval.strValue) && !SymTable_USERFUNCT_contains(yylval.strValue) &&
					 strcmp(global_for_val,yylval.strValue) != 0){
						SymTable_put(scope, yylineno, GLOBAL, yylval.strValue, 0, program_offset);
						program_offset++;
						(yyval.exprValue) = new expr(var_e, yylval.strValue, 0, "", false, NULL);
						SymTable_change_visibility(yylval.strValue, 0);
					}
					else if(scope != 0 && !SymTable_contains(yylval.strValue) && !SymTable_USERFUNCT_contains(yylval.strValue) &&
					 strcmp(global_for_val,yylval.strValue) != 0 && 
					 !SymTable_WHILE_FOR_IF_ELSE_contains(yylval.strValue) && !SymTable_LOCAL_prev_scope_isActive_contains(yylval.strValue)){
					if(is_function){
						SymTable_put(scope, yylineno, __LOCAL, yylval.strValue, 1, function_offset);
						function_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, yylval.strValue, 1, function_offset);
						function_offset++;							
					}
					(yyval.exprValue) = new expr(var_e, yylval.strValue, 0, "", false, NULL);
					SymTable_change_visibility(yylval.strValue, 0);						
					}
					else{
						(yyval.exprValue) = new expr(var_e, yylval.strValue, 0, "", false, NULL);					
					}
					if(global_for == 1){ 
						global_for_val = (char*)malloc(sizeof(yylval.strValue)); 
						sprintf(global_for_val, "%s",yylval.strValue);
						global_for = 0;
					}
					std::cout<<"lvalue <-- ID\n";
			}
#line 2299 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 691 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
					if(SymTable_LIBRARY_contains(yylval.strValue)){
						std::cout <<"\033[1;31mERROR\033[0m"<< ": "<< yylval.strValue <<" is a library function" << std::endl;
					}
					else if(SymTable_LOCAL_isActive_contains(yylval.strValue) && SymTable_contains(yylval.strValue)){
						(yyval.exprValue) = new expr(var_e, yylval.strValue, 0, "", false, NULL);
					}
					else if(!SymTable_contains(yylval.strValue) && strcmp(global_for_val,yylval.strValue) != 0){
						if(scope == 0){
							SymTable_put(scope, yylineno, __LOCAL, yylval.strValue, 1, function_offset);
							program_offset++;
						}
						else{
							if(is_function){
								SymTable_put(scope, yylineno, __LOCAL, yylval.strValue, 1, function_offset);
								function_offset++;
							}
							else{
								SymTable_put(scope, yylineno, __LOCAL, yylval.strValue, 1, function_offset);
								function_offset++;							
							}
						}
						(yyval.exprValue) = new expr(var_e, yylval.strValue, 0, "", false, NULL);
						SymTable_change_visibility(yylval.strValue, 0);
					}
					if(global_for == 1){
						global_for_val = (char*)malloc(sizeof(yylval.strValue)); 
						sprintf(global_for_val, "%s",yylval.strValue);
						global_for = 0;
					}
				std::cout<<"lvalue <-- LOCAL_ID\n";
			}
#line 2336 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 723 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				if(!SymTable_GLOBAL_isActive_contains(yylval.strValue)){
					std::cout <<"\033[1;31mERROR\033[0m"<< ": cannot access " << yylval.strValue << ". Not a global variable." << std::endl;
				} 
				else if(SymTable_GLOBAL_isActive_contains(yylval.strValue)){
					struct expr *e3 = new expr(var_e,yylval.strValue , 0, "", false, NULL);
					(yyval.exprValue)=e3;
				}
				std::cout<<"lvalue <-- COLON_COLON ID\n";
			}
#line 2351 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 733 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {   
					(yyval.exprValue) = (yyvsp[0].exprValue);
					
					std::cout<<"lvalue <-- member\n";}
#line 2360 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 739 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				if(SymTable_LIBRARY_contains(yylval.strValue)){
					std::cout <<"\033[1;31mERROR\033[0m"<< ": Cannot access LIBRARY FUNCTION" << yylval.strValue <<" this way."<< std::endl;
				}
				else{
					ostringstream out;
					(yyval.exprValue)=new expr(assignexpr_e, (yyvsp[-2].exprValue)->sym, 0, yylval.strValue, false, NULL);
					cout<< "**pernaei 1" <<endl;					
					out << (yyvsp[-2].exprValue)->sym << "." << yylval.strValue;
					cout<< "**pernaei 2" <<endl;
					string_member.assign(out.str());
					cout<< "**pernaei 3" <<endl;					
					ostringstream _OUT;
					_OUT << yylval.strValue; 
					member_flag = true;
				}
				std::cout<<"member <-- lvalue.ID\n";
			}
#line 2383 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 757 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
					if(ison){
						cout << "***MEMBER FLAG GET***" << endl;
						table_index=(yyvsp[-1].exprValue)->numConst;
						(yyval.exprValue) = new expr(var_e, (yyvsp[-3].exprValue)->sym, (yyvsp[-1].exprValue)->numConst, (yyvsp[-1].exprValue)->strConst, false, NULL);
						member_flag_get = true;
						ison = false;
					}
					else{
						cout << "***MEMBER FLAG SET***" << endl;
						(yyval.exprValue) = new expr(var_e, (yyvsp[-3].exprValue)->sym, (yyvsp[-1].exprValue)->numConst, (yyvsp[-1].exprValue)->strConst, false, NULL);
						//$$ = $3;
						table_index=(yyvsp[-1].exprValue)->numConst;
						table_str_index=(yyvsp[-1].exprValue)->strConst;
						member_flag_set = true;
					}
					std::cout<<"member <-- lvalue[expr] \n";
				}
#line 2406 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 775 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				if(SymTable_LIBRARY_contains(yylval.strValue)){
					std::cout <<"\033[1;31mERROR\033[0m"<< ": Cannot access LIBRARY FUNCTION" << yylval.strValue <<" this way."<< std::endl;
				}	
				else if(SymTable_GLOBAL_isActive_contains(yylval.strValue)){
					std::cout <<"\033[1;31mERROR\033[0m"<< ": Cannot access GLOBAL " << yylval.strValue <<" this way."<< std::endl;
				}
				else if((!SymTable_contains(yylval.strValue)) && (!SymTable_LIBRARY_contains(yylval.strValue))){
					if(scope == 0){
						SymTable_put(scope, yylineno, GLOBAL, yylval.strValue, 0, program_offset);
						program_offset++;
					}
					else{
						if(is_function){
							SymTable_put(scope, yylineno, __LOCAL, yylval.strValue, 1, function_offset);
							function_offset++;
						}
						else{
							SymTable_put(scope, yylineno, __LOCAL, yylval.strValue, 1, function_offset);
							function_offset++;
						}
					}
					ostringstream out;
					(yyvsp[0].exprValue)=new expr(assignexpr_e, yylval.strValue, 0, "", false, NULL);
					out << (yyvsp[-2].exprValue)->sym << "." << (yyvsp[0].exprValue)->sym;
					string temp_str_1=new_temp_name();
					string_member.assign(out.str());
					ostringstream _OUT;
					_OUT <<  "\"" << (yyvsp[0].exprValue)->sym<< "\"";
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
					(yyval.exprValue) = new expr(var_e, temp_str_1, 0, "", false, NULL);
					insert_quads(new quad(tablegetelem, (yyval.exprValue), new expr(assignexpr_e, (yyvsp[-2].exprValue)->sym, 0, "", false, NULL), new expr(assignexpr_e, _OUT.str(), 0, "", false,NULL), -2, ++currQuad));
					member_flag = true;
				}			 
				std::cout<<"member <-- call.ID \n";
			}
#line 2454 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 818 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
				(yyval.exprValue)=new expr(var_e, temp_str_1, 0, "", false, NULL);	
				insert_quads(new quad(tablegetelem, (yyval.exprValue), (yyvsp[-3].exprValue),(yyvsp[-1].exprValue), -2, ++currQuad));	
				std::cout<<"member <-- [expr] \n";}
#line 2472 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 833 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
					insert_quads(new quad(call, (yyvsp[-3].exprValue), NULL, NULL, -2, ++currQuad));
					string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}	
					insert_quads(new quad(getretval, new expr(assignexpr_e, temp_str_1, 0, "",false, NULL),NULL, NULL, -2, ++currQuad));
					std::cout<<"call <-- call(elist) \n";}
#line 2490 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 846 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
					string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}
					if(accessed_lib){
						accessed_lib = 0;
					}
					if(!method_flag && !SymTable_LIBRARY_contains((char*)(yyvsp[-1].exprValue)->sym.c_str())){
						for(int i=0; i<getretval_vector.size(); i++)
						{
							if(getretval_vector[i]->sym=="")
							{
								getretval_vector[i]->sym=(yyvsp[-1].exprValue)->sym;
							}
						}
						insert_quads(new quad(call, new expr(programfunc_e, (yyvsp[-1].exprValue)->sym, 0, "", false, NULL), NULL, NULL, -2, ++currQuad));
						if(getretval_vector.size()>0)
							(yyval.exprValue)=new expr(assignexpr_e, temp_str_1, getretval_vector[0]->numConst, "", false, NULL);
						else
							(yyval.exprValue)=new expr(assignexpr_e, temp_str_1, (yyvsp[-1].exprValue)->numConst, "", false, NULL);
					}
					else if(SymTable_LIBRARY_contains((char*)(yyvsp[-1].exprValue)->sym.c_str())){
						insert_quads(new quad(call, new expr(libraryfunc_e, (yyvsp[-1].exprValue)->sym, 0, "", false, NULL), NULL, NULL, -2, ++currQuad));
					}
					else{
						insert_quads(new quad(call, new expr(programfunc_e, (yyvsp[-1].exprValue)->sym, 0, "", false, NULL), NULL, NULL, -2, ++currQuad));
						method_flag=false;
					}
					if(getretval_vector.size()>0)
						insert_quads(new quad(getretval, new expr(assignexpr_e, getretval_vector[0]->strConst, getretval_vector[0]->numConst, "", false, NULL), new expr(assignexpr_e, temp_str_1, getretval_vector[0]->numConst, "", false, NULL), NULL, -2, ++currQuad));
					else
						insert_quads(new quad(getretval, new expr(assignexpr_e, (yyvsp[-1].exprValue)->strConst, (yyvsp[-1].exprValue)->numConst, "", false, NULL), new expr(assignexpr_e, temp_str_1, (yyvsp[-1].exprValue)->numConst, "", false, NULL), NULL, -2, ++currQuad));
 
				if(ret_flag){
					/*std::string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}*/	
					//currQuad++;
					//$$ = new expr(assignexpr_e, temp_str_1, 0, "", false, NULL);
					//insert_quads(new quad(getretval, $$, NULL, NULL, -2, currQuad));					
				}
				std::cout<<"call <-- lvalue callsuffix\n";
			}
#line 2550 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 901 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				insert_quads(new quad(call, (yyvsp[-4].exprValue), NULL, NULL, -2, ++currQuad));
					string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
					insert_quads(new quad(getretval, new expr(assignexpr_e, temp_str_1, 0, "",false, NULL),NULL, NULL, -2, ++currQuad));
					(yyval.exprValue)=(yyvsp[-4].exprValue);
				std::cout<<"call <-- (funcdef)(elist)\n";}
#line 2569 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 917 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {  std::cout<<"callsuffix <-- normcall\n";}
#line 2575 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 918 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    { 
				(yyval.exprValue)=(yyvsp[0].exprValue);
				std::cout<<"callsuffix <-- methodcall\n";}
#line 2583 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 923 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {call_func_flag = true;}
#line 2589 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 923 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {std::cout<<"normcall <-- normcall(elist)\n";}
#line 2595 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 926 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				if(SymTable_LIBRARY_contains(yylval.strValue)){
					std::cout <<"\033[1;31mERROR\033[0m"<< ": Cannot access LIBRARY FUNCTION" << yylval.strValue <<" this way."<< std::endl;
				}	
				else if(!SymTable_contains_no_scope(yylval.strValue) && !SymTable_LIBRARY_contains(yylval.strValue) && scope == 0){
					SymTable_put(scope,yylineno, USERFUNCT, yylval.strValue, 0, program_offset);
					program_offset++;
				}
				else if(!SymTable_contains_no_scope(yylval.strValue) && !SymTable_LIBRARY_contains(yylval.strValue) && scope != 0){
					SymTable_put(scope,yylineno, USERFUNCT, yylval.strValue, 1, function_offset);
					function_offset++;
				}
				
				method_string=yylval.strValue;
				method_flag=true;
			}
#line 2616 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 941 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    { // equivalent to lvalue.id(lvalue, elist)
				string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
				ostringstream _OUT;
				_OUT <<  "\"" << method_string<< "\"";
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
				(yyval.exprValue) = new expr(var_e, temp_str_1, 0, "", false, NULL);
				insert_quads(new quad(tablegetelem, (yyval.exprValue), (yyvsp[-1].exprValue), new expr(assignexpr_e, _OUT.str(), 0, "", false,NULL), -2, ++currQuad));
				insert_quads(new quad(param, new expr(assignexpr_e, (yyvsp[-1].exprValue)->sym, 0, "", false, NULL), NULL, NULL, -2, ++currQuad));
				std::cout<<"methodcall <-- ..ID(elist)\n";}
#line 2645 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 967 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {	
				if(t_create){	
					bool found = false;
					int index;
					for(int i = 0; i < indexes.size(); i++){
						if(!temp_vector[count_temps].compare(indexes[i]->sym)){
							found = true;
							index = indexes[i]->numConst;
							indexes[i]->numConst++;
							break;
						}
					}
					
					if(found){ 
						cout << "***INDEX found " << index << endl;
					insert_quads(new quad(tablesetelem, new expr(assignexpr_e, temp_vector[count_temps], 0, "", false,NULL), 
					new expr(constnum_e, "", index,"",false,NULL),
				 (yyvsp[0].exprValue), -2, ++currQuad));
					}
					else{ 
						cout << "***INDEX not found" << endl;
					insert_quads(new quad(tablesetelem, new expr(assignexpr_e, temp_vector[count_temps], 0, "", false,NULL), 
					new expr(constnum_e, "", array_index,"",false,NULL),
				 (yyvsp[0].exprValue), -2, ++currQuad));
					}
				}
				array_index++;
				
				if((method_flag || call_func_flag) && (yyvsp[0].exprValue)->strConst == "")
					insert_quads(new quad(param, new expr(constnum_e, "", (yyvsp[0].exprValue)->numConst, "", false, NULL), NULL, NULL, -2, ++currQuad));
				else if((method_flag || call_func_flag) && (yyvsp[0].exprValue)->strConst != "")
					insert_quads(new quad(param, new expr(conststring_e, "", 0, (yyvsp[0].exprValue)->strConst, false, NULL), NULL, NULL, -2, ++currQuad));
			}
#line 2683 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 999 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				t_create = false;
				std::cout<<"elist <-- expr expr2\n";
			}
#line 2692 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 1003 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {}
#line 2698 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 1007 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				if(t_create){	
					bool found = false;
					int index;
					for(int i = 0; i < indexes.size(); i++){
						if(!temp_vector[count_temps].compare(indexes[i]->sym)){
							found = true;
							index = indexes[i]->numConst;
							indexes[i]->numConst++;
							break;
						}
					}
					
					if(found){ 
						cout << "***INDEX found " << index << endl;
					insert_quads(new quad(tablesetelem, new expr(assignexpr_e, temp_vector[count_temps], 0, "", false,NULL), 
					new expr(constnum_e, "", index,"",false,NULL),
				 (yyvsp[0].exprValue), -2, ++currQuad));
					}
					else{ 
						cout << "***INDEX not found" << endl;
					insert_quads(new quad(tablesetelem, new expr(assignexpr_e, temp_vector[count_temps], 0, "", false,NULL), 
					new expr(constnum_e, "", array_index,"",false,NULL),
				 (yyvsp[0].exprValue), -2, ++currQuad));
					}
				}
				array_index++;	
				if((method_flag || call_func_flag) && (yyvsp[0].exprValue)->strConst == "")
					insert_quads(new quad(param, new expr(constnum_e, "", (yyvsp[0].exprValue)->numConst, "", false, NULL), NULL, NULL, -2, ++currQuad));
				else if((method_flag || call_func_flag) && (yyvsp[0].exprValue)->strConst != "")
					insert_quads(new quad(param, new expr(conststring_e, "", 0, (yyvsp[0].exprValue)->strConst, false, NULL), NULL, NULL, -2, ++currQuad));
			}
#line 2735 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 1038 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {

			}
#line 2743 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 1041 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {}
#line 2749 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 1044 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {	
				count_temps--;
				if(left_bracket) count_temps = 0;
				left_bracket = false;
				std::cout<<"objectdef <-- [elist]\n";
			}
#line 2760 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 1050 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				count_temps--;
				std::cout<<"objectdef <-- [indexed]\n";}
#line 2768 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 1055 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				left_bracket = true;
				count_temps = count_overall_temps;
				count_temps++;
				count_overall_temps++;
				array_index = 0;
				string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}		
				(yyval.exprValue)=new expr(newtable_e, temp_str_1, 0, "", false, NULL);
				insert_quads(new quad(tablecreate, (yyval.exprValue), NULL, NULL, -2, ++currQuad));	
				temp_tablecreate=temp_str_1;
				temp_vector.push_back(temp_str_1);
				indexes.push_back(new expr(constnum_e, temp_str_1, 0, "", false, NULL));
				t_create = true;
				cout << "objectdef_2 <-- [ " << endl;
			   }
#line 2796 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 1078 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				(yyval.exprValue)=(yyvsp[-1].exprValue);
				std::cout<<"indexed <-- indexedelem indexedelem_temp\n";}
#line 2804 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 1083 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
					
					std::cout<<"indexedelem_temp <-- ,indexedelem indexedelem_temp\n";}
#line 2812 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 1086 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {std::cout<<"indexedelem_temp<--empty"<<std::endl;}
#line 2818 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 1089 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {flag = 1;}
#line 2824 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 1089 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				flag=0;
				string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
				if(t_create==true)
				{
					(yyval.exprValue)=new expr(assignexpr_e, temp_vector[count_temps], 0, "", false,NULL);
					insert_quads(new quad(tablesetelem, (yyval.exprValue), (yyvsp[-3].exprValue), (yyvsp[-1].exprValue), -2, ++currQuad));
				}
				else{
					(yyval.exprValue)=new expr(assignexpr_e, temp_str_1, 0, "", false,NULL);
					insert_quads(new quad(tablesetelem, (yyval.exprValue), (yyvsp[-3].exprValue), (yyvsp[-1].exprValue), -2, ++currQuad));
				}
				std::cout<<"indexedelem <-- {expr:expr}\n";
				}
#line 2851 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 1113 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				scope++;
			}
#line 2859 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 1115 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				SymTable_change_visibility(c_temp_function,1); scope--;
				if(if_flag)
				{
					insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
					(yyval.exprValue) = new expr(constnum_e, "", 0, "", false, NULL);
					end_iflist.push_back(currQuad);
				}
				if(number_of_elses==0)
					if_flag=false;
				std::cout<<"block <-- {}\n";
			}
#line 2876 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 1127 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {scope++; }
#line 2882 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 1128 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				SymTable_find_by_type(__LOCAL, scope);
				SymTable_find_by_type(FORMAL, scope);
				SymTable_find_by_type(USERFUNCT, scope);
				scope--;
				while_scope = -1;
				for_scope = -1;
				if_scope = -1;
				is_function = 0;
				(yyval.exprValue)=(yyvsp[-2].exprValue);
				std::cout<<"block <-- {stmt stmt_list}\n";
			}
#line 2899 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 1142 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				is_function = 1; 
				function_offset = 0;
				char temp_str[2];
				char str_anonymous[2];
				strcpy(temp_str,"$");
				str_anonymous[0] = anonymous_count + '0';
				strcat(temp_str,str_anonymous); 
				strcpy(prev_func_id, strdup(temp_str));
				prev_scope = scope;
				prev_lineno = yylineno;
				currQuad++;
				insert_quads(new quad(funcstart, new expr(newtable_e, prev_func_id, 0, "", false, NULL), NULL, NULL, -2, currQuad));
				string s(prev_func_id);
				func_list.push_back(s);
				func_c++;
				func_flag = true;
				number_of_functions++;
				anonymous_count++; 
				scope++;
				cout << "FUNCTION (" << endl;
			}
#line 2926 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 1163 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {scope--;
			}
#line 2933 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 1164 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				 if(func_flag){
					SymTable_put(prev_scope, prev_lineno, USERFUNCT, prev_func_id, 1, function_offset);
					function_offset++;
					SymTable_change_visibility(prev_func_id,0);
					currQuad++;
					(yyval.exprValue) = new expr(programfunc_e, func_list[func_c], 0, "", false, NULL);
					func_c--;
					insert_quads(new quad(funcend, (yyval.exprValue), NULL, NULL, -2, currQuad));
					for(int i = 0; i < ret_list.size(); i++){
						backpatch(ret_list[i], currQuad);
					}
				 }
				 number_of_functions--;
			 			if(number_of_functions==0)
						 	func_flag=false;
				std::cout<<"funcdef <-- function(idlist) block\n";
			}
#line 2956 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 1182 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {is_function = 1; function_offset = 0; ret_flag = false;}
#line 2962 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 1182 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				if(SymTable_LIBRARY_contains(yytext)){std::cout <<"\033[1;31mERROR\033[0m"<< ": Redeclaration of Library function." << std::endl;}
				else if(SymTable_prev_USERFUNCT_contains(yytext)){std::cout << "\033[1;31mERROR\033[0m" << ": Redeclaration of function " << yytext << std::endl;}
				else if(SymTable_contains(yytext) && (SymTable_contains_isACTIVE(yytext) || SymTable_LOCAL_GLOBAL_isActive_contains(yytext))){
					std::cout << "\033[1;31mERROR\033[0m"<<": Redeclaration of function with existing id." << std::endl; return 0;}
				else{
					strcpy(prev_func_id2, (char*)yytext);
					prev_scope = scope;
					prev_lineno = yylineno;
					currQuad++;
					insert_quads(new quad(funcstart, new expr(newtable_e, prev_func_id2, 0, "", false, NULL), NULL, NULL, -2, currQuad));
					string s(prev_func_id2);
					func_list_2.push_back(s);
					func_c_2++;
					strcpy(c_temp_function, yylval.strValue);
					func_flag = true;
				}
			}
#line 2985 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 1200 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {scope++; number_of_functions++;}
#line 2991 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 1200 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {scope--;
			 		}
#line 2998 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 1201 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
						if(func_flag){
							SymTable_put(prev_scope, prev_lineno, USERFUNCT, prev_func_id2, 1, function_offset);
							function_offset++;
							SymTable_change_visibility(prev_func_id2,0);
							currQuad++;
							(yyval.exprValue) = new expr(programfunc_e, func_list_2[func_c_2], 0, "", false, NULL);
							func_c_2--;
							insert_quads(new quad(funcend, (yyval.exprValue), NULL, NULL, -2, currQuad));
					for(int i = 0; i < ret_list.size(); i++){
						backpatch(ret_list[i], currQuad);
					}
				 		}
						number_of_functions--;
							if(number_of_functions==0)
								func_flag=false;
				 		std::cout<<"funcdef <-- function ID(idlist) block\n";
			 		}
#line 3021 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 1219 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				(yyval.exprValue)=new expr(constnum_e, "", yylval.intValue, "", false, NULL);
				std::cout<<"const <--   INTCONST      \n";}
#line 3029 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 1222 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				(yyval.exprValue)=new expr(constnum_e, "", yylval.realValue, "", false, NULL);
				std::cout<<"const <--  REALCONST    \n";}
#line 3037 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 1225 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				(yyval.exprValue) = new expr(conststring_e, "", 0, yylval.strValue, false, NULL);
				std::cout<<"const <-- STRING     \n"; }
#line 3045 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 1228 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				(yyval.exprValue)=new expr(nil_e, "", 0, "nil", false, NULL);
				std::cout<<"const <-- NIL      \n"; }
#line 3053 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 1231 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				(yyval.exprValue)=new expr(constbool_e, "", 0, "", true, NULL);
				std::cout<<"const <-- TRUE   \n"; }
#line 3061 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 1234 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				(yyval.exprValue)=new expr(constbool_e, "", 0, "", false, NULL);
				std::cout<<"const <-- FALSE\n"; }
#line 3069 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 1238 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				if(SymTable_LIBRARY_contains(yylval.strValue)){
					std::cout <<"\033[1;31mERROR\033[0m"<< ": "<< yylval.strValue <<" is a library function" << std::endl;
				}
				else if(!SymTable_contains(yytext) && !SymTable_FORMAL_sameSCOPE_contains(yytext)) {
					SymTable_put(scope, yylineno, FORMAL, strdup(yytext), 2, formal_offset); 
					formal_offset++;
					SymTable_change_visibility(yytext,0);
					//currQuad++;
					//insert_quads(new quad(param, new expr(assignexpr_e, strdup(yytext), 0, "", false, NULL), NULL, NULL, -2, currQuad));
				}
				else{
					std::cout <<"\033[1;31mERROR\033[0m" <<": Redeclaration of formal " << yylval.strValue << std::endl;
				}
			}
#line 3089 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 1252 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {std::cout<<"idlist <-- ID idlist_temp\n";}
#line 3095 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 1256 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				if(SymTable_LIBRARY_contains(yylval.strValue)){
					std::cout <<"\033[1;31mERROR\033[0m"<< ": "<< yylval.strValue <<" is a library function" << std::endl;
				}
				else if(!SymTable_FORMAL_sameSCOPE_contains(yytext)) {
					SymTable_put(scope, yylineno, FORMAL, strdup(yytext), 2, formal_offset); 
					formal_offset++;
					SymTable_change_visibility(yytext,0);
					//currQuad++;
					//insert_quads(new quad(param, new expr(assignexpr_e, strdup(yytext), 0, "", false, NULL), NULL, NULL, -2, currQuad));
				}	
				else{
					std::cout << "\033[1;31mERROR\033[0m"<<": Redeclaration of formal " << yylval.strValue << std::endl;						
				}			
				}
#line 3115 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 1270 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {std::cout<<"idlist_temp <-- ,ID idlist_temp\n";}
#line 3121 "parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 1275 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				(yyval.exprValue) = (yyvsp[0].exprValue);
				if(number_of_elses>0) 
					number_of_elses--;
				if(number_of_elses==0) //backpatch gia otan exei ektelestei to if (h to else) kai ueloyme na pame sto telos
				{
					for(int i=0; i<end_iflist.size(); i++)
					{
						backpatch(end_iflist[i], currQuad+1);
						last_jump=end_iflist[i];
					}
				}
				if(ifstmt_flag )
				{
					if(iflist.size()==1)
					{
						backpatch(iflist[0], currQuad+1);
					}
					for(int i = 0; i < iflist.size()-1; i++) //backpatch gia otan den isxuei to if(katw apo to if_eq)
					{
						if(iflist[i]==22)
						{
							for(int i=0; i<quads.size(); i++)
							{
								if(quads[i].line==22)
								{
									quads[i].label=25;
								}
							}
						}
						backpatch(iflist[i], iflist[i+1]-1);
					}
				}
				cout<<"ifstmt <-- ifstart ) stmt ifstmt_temp\n";
			}
#line 3161 "parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 1312 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {if_scope = scope; if_flag = true;}
#line 3167 "parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 1313 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
					int trueLabel = ++currQuad;
					int falseLabel = trueLabel + 2;
					for(int i = 0; i < (yyvsp[0].exprValue)->truelist.size(); i++){
						for(int j = 0; j < quads.size(); j++){
							if((yyvsp[0].exprValue)->truelist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = trueLabel;
							}
						}
					} 
					for(int i = 0; i < (yyvsp[0].exprValue)->falselist.size(); i++){
						for(int j = 0; j < quads.size(); j++){ 
							if((yyvsp[0].exprValue)->falselist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = falseLabel;
							}
						}
					}
					if(temp_metavlhth)
					{
						std::string temp_str_1=new_temp_name();
						if(scope==0){
							SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
							program_offset++;
						}
						else{
							SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
							function_offset++;
						}	
						(yyval.exprValue)=new expr(assignexpr_e, temp_str_1, 0, "", false, NULL);					
						insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, -1, trueLabel));
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, falseLabel+1, trueLabel + 1));
						currQuad++;
						insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), new expr(assignexpr_e, "FALSE", 0, "", false, NULL), NULL, -1, falseLabel));
						currQuad++;
						insert_quads(new quad(if_eq, (yyval.exprValue), new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, falseLabel+3, falseLabel+1));//allagh edw
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
						iflist.push_back(currQuad);
					}
					else
					{
						if((yyvsp[0].exprValue)->sym==""){
							if((yyvsp[0].exprValue)->boolConst==false )
									(yyval.exprValue)=new expr(constnum_e, (yyvsp[0].exprValue)->sym, -1, "", (yyvsp[0].exprValue)->boolConst, NULL);
							else		
								(yyval.exprValue)=new expr(constnum_e, (yyvsp[0].exprValue)->sym, (yyvsp[0].exprValue)->numConst, "", (yyvsp[0].exprValue)->boolConst, NULL);
							insert_quads(new quad(if_eq, (yyval.exprValue), new expr(constnum_e, "", (yyvsp[0].exprValue)->numConst, "", (yyvsp[0].exprValue)->boolConst, NULL), NULL, currQuad+2, currQuad));
						}
						else{
							if((yyvsp[0].exprValue)->type==assignexpr_e)
							{
								(yyval.exprValue)=new expr(constnum_e, "", 1, "", (yyvsp[0].exprValue)->boolConst, NULL);
								insert_quads(new quad(if_eq, (yyval.exprValue), new expr(constnum_e, "", 1, "", (yyvsp[0].exprValue)->boolConst, NULL), NULL, currQuad+2, currQuad));
							}
							else{
								if((yyvsp[0].exprValue)->boolConst==false)  
									(yyval.exprValue)=new expr(constnum_e, (yyvsp[0].exprValue)->sym, -1, "", (yyvsp[0].exprValue)->boolConst, NULL);
								else		
									(yyval.exprValue)=new expr(constnum_e, (yyvsp[0].exprValue)->sym, (yyvsp[0].exprValue)->numConst, "", (yyvsp[0].exprValue)->boolConst, NULL);
								insert_quads(new quad(if_eq, (yyval.exprValue), new expr(constnum_e, (yyvsp[0].exprValue)->sym, (yyvsp[0].exprValue)->numConst, "", (yyvsp[0].exprValue)->boolConst, NULL), NULL, currQuad+2, currQuad));
				 			}
						}
						/*if($4->sym=="")
							$$=new expr(constnum_e, "", $4->numConst, "", false, NULL);
						else
							$$=new expr(conststring_e, $4->sym, -4, "", false, NULL);
						insert_quads(new quad(if_eq, $$, new expr(constbool_e, "TRUE", 0, "", true, NULL), NULL, currQuad+2, currQuad));*/
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
						iflist.push_back(currQuad);
						if(expression_semicolon)
						{	
							ifstmt_flag = true;
						}							
						else if(!expression_semicolon && !ifstmt_flag){							
							ifstmt_flag = true;
						}
						else
						{
							ifstmt_flag = false;
						}	
					}
					temp_metavlhth=false;
					std::cout << "ifstart <-- IF(expr" << std::endl;
			}
#line 3258 "parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 1400 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
						(yyval.exprValue)=(yyvsp[0].exprValue);
						number_of_elses++;
						std::cout<<"ifstmt_temp <-- ELSE stmt"<<std::endl;
					}
#line 3268 "parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 1405 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {std::cout<<"ifstmt_temp <-- empty"<< std::endl;}
#line 3274 "parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 1409 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    { 
				loop_index--;
				currQuad++; 
				if((yyvsp[-2].exprValue)->list.size()==1)
				{
					insert_quads(new quad(jump, NULL, NULL, NULL, (yyvsp[-2].exprValue)->list[0]-1, currQuad));	
				}
				else
					insert_quads(new quad(jump, NULL, NULL, NULL, while_startlist[loop_index], currQuad)); 
				for(int i = 0; i < (yyvsp[-2].exprValue)->whilelist.size(); i++){
					for(int j = 0; j < quads.size(); j++){
						if((yyvsp[-2].exprValue)->whilelist[i] == quads[j].line){
							if(quads[j].label == -1) quads[j].label = currQuad+1;
						}
					}
				}	
				for(int i=0; i<breaklist.size(); i++)
				{
					backpatch(breaklist[i], currQuad+1);
				}	
				for(int i=0; i<continuelist.size(); i++)
				{
					if((yyvsp[-2].exprValue)->list.size()==1)
					{
						backpatch(continuelist[i], (yyvsp[-2].exprValue)->list[0]-1);
					}
					backpatch(continuelist[i], while_startlist[loop_index]); //
				}
				if(loop_index==0)
				{
					while_startlist.clear();
					while_flag=false;
				}
				std::cout<<"whilestmt <-- whilestart ) stmt\n";	
			}
#line 3314 "parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 1446 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {while_scope = scope; while_flag = true; loop_start=true;}
#line 3320 "parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 1446 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
					int trueLabel = ++currQuad;
					int falseLabel = trueLabel + 2;
					for(int i = 0; i < (yyvsp[0].exprValue)->truelist.size(); i++){
						for(int j = 0; j < quads.size(); j++){
							if((yyvsp[0].exprValue)->truelist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = trueLabel;
							}
						}
					}
					for(int i = 0; i < (yyvsp[0].exprValue)->falselist.size(); i++){
						for(int j = 0; j < quads.size(); j++){
							if((yyvsp[0].exprValue)->falselist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = falseLabel;
							}
						}
					}
					if(temp_metavlhth)
					{
						std::string temp_str_1=new_temp_name();
						if(scope==0){
							SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
							program_offset++;
						}
						else{
							SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
							function_offset++;
						}	
						(yyval.exprValue)=new expr(assignexpr_e, temp_str_1, 0, "", false, NULL);					
						insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, -1, trueLabel));
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, falseLabel+1, trueLabel + 1));
						currQuad++;
						insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), new expr(assignexpr_e, "FALSE", 0, "", false, NULL), NULL, -1, falseLabel));
						currQuad++;
						insert_quads(new quad(if_eq, (yyval.exprValue), new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, falseLabel+3, falseLabel+1));
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
						(yyval.exprValue)->whilelist.push_back(currQuad); 
					}
					else
					{ 
						if((yyvsp[0].exprValue)->sym==""){
							(yyval.exprValue)=new expr(constnum_e, "", (yyvsp[0].exprValue)->numConst, "", true, NULL);
							insert_quads(new quad(if_eq, (yyval.exprValue), new expr(constnum_e, "", (yyvsp[0].exprValue)->numConst, "", true, NULL), NULL, currQuad+2, currQuad));
						}
						else{
							if((yyvsp[0].exprValue)->type==assignexpr_e)
							{
								(yyval.exprValue)=new expr(constnum_e, "", 1, "", true, NULL);
								insert_quads(new quad(if_eq, (yyval.exprValue), new expr(constnum_e, "", 1, "", true, NULL), NULL, currQuad+2, currQuad));
							}
							else{
								(yyval.exprValue)=new expr(constnum_e, (yyvsp[0].exprValue)->sym, (yyvsp[0].exprValue)->numConst, "", true, NULL);
								insert_quads(new quad(if_eq, (yyval.exprValue), new expr(constnum_e, (yyvsp[0].exprValue)->sym, (yyvsp[0].exprValue)->numConst, "", true, NULL), NULL, currQuad+2, currQuad));
							}
						}
						//insert_quads(new quad(if_eq, $$, new expr($4->type, "", 1, "", true, NULL), NULL, currQuad+2, currQuad));
						while_startlist.push_back(currQuad); //mono edw
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
						(yyval.exprValue)->whilelist.push_back(currQuad);	
					}
					loop_index++;
					temp_metavlhth=false;
					(yyval.exprValue)->list=(yyvsp[0].exprValue)->list;
				std::cout<<"whilestart <-- WHILE(expr\n";
			}
#line 3393 "parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 1516 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				loop_index--; 
				for_index--;
				currQuad++;
				if(!assign_flag)
					assign_quads.push_back(while_startlist[loop_index]+1);
				insert_quads(new quad(jump, NULL, NULL, NULL, assign_quads[for_index], currQuad));
				for(int i = 0; i < (yyvsp[-2].exprValue)->forlist.size(); i++){
					for(int j = 0; j < quads.size(); j++){
						if((yyvsp[-2].exprValue)->forlist[i] == quads[j].line){
							if(quads[j].label == -1) quads[j].label = currQuad+1;
						}
					} 
				}
				for(int i=0; i<breaklist.size(); i++)
				{
					backpatch(breaklist[i], currQuad+1);
				}
				for(int i=0; i<continuelist.size(); i++)
				{
					backpatch(continuelist[i], while_startlist[loop_index]+1);
				}
				for_flag=false;
				if(for_index==0)
					assign_quads.clear();
			}
#line 3424 "parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 1544 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				if(if_flag){
					insert_quads(new quad(jump, NULL, NULL, NULL, while_startlist[loop_index], currQuad));
				}
				if(for_flag){
					currQuad++;	
					insert_quads(new quad(jump, NULL, NULL, NULL, while_startlist[loop_index]-1, currQuad));
				}
				loop_index++;
				for_index++;
			}
#line 3440 "parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 1557 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {global_for = 1; for_scope = scope; for_flag = true; loop_start=true;}
#line 3446 "parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 1557 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
					int trueLabel = ++currQuad;
					int falseLabel = trueLabel + 2;
					for(int i = 0; i < (yyvsp[0].exprValue)->truelist.size(); i++){
						for(int j = 0; j < quads.size(); j++){
							if((yyvsp[0].exprValue)->truelist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = trueLabel;
							}
						}
					}
					for(int i = 0; i < (yyvsp[0].exprValue)->falselist.size(); i++){
						for(int j = 0; j < quads.size(); j++){
							if((yyvsp[0].exprValue)->falselist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = falseLabel;
							}
						}
					}
					std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
					(yyval.exprValue)=new expr(assignexpr_e, temp_str_1, 0, "", false, NULL);	
					if(temp_metavlhth)
					{				
						insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, -1, trueLabel));
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, currQuad + 2, trueLabel + 1));
						currQuad++;
						insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), new expr(assignexpr_e, "FALSE", 0, "", false, NULL), NULL, -1, falseLabel));
						currQuad++;
						insert_quads(new quad(if_eq, (yyval.exprValue), new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, falseLabel+6, falseLabel+1));
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
						while_startlist.push_back(currQuad);	
						(yyval.exprValue)->forlist.push_back(currQuad);
					}
					else
					{
						if((yyvsp[0].exprValue)->sym=="")
							(yyval.exprValue)=new expr(constnum_e, "", (yyvsp[0].exprValue)->numConst, "", false, NULL);
						else
							(yyval.exprValue)=new expr(conststring_e, (yyvsp[0].exprValue)->sym, -4, "", false, NULL);
						insert_quads(new quad(if_eq, (yyval.exprValue), new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, currQuad+4, currQuad));	
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
						(yyval.exprValue)->forlist.push_back(currQuad);
						while_startlist.push_back(currQuad); 
					}
				std::cout<<"forstart <-- FOR(elist ; expr\n";
			}
#line 3506 "parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 1614 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				if (!func_flag)
					std::cout << "\033[1;31mERROR\033[0m" << ": Cannot use return outside a function" << std::endl;
			}
#line 3515 "parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 1617 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {  
				currQuad++;    
				insert_quads(new quad(ret, NULL, NULL, NULL, -2, currQuad));
				currQuad++;
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				ret_list.push_back(currQuad);
				ret_flag = true;
				std::cout<<"returnstmt <-- return;\n";}
#line 3528 "parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 1625 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				if(!func_flag)
					std::cout << "\033[1;31mERROR\033[0m" << ": Cannot use return outside a function" << std::endl;
			}
#line 3537 "parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 1628 "parserFINALNOCONFLICTS.y" /* yacc.c:1646  */
    {
				currQuad++;
				string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++; 
				}
				insert_quads(new quad(ret, (yyvsp[-1].exprValue), new expr(assignexpr_e, temp_str_1, 0, "",false, NULL), NULL, -2, currQuad));
				currQuad++;
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				ret_list.push_back(currQuad);
				ret_flag = true;
				getretval_vector.push_back(new expr((yyvsp[-1].exprValue)->type, (yyvsp[-1].exprValue)->sym, (yyvsp[-1].exprValue)->numConst, temp_str_1, (yyvsp[-1].exprValue)->boolConst, NULL));			
				std::cout<<"returnstmt <-- return expr;\n";}
#line 3560 "parser.cpp" /* yacc.c:1646  */
    break;


#line 3564 "parser.cpp" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
  return yyresult;
}
#line 1647 "parserFINALNOCONFLICTS.y" /* yacc.c:1906  */

int main(int argc, char** argv)
{	
	if(argc >1){
		if(!(yyin = fopen(argv[1],"r")))
		{
			std::cout<<"cannot read file: "<< argv[1]<<std::endl;
			return 1;
		}
	}
	else{
		cout<<"\033[1;31mGive input file !!\033[0m"<<endl;
		return 1;
	}
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	SymTable_new(); 
	SymTable_put( 0, 0,LIBFUNC, "print", 0 ,0);
	SymTable_change_visibility("print",0);
	SymTable_put( 0, 0, LIBFUNC, "input", 0 ,0);//
	SymTable_change_visibility("input",0);
	SymTable_put( 0, 0, LIBFUNC, "objectmemberkeys", 0 ,0);//
	SymTable_change_visibility("objectmemberkeys",0);
	SymTable_put( 0, 0, LIBFUNC, "objecttotalmembers", 0 ,0);// 
	SymTable_change_visibility("objecttotalmembers",0);
	SymTable_put( 0, 0, LIBFUNC, "objectcopy", 0 ,0);//
	SymTable_change_visibility("objectcopy",0);
	SymTable_put( 0, 0, LIBFUNC, "totalarguments", 0 ,0);
	SymTable_change_visibility("totalarguments",0);
	SymTable_put( 0, 0, LIBFUNC, "argument", 0 ,0);
	SymTable_change_visibility("argument", 0);
	SymTable_put( 0, 0, LIBFUNC, "typeof", 0 ,0);
	SymTable_change_visibility("typeof", 0);
	SymTable_put( 0, 0, LIBFUNC, "strtonum", 0 ,0);//
	SymTable_change_visibility("strtonum", 0);
	SymTable_put( 0, 0, LIBFUNC, "sqrt", 0 ,0);//
	SymTable_change_visibility("sqrt", 0);
	SymTable_put( 0, 0, LIBFUNC, "cos", 0 ,0);//
	SymTable_change_visibility("cos", 0);
	SymTable_put( 0, 0, LIBFUNC, "sin", 0 ,0);//
	SymTable_change_visibility("sin", 0);
	yyparse();
	SymTable_PRINT();
	print_quads();
	enable_generates();
	print_instruction();
	make_binary_file();
	return 0;
}
