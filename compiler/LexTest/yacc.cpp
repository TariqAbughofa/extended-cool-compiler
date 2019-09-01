/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NOT = 258,
     IF = 259,
     THEN = 260,
     ELSE = 261,
     FI = 262,
     WHILE = 263,
     LOOP = 264,
     POOL = 265,
     LET = 266,
     IN = 267,
     CASE = 268,
     OF = 269,
     ESAC = 270,
     SWITCH = 271,
     ERROR = 272,
     LC = 273,
     RC = 274,
     DOT = 275,
     COMMA = 276,
     LP = 277,
     RP = 278,
     COLON = 279,
     LB = 280,
     RB = 281,
     SEMICOLON = 282,
     IS = 283,
     BEG = 284,
     END = 285,
     err_FALSE = 286,
     err_TRUE = 287,
     INTERFACE = 288,
     NAMESPACE = 289,
     CLASS = 290,
     IMPLEMENTS = 291,
     RETURN = 292,
     INHERITS = 293,
     AT = 294,
     VOID = 295,
     DELETE = 296,
     SUPER = 297,
     PLUS = 298,
     MINUS = 299,
     STAR = 300,
     DIV = 301,
     NEGATE = 302,
     LT = 303,
     LE = 304,
     GT = 305,
     GE = 306,
     EQUAL = 307,
     RE = 308,
     ND = 309,
     AOR = 310,
     ASSIGN = 311,
     ISVOID = 312,
     NEW = 313,
     INT = 314,
     FLOAT = 315,
     STRINGS = 316,
     ID = 317,
     TRUE = 318,
     FALSE = 319,
     PUBLIC = 320,
     PRIVATE = 321,
     PROTECTED = 322,
     INTERNAL = 323,
     STATIC = 324,
     READONLY = 325,
     VIRTUAL = 326,
     SEALED = 327,
     OVERRIDE = 328,
     ABSTRACT = 329,
     XQID = 330
   };
#endif
/* Tokens.  */
#define NOT 258
#define IF 259
#define THEN 260
#define ELSE 261
#define FI 262
#define WHILE 263
#define LOOP 264
#define POOL 265
#define LET 266
#define IN 267
#define CASE 268
#define OF 269
#define ESAC 270
#define SWITCH 271
#define ERROR 272
#define LC 273
#define RC 274
#define DOT 275
#define COMMA 276
#define LP 277
#define RP 278
#define COLON 279
#define LB 280
#define RB 281
#define SEMICOLON 282
#define IS 283
#define BEG 284
#define END 285
#define err_FALSE 286
#define err_TRUE 287
#define INTERFACE 288
#define NAMESPACE 289
#define CLASS 290
#define IMPLEMENTS 291
#define RETURN 292
#define INHERITS 293
#define AT 294
#define VOID 295
#define DELETE 296
#define SUPER 297
#define PLUS 298
#define MINUS 299
#define STAR 300
#define DIV 301
#define NEGATE 302
#define LT 303
#define LE 304
#define GT 305
#define GE 306
#define EQUAL 307
#define RE 308
#define ND 309
#define AOR 310
#define ASSIGN 311
#define ISVOID 312
#define NEW 313
#define INT 314
#define FLOAT 315
#define STRINGS 316
#define ID 317
#define TRUE 318
#define FALSE 319
#define PUBLIC 320
#define PRIVATE 321
#define PROTECTED 322
#define INTERNAL 323
#define STATIC 324
#define READONLY 325
#define VIRTUAL 326
#define SEALED 327
#define OVERRIDE 328
#define ABSTRACT 329
#define XQID 330




/* Copy the first part of user declarations.  */
#line 2 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"


/***Includes and Defines ***/
#define YYDEBUG 1
#include <iostream>
#include <fstream>
using namespace std;
#include "FlexLexer.h"
#include "Actions.h"
#include <cstring>

int yylex(void);
int yyparse();
void yyerror(char *);
char* copystr(const char*);

extern int line;
extern int col;

// Lets Go to Create My Symbol Table

FlexLexer* lexer = new yyFlexLexer();

//temp list
std::list <my_implements*> keke;
std::list <Modifier> meme;
std::list <Variable* > para;
my_implements* Inherit_Struct=new my_implements();
Scope * prevScope;
bool laterLoop = false;

Actions * my_action=new Actions();
bool ok=true;
int paraNum = 0;
class Parser
{
public:
	int	parse()
	{
		return yyparse();
	} 
};



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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 53 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
typedef union YYSTYPE {
int ival;
float fval;
bool bval;
char * sval;
enum Modifier modi;
class	my_modifiers	*my_modifier;
class	my_implements	*my_implement;
class	Variable		*my_parameter;
class	my_parameters	*my_parameterss;
class	my_variables	*my_variable;
class	Case_Expr		*my_caseExpr;
class	my_QIDList		*my_QIDList;
class	Node			*my_Node;
class	AST				*my_AST;
} YYSTYPE;
/* Line 196 of yacc.c.  */
#line 297 "yacc.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 219 of yacc.c.  */
#line 309 "yacc.cpp"

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T) && (defined (__STDC__) || defined (__cplusplus))
# include <stddef.h> /* INFRINGES ON USER NAME SPACE */
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

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

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if defined (__STDC__) || defined (__cplusplus)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     define YYINCLUDED_STDLIB_H
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2005 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM ((YYSIZE_T) -1)
#  endif
#  ifdef __cplusplus
extern "C" {
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if (! defined (malloc) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if (! defined (free) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifdef __cplusplus
}
#  endif
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
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
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1266

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  107
/* YYNRULES -- Number of rules. */
#define YYNRULES  320
/* YYNRULES -- Number of states. */
#define YYNSTATES  569

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   330

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     6,     8,    10,    13,    15,    16,    22,
      23,    28,    29,    35,    39,    42,    45,    48,    49,    51,
      53,    55,    57,    58,    69,    70,    79,    80,    89,    90,
      97,    98,   108,   109,   117,   118,   126,   127,   133,   134,
     142,   143,   150,   151,   159,   160,   167,   168,   174,   175,
     180,   181,   192,   193,   203,   204,   213,   214,   222,   223,
     232,   233,   241,   242,   249,   250,   256,   265,   273,   280,
     286,   293,   299,   304,   308,   311,   314,   318,   320,   324,
     326,   330,   332,   336,   340,   343,   346,   349,   350,   352,
     354,   356,   357,   364,   365,   371,   372,   379,   380,   386,
     392,   397,   406,   414,   422,   429,   439,   448,   453,   458,
     462,   463,   469,   473,   477,   480,   481,   486,   487,   498,
     499,   509,   510,   520,   521,   530,   531,   538,   539,   548,
     549,   557,   558,   567,   568,   576,   577,   586,   587,   597,
     598,   608,   609,   615,   616,   623,   624,   632,   633,   641,
     642,   649,   650,   659,   660,   668,   669,   678,   681,   683,
     686,   695,   703,   710,   718,   722,   724,   727,   729,   731,
     733,   735,   737,   739,   741,   743,   745,   747,   749,   751,
     754,   756,   760,   762,   770,   776,   782,   787,   790,   796,
     800,   804,   807,   814,   820,   826,   829,   835,   840,   845,
     849,   852,   856,   858,   860,   864,   871,   877,   883,   895,
     907,   909,   914,   919,   923,   930,   937,   941,   946,   951,
     957,   961,   966,   974,   982,   988,   992,   998,  1005,  1009,
    1013,  1014,  1015,  1016,  1017,  1029,  1030,  1031,  1039,  1040,
    1041,  1047,  1050,  1051,  1052,  1053,  1062,  1068,  1072,  1076,
    1080,  1084,  1088,  1092,  1096,  1100,  1104,  1108,  1112,  1115,
    1118,  1121,  1124,  1127,  1130,  1133,  1135,  1137,  1139,  1141,
    1143,  1145,  1148,  1152,  1156,  1159,  1162,  1163,  1172,  1173,
    1180,  1181,  1189,  1190,  1196,  1197,  1205,  1206,  1213,  1214,
    1220,  1221,  1226,  1227,  1236,  1237,  1245,  1246,  1253,  1254,
    1260,  1267,  1273,  1278,  1282,  1285,  1288,  1291,  1294,  1295,
    1302,  1310,  1316,  1321,  1325,  1328,  1335,  1341,  1351,  1361,
    1370
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
      77,     0,    -1,    77,    78,    -1,    78,    -1,    19,    -1,
      77,    19,    -1,     1,    -1,    -1,    34,   110,    18,    79,
      82,    -1,    -1,    34,     1,    80,    82,    -1,    -1,    34,
     110,     1,    81,    82,    -1,    34,   110,    19,    -1,    83,
      19,    -1,    83,    84,    -1,    83,    85,    -1,    -1,    78,
      -1,    86,    -1,   167,    -1,     1,    -1,    -1,   149,    35,
      62,    38,   110,    36,   111,    28,    87,   109,    -1,    -1,
     149,    35,    62,    36,   111,    28,    88,   109,    -1,    -1,
     149,    35,    62,    38,   110,    28,    89,   109,    -1,    -1,
     149,    35,    62,    28,    90,   109,    -1,    -1,    35,    62,
      38,   110,    36,   111,    28,    91,   109,    -1,    -1,    35,
      62,    36,   111,    28,    92,   109,    -1,    -1,    35,    62,
      38,   110,    28,    93,   109,    -1,    -1,    35,    62,    28,
      94,   109,    -1,    -1,   149,    35,    62,    36,     1,    95,
     109,    -1,    -1,    35,    62,    36,     1,    96,   109,    -1,
      -1,   149,    35,    62,    38,     1,    97,   109,    -1,    -1,
      35,    62,    38,     1,    98,   109,    -1,    -1,   149,    35,
       1,    99,   109,    -1,    -1,    35,     1,   100,   109,    -1,
      -1,   149,    35,    62,    38,   110,    36,   111,     1,   101,
     109,    -1,    -1,    35,    62,    38,   110,    36,   111,     1,
     102,   109,    -1,    -1,   149,    35,    62,    36,   111,     1,
     103,   109,    -1,    -1,    35,    62,    36,   111,     1,   104,
     109,    -1,    -1,   149,    35,    62,    38,   110,     1,   105,
     109,    -1,    -1,    35,    62,    38,   110,     1,   106,   109,
      -1,    -1,   149,    35,    62,     1,   107,   109,    -1,    -1,
      35,    62,     1,   108,   109,    -1,   149,    35,    62,    38,
     110,    36,   111,    30,    -1,    35,    62,    38,   110,    36,
     111,    30,    -1,   149,    35,    62,    38,   110,    30,    -1,
      35,    62,    38,   110,    30,    -1,   149,    35,    62,    36,
     111,    30,    -1,    35,    62,    36,   111,    30,    -1,   149,
      35,    62,    30,    -1,    35,    62,    30,    -1,   114,    30,
      -1,   114,    84,    -1,   110,    20,    62,    -1,    62,    -1,
     111,    21,   110,    -1,   110,    -1,   112,    21,   113,    -1,
     113,    -1,    62,    24,   110,    -1,    62,    24,     1,    -1,
      62,     1,    -1,   114,   115,    -1,   114,    85,    -1,    -1,
     116,    -1,   124,    -1,   145,    -1,    -1,   149,    62,    24,
     110,   117,   146,    -1,    -1,    62,    24,   110,   118,   146,
      -1,    -1,   149,    62,    24,     1,   119,   146,    -1,    -1,
      62,    24,     1,   120,   146,    -1,   149,    62,    24,   110,
       1,    -1,    62,    24,   110,     1,    -1,   149,    62,    24,
     110,    25,    59,    26,    27,    -1,    62,    24,   110,    25,
      59,    26,    27,    -1,   149,    62,    24,   110,    25,    26,
      27,    -1,    62,    24,   110,    25,    26,    27,    -1,   149,
      62,    24,   110,    25,    59,    26,   121,    27,    -1,    62,
      24,   110,    25,    59,    26,   121,    27,    -1,   121,    25,
      59,    26,    -1,   121,    25,    59,     1,    -1,   121,    25,
      26,    -1,    -1,   121,    25,     1,   122,    26,    -1,    25,
      59,    26,    -1,    25,    59,     1,    -1,    25,    26,    -1,
      -1,    25,     1,   123,    26,    -1,    -1,   149,    62,    22,
     112,    23,    24,   110,    28,   125,   147,    -1,    -1,   149,
      62,    22,    23,    24,   110,    28,   126,   147,    -1,    -1,
      62,    22,   112,    23,    24,   110,    28,   127,   147,    -1,
      -1,    62,    22,    23,    24,   110,    28,   128,   147,    -1,
      -1,   149,    62,    22,     1,   129,   147,    -1,    -1,   149,
      62,    22,    23,    24,     1,   130,   147,    -1,    -1,   149,
      62,    22,    23,     1,   131,   147,    -1,    -1,   149,    62,
      22,    23,    24,   110,   132,   147,    -1,    -1,   149,    62,
      22,   112,     1,   133,   147,    -1,    -1,   149,    62,    22,
     112,    23,     1,   134,   147,    -1,    -1,   149,    62,    22,
     112,    23,    24,     1,   135,   147,    -1,    -1,   149,    62,
      22,   112,    23,    24,   110,   136,   147,    -1,    -1,    62,
      22,     1,   137,   147,    -1,    -1,    62,    22,    23,     1,
     138,   147,    -1,    -1,    62,    22,    23,    24,     1,   139,
     147,    -1,    -1,    62,    22,    23,    24,   110,   140,   147,
      -1,    -1,    62,    22,   112,     1,   141,   147,    -1,    -1,
      62,    22,   112,    23,    24,     1,   142,   147,    -1,    -1,
      62,    22,   112,    23,     1,   143,   147,    -1,    -1,    62,
      22,   112,    23,    24,   110,   144,   147,    -1,   149,     1,
      -1,    62,    -1,   149,    62,    -1,   149,    62,    22,   112,
      23,    24,   110,    27,    -1,   149,    62,    22,    23,    24,
     110,    27,    -1,    62,    22,    23,    24,   110,    27,    -1,
      62,    22,   112,    23,    24,   110,    27,    -1,    56,   154,
      27,    -1,    27,    -1,   153,    30,    -1,    30,    -1,    65,
      -1,    67,    -1,    68,    -1,    66,    -1,    69,    -1,    70,
      -1,    74,    -1,    72,    -1,    73,    -1,    71,    -1,    58,
      -1,   149,   148,    -1,   148,    -1,   150,    21,   154,    -1,
     154,    -1,   151,    21,    62,    24,   110,    56,   154,    -1,
     151,    21,    62,    24,   110,    -1,   151,    21,    62,    24,
       1,    -1,   151,    21,    62,     1,    -1,   151,     1,    -1,
      62,    24,   110,    56,   154,    -1,    62,    24,   110,    -1,
      62,    24,     1,    -1,    62,     1,    -1,   152,    13,   154,
      53,   154,    27,    -1,   152,    13,   154,    53,   154,    -1,
     152,    13,   154,     1,    27,    -1,   152,     1,    -1,    13,
     154,    53,   154,    27,    -1,    13,   154,    53,   154,    -1,
      13,   154,     1,    27,    -1,   153,   154,    27,    -1,   154,
      27,    -1,   153,   166,    27,    -1,   166,    -1,     1,    -1,
      62,    24,   110,    -1,    62,    24,   110,    25,    59,    26,
      -1,    62,    24,   110,    56,   154,    -1,    62,    24,   110,
      25,    26,    -1,    62,    24,   110,    25,    26,    56,    58,
     110,    25,    62,    26,    -1,    62,    24,   110,    25,    26,
      56,    58,   110,    25,    59,    26,    -1,   110,    -1,   110,
      25,    59,    26,    -1,   110,    25,    62,    26,    -1,   110,
      56,   154,    -1,   110,    25,    59,    26,    56,   154,    -1,
     110,    25,    62,    26,    56,   154,    -1,   110,    22,    23,
      -1,   110,    22,   150,    23,    -1,    58,   110,    22,    23,
      -1,    58,   110,    22,   150,    23,    -1,    42,    22,    23,
      -1,    42,    22,   150,    23,    -1,   110,    56,    58,   110,
      25,    62,    26,    -1,   110,    56,    58,   110,    25,    59,
      26,    -1,   154,    20,    62,    56,   154,    -1,   154,    20,
      62,    -1,   154,    20,    62,    22,    23,    -1,   154,    20,
      62,    22,   150,    23,    -1,    22,   154,    23,    -1,   154,
      39,   110,    -1,    -1,    -1,    -1,    -1,     4,   154,     5,
     155,   153,   156,     6,   157,   153,   158,     7,    -1,    -1,
      -1,     8,   154,     9,   159,   153,   160,    10,    -1,    -1,
      -1,    29,   161,   153,   162,    30,    -1,    29,    30,    -1,
      -1,    -1,    -1,    11,   163,   151,   164,    12,   154,   165,
      30,    -1,    16,   154,    14,   152,    15,    -1,   154,    43,
     154,    -1,   154,    44,   154,    -1,   154,    45,   154,    -1,
     154,    46,   154,    -1,   154,    48,   154,    -1,   154,    49,
     154,    -1,   154,    50,   154,    -1,   154,    51,   154,    -1,
     154,    52,   154,    -1,   154,    54,   154,    -1,   154,    55,
     154,    -1,    57,   154,    -1,    47,   154,    -1,     3,   154,
      -1,    41,   154,    -1,    37,   154,    -1,    44,    59,    -1,
      43,    59,    -1,    59,    -1,    60,    -1,    61,    -1,    63,
      -1,    64,    -1,    40,    -1,    58,     1,    -1,   154,    39,
       1,    -1,    16,   154,     1,    -1,    31,     1,    -1,    32,
       1,    -1,    -1,   149,    33,    62,    38,   111,    18,   168,
     180,    -1,    -1,   149,    33,    62,    18,   169,   180,    -1,
      -1,    33,    62,    38,   111,    18,   170,   180,    -1,    -1,
      33,    62,    18,   171,   180,    -1,    -1,    33,    62,    38,
     111,     1,   172,   180,    -1,    -1,    33,    62,    38,     1,
     173,   180,    -1,    -1,    33,    62,     1,   174,   180,    -1,
      -1,    33,     1,   175,   180,    -1,    -1,   149,    33,    62,
      38,   111,     1,   176,   180,    -1,    -1,   149,    33,    62,
      38,     1,   177,   180,    -1,    -1,   149,    33,    62,     1,
     178,   180,    -1,    -1,   149,    33,     1,   179,   180,    -1,
     149,    33,    62,    38,   111,    19,    -1,    33,    62,    38,
     111,    19,    -1,   149,    33,    62,    19,    -1,    33,    62,
      19,    -1,   181,    19,    -1,   181,    84,    -1,   181,   182,
      -1,   181,    85,    -1,    -1,    62,    22,    23,    24,   110,
      27,    -1,    62,    22,   112,    23,    24,   110,    27,    -1,
      62,    22,    23,    24,   110,    -1,    62,    22,     1,    27,
      -1,    62,     1,    27,    -1,     1,    27,    -1,    62,    22,
     112,    23,    24,   110,    -1,    62,    22,   112,     1,    27,
      -1,    62,    22,   112,    23,    24,   110,    18,     1,    27,
      -1,    62,    22,   112,    23,    24,   110,    28,     1,    27,
      -1,    62,    22,    23,    24,   110,    18,     1,    27,    -1,
      62,    22,    23,    24,   110,    28,     1,    27,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   102,   102,   103,   104,   105,   106,   111,   111,   114,
     114,   115,   115,   116,   119,   123,   124,   125,   128,   129,
     130,   133,   138,   138,   140,   140,   142,   142,   144,   144,
     146,   146,   148,   148,   150,   150,   152,   152,   154,   154,
     155,   155,   157,   157,   158,   158,   160,   160,   161,   161,
     163,   163,   164,   164,   165,   165,   166,   166,   168,   168,
     169,   169,   171,   171,   172,   172,   175,   176,   177,   178,
     179,   180,   181,   182,   185,   186,   190,   191,   194,   195,
     198,   199,   202,   203,   204,   209,   210,   211,   214,   215,
     216,   221,   221,   222,   222,   223,   223,   224,   224,   226,
     227,   230,   232,   234,   235,   237,   238,   241,   242,   243,
     244,   244,   246,   247,   248,   249,   249,   253,   253,   255,
     255,   257,   257,   259,   259,   261,   261,   262,   262,   263,
     263,   264,   264,   266,   266,   267,   267,   268,   268,   269,
     269,   271,   271,   272,   272,   273,   273,   274,   274,   276,
     276,   277,   277,   278,   278,   279,   279,   286,   288,   289,
     293,   294,   296,   297,   300,   319,   337,   338,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   359,
     360,   365,   366,   369,   370,   371,   372,   373,   375,   376,
     377,   378,   382,   395,   396,   397,   399,   409,   410,   413,
     430,   438,   439,   441,   445,   446,   447,   448,   449,   450,
     453,   455,   456,   458,   459,   460,   463,   464,   467,   468,
     469,   470,   472,   473,   476,   477,   483,   484,   487,   490,
     493,   494,   495,   496,   493,   508,   509,   508,   521,   522,
     521,   525,   528,   529,   529,   528,   533,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   549,   550,
     551,   552,   554,   557,   558,   559,   560,   561,   562,   563,
     564,   574,   586,   604,   607,   608,   613,   613,   615,   615,
     617,   617,   619,   619,   621,   621,   622,   622,   623,   623,
     624,   624,   626,   626,   627,   627,   628,   628,   629,   629,
     631,   632,   633,   634,   637,   638,   642,   643,   644,   647,
     648,   650,   651,   652,   653,   655,   656,   657,   658,   659,
     660
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NOT", "IF", "THEN", "ELSE", "FI",
  "WHILE", "LOOP", "POOL", "LET", "IN", "CASE", "OF", "ESAC", "SWITCH",
  "ERROR", "LC", "RC", "DOT", "COMMA", "LP", "RP", "COLON", "LB", "RB",
  "SEMICOLON", "IS", "BEG", "END", "err_FALSE", "err_TRUE", "INTERFACE",
  "NAMESPACE", "CLASS", "IMPLEMENTS", "RETURN", "INHERITS", "AT", "VOID",
  "DELETE", "SUPER", "PLUS", "MINUS", "STAR", "DIV", "NEGATE", "LT", "LE",
  "GT", "GE", "EQUAL", "RE", "ND", "AOR", "ASSIGN", "ISVOID", "NEW", "INT",
  "FLOAT", "STRINGS", "ID", "TRUE", "FALSE", "PUBLIC", "PRIVATE",
  "PROTECTED", "INTERNAL", "STATIC", "READONLY", "VIRTUAL", "SEALED",
  "OVERRIDE", "ABSTRACT", "XQID", "$accept", "Program", "Namespacedecl",
  "@1", "@2", "@3", "NamespaceBody", "nTypeDecl", "TypeDecl", "ErrorDecl",
  "classdecl", "@4", "@5", "@6", "@7", "@8", "@9", "@10", "@11", "@12",
  "@13", "@14", "@15", "@16", "@17", "@18", "@19", "@20", "@21", "@22",
  "@23", "@24", "@25", "classBody", "QID", "QIDList", "nFormal", "formal",
  "nFeature", "Feature", "fieldDecl", "@26", "@27", "@28", "@29",
  "INTValue", "@30", "@31", "functionDecl", "@32", "@33", "@34", "@35",
  "@36", "@37", "@38", "@39", "@40", "@41", "@42", "@43", "@44", "@45",
  "@46", "@47", "@48", "@49", "@50", "@51", "abstFuncDecl", "fieldBody",
  "functionBody", "ModifierBuild", "Modifier", "callExpr", "letExpr",
  "caseExpr", "nExpr", "expr", "@52", "@53", "@54", "@55", "@56", "@57",
  "@58", "@59", "@60", "@61", "@62", "exprError", "Interfacedecl", "@63",
  "@64", "@65", "@66", "@67", "@68", "@69", "@70", "@71", "@72", "@73",
  "@74", "interfacebody", "nInterfaceMethod", "InterfaceMethod", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    76,    77,    77,    77,    77,    77,    79,    78,    80,
      78,    81,    78,    78,    82,    83,    83,    83,    84,    84,
      84,    85,    87,    86,    88,    86,    89,    86,    90,    86,
      91,    86,    92,    86,    93,    86,    94,    86,    95,    86,
      96,    86,    97,    86,    98,    86,    99,    86,   100,    86,
     101,    86,   102,    86,   103,    86,   104,    86,   105,    86,
     106,    86,   107,    86,   108,    86,    86,    86,    86,    86,
      86,    86,    86,    86,   109,   109,   110,   110,   111,   111,
     112,   112,   113,   113,   113,   114,   114,   114,   115,   115,
     115,   117,   116,   118,   116,   119,   116,   120,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   121,   121,   121,
     122,   121,   121,   121,   121,   123,   121,   125,   124,   126,
     124,   127,   124,   128,   124,   129,   124,   130,   124,   131,
     124,   132,   124,   133,   124,   134,   124,   135,   124,   136,
     124,   137,   124,   138,   124,   139,   124,   140,   124,   141,
     124,   142,   124,   143,   124,   144,   124,   124,   124,   124,
     145,   145,   145,   145,   146,   146,   147,   147,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   149,
     149,   150,   150,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   152,   152,   152,   152,   152,   152,   152,   153,
     153,   153,   153,   153,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     155,   156,   157,   158,   154,   159,   160,   154,   161,   162,
     154,   154,   163,   164,   165,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   166,   166,   166,   166,   166,   168,   167,   169,   167,
     170,   167,   171,   167,   172,   167,   173,   167,   174,   167,
     175,   167,   176,   167,   177,   167,   178,   167,   179,   167,
     167,   167,   167,   167,   180,   180,   181,   181,   181,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     1,     1,     2,     1,     0,     5,     0,
       4,     0,     5,     3,     2,     2,     2,     0,     1,     1,
       1,     1,     0,    10,     0,     8,     0,     8,     0,     6,
       0,     9,     0,     7,     0,     7,     0,     5,     0,     7,
       0,     6,     0,     7,     0,     6,     0,     5,     0,     4,
       0,    10,     0,     9,     0,     8,     0,     7,     0,     8,
       0,     7,     0,     6,     0,     5,     8,     7,     6,     5,
       6,     5,     4,     3,     2,     2,     3,     1,     3,     1,
       3,     1,     3,     3,     2,     2,     2,     0,     1,     1,
       1,     0,     6,     0,     5,     0,     6,     0,     5,     5,
       4,     8,     7,     7,     6,     9,     8,     4,     4,     3,
       0,     5,     3,     3,     2,     0,     4,     0,    10,     0,
       9,     0,     9,     0,     8,     0,     6,     0,     8,     0,
       7,     0,     8,     0,     7,     0,     8,     0,     9,     0,
       9,     0,     5,     0,     6,     0,     7,     0,     7,     0,
       6,     0,     8,     0,     7,     0,     8,     2,     1,     2,
       8,     7,     6,     7,     3,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     3,     1,     7,     5,     5,     4,     2,     5,     3,
       3,     2,     6,     5,     5,     2,     5,     4,     4,     3,
       2,     3,     1,     1,     3,     6,     5,     5,    11,    11,
       1,     4,     4,     3,     6,     6,     3,     4,     4,     5,
       3,     4,     7,     7,     5,     3,     5,     6,     3,     3,
       0,     0,     0,     0,    11,     0,     0,     7,     0,     0,
       5,     2,     0,     0,     0,     8,     5,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     2,     3,     3,     2,     2,     0,     8,     0,     6,
       0,     7,     0,     5,     0,     7,     0,     6,     0,     5,
       0,     4,     0,     8,     0,     7,     0,     6,     0,     5,
       6,     5,     4,     3,     2,     2,     2,     2,     0,     6,
       7,     5,     4,     3,     2,     6,     5,     9,     9,     8,
       8
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned short int yydefact[] =
{
       0,     6,     4,     0,     0,     3,     9,    77,     0,     1,
       5,     2,    17,    11,     7,    13,     0,    10,     0,    17,
      17,    76,    21,    14,     0,     0,   178,   168,   171,   169,
     170,   172,   173,   177,   175,   176,   174,    18,    15,    16,
      19,   180,     0,    20,    12,     8,   290,     0,    48,     0,
       0,     0,   179,   308,   288,   282,   303,     0,    87,    64,
      36,    73,     0,     0,   298,     0,    46,     0,   291,     0,
     308,   308,   286,    79,     0,    49,     0,    87,    87,    40,
       0,    44,     0,   308,   296,   278,   302,     0,    87,    62,
      28,    72,     0,     0,    21,   304,     0,   305,   307,   306,
     289,   283,   308,   284,   280,   301,     0,    74,   158,    75,
      86,    85,    88,    89,    90,     0,    65,    37,    87,    56,
      32,    71,    87,    60,    34,    69,     0,   299,   308,   308,
     294,     0,    47,    87,    87,    38,     0,    42,     0,   314,
       0,     0,   287,   308,   308,    78,     0,     0,   157,   159,
      41,    87,    87,    45,    87,    87,     0,   297,   279,   308,
     292,   276,   300,    63,    29,    87,    54,    24,    70,    87,
      58,    26,    68,     0,   313,     0,     0,     0,     0,    81,
     285,   281,   141,     0,     0,    97,     0,     0,     0,    57,
      33,    61,    35,    52,    30,    67,   295,   308,   308,    39,
      87,    87,    43,    87,    87,     0,   312,     0,    84,     0,
       0,     0,     0,     0,   143,     0,   149,     0,     0,   100,
       0,     0,   125,     0,     0,    95,     0,    87,    87,   293,
     277,    55,    25,    59,    27,    50,    22,    66,   311,    83,
      82,   316,    80,     0,   203,     0,     0,     0,   242,     0,
       0,   238,   167,     0,     0,     0,   270,     0,     0,     0,
       0,     0,     0,     0,   265,   266,   267,    77,   268,   269,
     210,   142,     0,     0,   202,     0,   145,   147,     0,   153,
       0,   165,     0,    98,     0,     0,    94,     0,   129,     0,
     133,     0,     0,    99,     0,     0,    53,    31,    87,    87,
       0,   309,     0,   315,     0,     0,   260,     0,     0,     0,
       0,     0,   241,     0,   274,   275,   262,   261,     0,   264,
     263,   259,   258,   271,     0,     0,     0,     0,     0,   166,
       0,     0,     0,   200,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   144,     0,   162,   123,
       0,   150,     0,   151,   155,     0,   104,     0,   126,     0,
     127,   131,     0,   135,     0,    96,     0,     0,    92,    51,
      23,     0,     0,     0,   310,     0,     0,     0,   230,   235,
       0,     0,   273,     0,   228,   239,   220,     0,   182,     0,
     204,   216,     0,     0,     0,     0,   213,   199,   201,   225,
     272,   229,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   146,     0,   148,   154,     0,   163,   121,
       0,   164,     0,   102,     0,   130,     0,   161,   119,     0,
     134,     0,   137,   139,   103,     0,   319,   320,     0,     0,
       0,     0,   191,     0,   187,     0,     0,     0,     0,     0,
       0,   221,   218,     0,     0,     0,   217,   211,   212,     0,
       0,     0,   124,   152,     0,   156,   115,   114,     0,     0,
     106,   128,     0,   132,   136,     0,   160,   117,     0,   101,
       0,   317,   318,   231,   236,   190,   189,     0,     0,     0,
     195,     0,   246,   240,   181,   219,   207,     0,   206,     0,
       0,     0,   226,     0,   224,   122,     0,   113,   112,   110,
     109,     0,   120,   138,     0,   140,   105,     0,     0,     0,
     186,     0,   244,     0,     0,     0,     0,   205,   214,   215,
       0,     0,   227,   116,     0,   108,   107,   118,   232,   237,
     188,   185,   184,     0,   198,   197,     0,     0,     0,   223,
     222,   111,     0,     0,   245,   196,   194,   193,     0,   233,
     183,   192,     0,     0,     0,     0,   234,   209,   208
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     4,    37,    20,    12,    19,    17,    18,    38,    39,
      40,   299,   201,   204,   134,   228,   152,   155,    78,   165,
     118,   169,   122,    88,    58,   298,   227,   200,   151,   203,
     154,   133,    77,    75,   270,    74,   178,   179,    76,   111,
     112,   295,   221,   292,   218,   424,   534,   506,   113,   514,
     472,   464,   414,   287,   426,   359,   429,   362,   431,   475,
     478,   213,   275,   347,   350,   278,   417,   352,   420,   114,
     283,   271,    41,    42,   387,   381,   448,   272,   273,   440,
     517,   552,   563,   441,   518,   313,   449,   309,   446,   543,
     274,    43,   198,   129,   144,    71,   143,   102,    70,    53,
     197,   159,   128,    83,    68,    69,    99
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -326
static const short int yypact[] =
{
     231,  -326,  -326,     4,    46,  -326,  -326,  -326,   467,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,   -51,  -326,   356,  -326,
    -326,  -326,  -326,  -326,     8,     9,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  1015,  -326,  -326,  -326,  -326,   204,  -326,    17,
      23,    29,  -326,  -326,  -326,  -326,  -326,    35,  -326,  -326,
    -326,  -326,    39,    40,  -326,   237,  -326,   183,  -326,   311,
    -326,  -326,  -326,     3,   415,  -326,   337,  -326,  -326,  -326,
     148,  -326,   243,  -326,  -326,  -326,  -326,    56,  -326,  -326,
    -326,  -326,    60,    62,    77,  -326,    34,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,    31,  -326,    15,  -326,
    -326,  -326,  -326,  -326,  -326,   385,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,    31,  -326,  -326,  -326,
    -326,   461,  -326,  -326,  -326,  -326,   298,  -326,   246,  -326,
     181,    11,  -326,  -326,  -326,     3,    20,    66,  -326,    70,
    -326,  -326,  -326,  -326,  -326,  -326,   411,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,    31,  -326,   254,   268,   228,   313,  -326,
    -326,  -326,  -326,   244,   314,  -326,   162,    21,    85,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,   414,  -326,    31,  -326,    94,
     269,   277,   309,   462,  -326,    98,  -326,   256,     2,  -326,
     108,     2,  -326,   271,   319,  -326,   208,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,   449,  -326,
       3,  -326,  -326,    31,  -326,   854,   854,   854,  -326,   854,
     854,   357,  -326,   367,   387,   854,  -326,   854,   391,   372,
     378,   854,   854,   119,  -326,  -326,  -326,   424,  -326,  -326,
     123,  -326,   588,  1051,  -326,   462,  -326,   418,   462,  -326,
     124,  -326,   854,  -326,   422,   434,  -326,   462,  -326,   130,
    -326,   282,     2,  -326,   112,     2,  -326,  -326,  -326,  -326,
     460,  -326,   473,   470,   854,    31,  1192,   974,   992,   413,
     918,  1084,  -326,   526,  -326,  -326,  1192,  1192,   712,  -326,
    -326,   141,   141,  -326,   153,    31,   721,   189,   863,  -326,
    1098,   468,   427,  -326,   135,   854,   854,   854,   854,   854,
     854,   854,   854,   854,   854,   854,  -326,   462,  -326,  -326,
     462,  -326,   462,  -326,   444,  1131,  -326,   300,  -326,   462,
    -326,   480,   462,  -326,   136,  -326,   469,   475,  -326,  -326,
    -326,   488,   490,   530,  -326,   531,  1013,    31,  -326,  -326,
     286,   320,  -326,   520,  -326,   650,  -326,   343,  1192,   783,
     168,  -326,   377,   512,   513,    31,  1192,  -326,  -326,     6,
    -326,     3,   239,   239,   141,   141,   304,   304,   304,   304,
     304,  1214,  1214,  -326,   462,  -326,  -326,   462,  -326,  -326,
     462,  -326,   151,  -326,   392,  -326,   462,  -326,  -326,   462,
    -326,   462,  -326,   508,  -326,   456,  -326,  -326,   514,   516,
     526,   526,  -326,   139,  -326,   478,   532,   854,   290,   517,
     854,  -326,  -326,   489,   113,   854,  -326,   494,   495,   338,
     792,   854,  -326,  -326,   462,  -326,  -326,  -326,    25,   157,
    -326,  -326,   462,  -326,  -326,   462,  -326,  -326,   462,  -326,
     486,  -326,  -326,   650,   650,  -326,    -7,   287,   854,   932,
    -326,   854,  -326,  -326,  1192,  -326,   496,   523,  1192,   854,
     854,   334,  -326,   493,  1192,  -326,   527,  -326,  -326,  -326,
    -326,   165,  -326,  -326,   462,  -326,  -326,   540,   544,   854,
    -326,   145,  1192,   529,   854,   954,   501,  -326,  1192,  1192,
     534,   535,  -326,  -326,   536,  -326,  -326,  -326,  -326,  -326,
    1192,  -326,    -6,   541,  -326,  1145,   537,   854,    31,  -326,
    -326,  -326,   526,   854,  -326,  -326,  -326,  1178,   242,   650,
    1192,  -326,   335,   558,   546,   548,  -326,  -326,  -326
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -326,  -326,   190,  -326,  -326,  -326,   289,  -326,   167,   224,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,    -1,    -3,   -54,  -139,   364,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,   142,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -217,  -113,   -36,   500,  -325,  -326,  -326,  -311,  -230,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -269,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,    -2,  -326,  -326
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -244
static const short int yytable[] =
{
       8,   392,   385,   331,   286,     6,    52,   184,    80,    46,
      48,    21,   175,    16,    16,   306,   307,   308,    59,   310,
     311,   182,   222,    16,    64,   316,   507,   317,   460,   281,
      66,   321,   322,   131,   176,   140,    72,   146,   136,   147,
      79,    81,   330,   183,   223,    60,     9,    61,   224,   519,
     553,   508,   355,    62,    73,    63,   141,   130,   282,    73,
      82,   135,   461,   137,   453,    10,     7,   185,   100,   101,
      47,    49,   156,   177,   376,   365,   116,   117,   368,    52,
       3,   127,   177,   177,    73,    65,   225,   132,   388,    73,
     138,    67,   187,     7,   188,   239,   388,     7,   396,   276,
     142,     7,     7,   145,   139,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   411,   412,   331,   150,     7,   205,
     323,   153,     7,    73,     7,   353,   157,   158,     7,   483,
     484,   360,   163,   164,   284,   503,   400,   432,   366,   496,
     485,   180,   181,    16,   186,   326,   541,     7,   327,   119,
     189,   190,   466,   191,   192,   330,     7,   196,   509,   388,
       7,   332,   346,   219,   199,   351,   535,   285,   202,   106,
      73,   367,   497,    16,   358,   389,   120,   467,   121,   328,
     377,     7,    16,   510,    89,   226,     7,   220,    16,   -93,
       5,   536,     7,   454,    11,   229,   230,     7,     7,   231,
     232,     7,   233,   234,   238,    54,   240,     7,   174,   293,
     468,    90,   277,    91,   331,   331,   511,   489,   -93,    92,
     494,    93,    55,    56,   455,   498,   296,   297,    16,   208,
     388,   504,     1,   294,   413,   -91,    97,   415,    84,   416,
     303,   559,    57,   109,   123,   214,   425,   170,   393,   430,
       2,   394,   209,   330,   330,    85,    86,   279,   522,   332,
     324,   525,    16,    16,   -91,     3,    16,   562,   215,   528,
     529,   124,   288,   125,   171,    87,   172,   354,   377,   126,
     280,   206,   173,   363,   337,   338,   361,   442,   520,   540,
     331,   490,   207,    98,   545,   289,   241,   369,   370,   166,
     110,   462,   324,   491,   463,   492,   364,   465,    44,    45,
     443,   521,    94,   471,   210,   216,   473,   557,   474,   106,
     290,   444,   390,   560,   332,   422,   167,   423,   168,   330,
      95,   401,  -243,   243,   211,   211,   212,   217,    22,   177,
     211,   445,   291,   377,    24,     3,    25,   335,   336,   337,
     338,   505,  -244,  -244,  -244,  -244,  -244,    22,    16,   512,
     389,   433,   513,   501,   450,   515,   451,   107,   314,    26,
      24,     3,    25,    96,   401,    23,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,   148,   312,   315,    24,
       3,    25,   459,   530,   564,    26,   531,   565,   450,   108,
     456,   537,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,   193,   318,    26,   235,   103,   469,    50,   470,
      51,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,   319,   106,   104,   105,   106,   106,   320,    16,   194,
     486,   195,   236,    26,   237,   348,   349,   149,   325,   356,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
     357,   371,   160,   244,    16,   245,   246,   300,    13,    16,
     247,   418,   419,   248,   372,   380,   301,   302,   249,   161,
     162,   422,   106,   479,   250,    14,    15,    16,   373,   399,
      16,   251,   252,   253,   254,   398,   434,   374,   375,   255,
      16,   435,   256,   257,   258,   259,   260,   427,   428,   261,
     450,   469,   495,   516,   450,   436,   532,   437,   542,   262,
     263,   264,   265,   266,   267,   268,   269,   244,    16,   245,
     246,   438,   439,   447,   247,   476,   477,   248,   457,   458,
     487,   481,   249,   482,   488,   558,   538,   493,   250,   527,
     499,   500,   526,   533,   539,   251,   544,   253,   254,   548,
     549,   550,   551,   255,   556,   566,   256,   257,   258,   259,
     260,   554,   567,   261,   568,   242,   115,   480,     0,     0,
       0,     0,     0,   262,   263,   264,   265,   266,   267,   268,
     269,   245,   246,     0,     0,     0,   247,     0,     0,   248,
       0,     0,     0,     0,   249,     0,     0,     0,     0,     0,
     250,     0,     0,     0,     0,     0,     0,   251,   329,   253,
     254,     0,     0,     0,     0,   255,     0,     0,   256,   257,
     258,   259,   260,     0,     0,   261,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   262,   263,   264,   265,   266,
     267,   268,   269,   245,   246,     0,     0,     0,   247,     0,
       0,   248,     0,     0,     0,     0,   249,     0,     0,     0,
       0,     0,   250,     0,     0,     0,     0,     0,     0,   251,
       0,   253,   254,     0,     0,     0,     0,   255,     0,     0,
     256,   257,   258,   259,   260,     0,     0,   261,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   262,   263,   264,
     265,   266,   267,   268,   269,   245,   246,     0,     0,     0,
     247,     0,     0,   248,   245,   246,     0,     0,   304,   247,
       0,     0,   248,     0,   250,   386,     0,   304,     0,     0,
       0,   251,     0,   250,   391,     0,     0,     0,     0,   255,
     251,     0,   256,   257,   258,   259,   260,     0,   255,   261,
       0,   256,   257,   258,   259,   260,     0,     0,   261,   262,
     305,   264,   265,   266,   267,   268,   269,     0,   262,   305,
     264,   265,   266,   267,   268,   269,   245,   246,     0,     0,
       0,   247,     0,     0,   248,   245,   246,     0,     0,   304,
     247,     0,     0,   248,     0,   250,   452,     0,   304,     0,
       0,     0,   251,     0,   250,   502,     0,     0,     0,     0,
     255,   251,     0,   256,   257,   258,   259,   260,     0,   255,
     261,     0,   256,   257,   258,   259,   260,     0,     0,   261,
     262,   305,   264,   265,   266,   267,   268,   269,     0,   262,
     305,   264,   265,   266,   267,   268,   269,   245,   246,     0,
       0,     0,   247,     0,     0,   248,   245,   246,     0,     0,
     304,   247,     0,     0,   248,     0,   250,     0,     0,   304,
       0,     0,     0,   251,     0,   250,     0,     0,     0,     0,
       0,   255,   251,     0,   256,   257,   258,   259,   260,     0,
     255,   261,     0,   256,   257,   258,   259,   260,     0,     0,
     261,   262,   305,   264,   265,   266,   267,   268,   269,   382,
     262,   395,   264,   265,   266,   267,   268,   269,     0,     0,
       0,     0,   383,   523,     0,     0,     0,     0,   332,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   332,     0,     0,   546,     0,   377,     0,     0,
       0,   335,   336,   337,   338,     0,   339,   340,   341,   342,
     343,   377,   344,   345,   332,   335,   336,   337,   338,   378,
     339,   340,   341,   342,   343,   524,   344,   345,     0,     0,
       0,     0,     0,   377,   332,     0,     0,   335,   336,   337,
     338,   379,   339,   340,   341,   342,   343,   547,   344,   345,
       0,     0,   332,   377,     0,     0,     0,   335,   336,   337,
     338,     0,   339,   340,   341,   342,   343,   383,   344,   345,
       0,   377,     0,   332,     0,   335,   336,   337,   338,     0,
     339,   340,   341,   342,   343,     0,   344,   345,    50,     0,
      51,     0,   377,     0,     0,     0,   335,   336,   337,   338,
       0,   339,   340,   341,   342,   343,     0,   344,   345,     0,
       0,   332,     0,    26,     0,     0,     0,     0,   333,     0,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
     334,     0,     0,     0,   335,   336,   337,   338,     0,   339,
     340,   341,   342,   343,   332,   344,   345,   384,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   332,     0,
       0,     0,     0,   377,     0,   397,     0,   335,   336,   337,
     338,     0,   339,   340,   341,   342,   343,   334,   344,   345,
       0,   335,   336,   337,   338,     0,   339,   340,   341,   342,
     343,   332,   344,   345,     0,     0,     0,     0,   421,     0,
       0,     0,     0,     0,     0,   332,     0,     0,     0,     0,
     377,     0,   555,     0,   335,   336,   337,   338,     0,   339,
     340,   341,   342,   343,   377,   344,   345,     0,   335,   336,
     337,   338,     0,   339,   340,   341,   342,   343,   332,   344,
     345,     0,     0,     0,     0,   561,     0,     0,     0,     0,
       0,     0,   332,     0,     0,     0,     0,   377,     0,     0,
       0,   335,   336,   337,   338,     0,   339,   340,   341,   342,
     343,   377,   344,   345,   332,   335,   336,   337,   338,     0,
     339,   340,   341,   342,   343,     0,   344,   345,     0,     0,
       0,     0,     0,   377,     0,     0,     0,   335,   336,   337,
     338,     0,   339,   340,   341,   342,   343
};

static const short int yycheck[] =
{
       3,   326,   313,   272,   221,     1,    42,   146,    62,     1,
       1,    62,     1,    20,    20,   245,   246,   247,     1,   249,
     250,     1,     1,    20,     1,   255,     1,   257,    22,    27,
       1,   261,   262,    87,    23,     1,     1,    22,    92,    24,
       1,     1,   272,    23,    23,    28,     0,    30,   187,    56,
      56,    26,   282,    36,    57,    38,    22,     1,    56,    62,
      63,     1,    56,     1,   389,    19,    62,     1,    70,    71,
      62,    62,   126,    62,   304,   292,    77,    78,   295,   115,
      34,    83,    62,    62,    87,    62,     1,    88,   318,    92,
      93,    62,    22,    62,    24,     1,   326,    62,   328,     1,
     102,    62,    62,   106,    27,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   385,   118,    62,   173,
       1,   122,    62,   126,    62,     1,   128,   129,    62,   440,
     441,     1,   133,   134,    26,   460,     1,     1,    26,    26,
       1,   143,   144,    20,   147,    22,     1,    62,    25,     1,
     151,   152,     1,   154,   155,   385,    62,   159,     1,   389,
      62,    20,   275,     1,   165,   278,     1,    59,   169,    21,
     173,    59,    59,    20,   287,    22,    28,    26,    30,    56,
      39,    62,    20,    26,     1,   188,    62,    25,    20,    27,
       0,    26,    62,    25,     4,   197,   198,    62,    62,   200,
     201,    62,   203,   204,   207,     1,   209,    62,    27,     1,
      59,    28,   215,    30,   483,   484,    59,   447,    56,    36,
     450,    38,    18,    19,    56,   455,   227,   228,    20,     1,
     460,   461,     1,    25,   347,    27,    69,   350,     1,   352,
     243,   552,    38,    76,     1,     1,   359,     1,    59,   362,
      19,    62,    24,   483,   484,    18,    19,     1,   488,    20,
     263,   491,    20,    20,    56,    34,    20,    25,    24,   499,
     500,    28,     1,    30,    28,    38,    30,   280,    39,    36,
      24,    27,    36,     1,    45,    46,   289,     1,     1,   519,
     559,     1,    24,    69,   524,    24,    27,   298,   299,     1,
      76,   414,   305,    13,   417,    15,    24,   420,    19,    20,
      24,    24,     1,   426,     1,     1,   429,   547,   431,    21,
       1,     1,   325,   553,    20,    25,    28,    27,    30,   559,
      19,   334,    12,    24,    21,    21,    23,    23,     1,    62,
      21,    21,    23,    39,    33,    34,    35,    43,    44,    45,
      46,   464,    48,    49,    50,    51,    52,     1,    20,   472,
      22,   364,   475,    25,    21,   478,    23,    30,     1,    58,
      33,    34,    35,    62,   377,    19,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,     1,    30,     1,    33,
      34,    35,   395,    59,    59,    58,    62,    62,    21,    62,
      23,   514,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,     1,    22,    58,     1,     1,    25,    33,    27,
      35,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    59,    21,    18,    19,    21,    21,    59,    20,    28,
     443,    30,    28,    58,    30,    27,    28,    62,    24,    27,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      26,     1,     1,     1,    20,     3,     4,    18,     1,    20,
       8,    27,    28,    11,     1,    62,    27,    28,    16,    18,
      19,    25,    21,    27,    22,    18,    19,    20,    18,    62,
      20,    29,    30,    31,    32,    27,    27,    27,    28,    37,
      20,    26,    40,    41,    42,    43,    44,    27,    28,    47,
      21,    25,    23,    27,    21,    27,    23,    27,   521,    57,
      58,    59,    60,    61,    62,    63,    64,     1,    20,     3,
       4,     1,     1,    13,     8,    27,    28,    11,    26,    26,
      62,    27,    16,    27,    12,   548,     6,    30,    22,    26,
      56,    56,    56,    26,    10,    29,    27,    31,    32,    58,
      26,    26,    26,    37,    27,     7,    40,    41,    42,    43,
      44,    30,    26,    47,    26,   211,    76,   435,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,     3,     4,    -1,    -1,    -1,     8,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    -1,    -1,    -1,    -1,    37,    -1,    -1,    40,    41,
      42,    43,    44,    -1,    -1,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,     3,     4,    -1,    -1,    -1,     8,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,
      -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    31,    32,    -1,    -1,    -1,    -1,    37,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    61,    62,    63,    64,     3,     4,    -1,    -1,    -1,
       8,    -1,    -1,    11,     3,     4,    -1,    -1,    16,     8,
      -1,    -1,    11,    -1,    22,    23,    -1,    16,    -1,    -1,
      -1,    29,    -1,    22,    23,    -1,    -1,    -1,    -1,    37,
      29,    -1,    40,    41,    42,    43,    44,    -1,    37,    47,
      -1,    40,    41,    42,    43,    44,    -1,    -1,    47,    57,
      58,    59,    60,    61,    62,    63,    64,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,     3,     4,    -1,    -1,
      -1,     8,    -1,    -1,    11,     3,     4,    -1,    -1,    16,
       8,    -1,    -1,    11,    -1,    22,    23,    -1,    16,    -1,
      -1,    -1,    29,    -1,    22,    23,    -1,    -1,    -1,    -1,
      37,    29,    -1,    40,    41,    42,    43,    44,    -1,    37,
      47,    -1,    40,    41,    42,    43,    44,    -1,    -1,    47,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    57,
      58,    59,    60,    61,    62,    63,    64,     3,     4,    -1,
      -1,    -1,     8,    -1,    -1,    11,     3,     4,    -1,    -1,
      16,     8,    -1,    -1,    11,    -1,    22,    -1,    -1,    16,
      -1,    -1,    -1,    29,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    37,    29,    -1,    40,    41,    42,    43,    44,    -1,
      37,    47,    -1,    40,    41,    42,    43,    44,    -1,    -1,
      47,    57,    58,    59,    60,    61,    62,    63,    64,     1,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    -1,    14,     1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,     1,    -1,    39,    -1,    -1,
      -1,    43,    44,    45,    46,    -1,    48,    49,    50,    51,
      52,    39,    54,    55,    20,    43,    44,    45,    46,     5,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    39,    20,    -1,    -1,    43,    44,    45,
      46,     9,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    -1,    20,    39,    -1,    -1,    -1,    43,    44,    45,
      46,    -1,    48,    49,    50,    51,    52,    14,    54,    55,
      -1,    39,    -1,    20,    -1,    43,    44,    45,    46,    -1,
      48,    49,    50,    51,    52,    -1,    54,    55,    33,    -1,
      35,    -1,    39,    -1,    -1,    -1,    43,    44,    45,    46,
      -1,    48,    49,    50,    51,    52,    -1,    54,    55,    -1,
      -1,    20,    -1,    58,    -1,    -1,    -1,    -1,    27,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      39,    -1,    -1,    -1,    43,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,    20,    54,    55,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    39,    -1,    27,    -1,    43,    44,    45,
      46,    -1,    48,    49,    50,    51,    52,    39,    54,    55,
      -1,    43,    44,    45,    46,    -1,    48,    49,    50,    51,
      52,    20,    54,    55,    -1,    -1,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      39,    -1,    27,    -1,    43,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,    39,    54,    55,    -1,    43,    44,
      45,    46,    -1,    48,    49,    50,    51,    52,    20,    54,
      55,    -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    43,    44,    45,    46,    -1,    48,    49,    50,    51,
      52,    39,    54,    55,    20,    43,    44,    45,    46,    -1,
      48,    49,    50,    51,    52,    -1,    54,    55,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    44,    45,
      46,    -1,    48,    49,    50,    51,    52
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     1,    19,    34,    77,    78,     1,    62,   110,     0,
      19,    78,    80,     1,    18,    19,    20,    82,    83,    81,
      79,    62,     1,    19,    33,    35,    58,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    78,    84,    85,
      86,   148,   149,   167,    82,    82,     1,    62,     1,    62,
      33,    35,   148,   175,     1,    18,    19,    38,   100,     1,
      28,    30,    36,    38,     1,    62,     1,    62,   180,   181,
     174,   171,     1,   110,   111,   109,   114,   108,    94,     1,
     111,     1,   110,   179,     1,    18,    19,    38,    99,     1,
      28,    30,    36,    38,     1,    19,    62,    84,    85,   182,
     180,   180,   173,     1,    18,    19,    21,    30,    62,    84,
      85,   115,   116,   124,   145,   149,   109,   109,    96,     1,
      28,    30,    98,     1,    28,    30,    36,   180,   178,   169,
       1,   111,   109,   107,    90,     1,   111,     1,   110,    27,
       1,    22,   180,   172,   170,   110,    22,    24,     1,    62,
     109,   104,    92,   109,   106,    93,   111,   180,   180,   177,
       1,    18,    19,   109,   109,    95,     1,    28,    30,    97,
       1,    28,    30,    36,    27,     1,    23,    62,   112,   113,
     180,   180,     1,    23,   112,     1,   110,    22,    24,   109,
     109,   109,   109,     1,    28,    30,   180,   176,   168,   109,
     103,    88,   109,   105,    89,   111,    27,    24,     1,    24,
       1,    21,    23,   137,     1,    24,     1,    23,   120,     1,
      25,   118,     1,    23,   112,     1,   110,   102,    91,   180,
     180,   109,   109,   109,   109,     1,    28,    30,   110,     1,
     110,    27,   113,    24,     1,     3,     4,     8,    11,    16,
      22,    29,    30,    31,    32,    37,    40,    41,    42,    43,
      44,    47,    57,    58,    59,    60,    61,    62,    63,    64,
     110,   147,   153,   154,   166,   138,     1,   110,   141,     1,
      24,    27,    56,   146,    26,    59,   146,   129,     1,    24,
       1,    23,   119,     1,    25,   117,   109,   109,   101,    87,
      18,    27,    28,   110,    16,    58,   154,   154,   154,   163,
     154,   154,    30,   161,     1,     1,   154,   154,    22,    59,
      59,   154,   154,     1,   110,    24,    22,    25,    56,    30,
     154,   166,    20,    27,    39,    43,    44,    45,    46,    48,
      49,    50,    51,    52,    54,    55,   147,   139,    27,    28,
     140,   147,   143,     1,   110,   154,    27,    26,   147,   131,
       1,   110,   133,     1,    24,   146,    26,    59,   146,   109,
     109,     1,     1,    18,    27,    28,   154,    39,     5,     9,
      62,   151,     1,    14,    23,   153,    23,   150,   154,    22,
     110,    23,   150,    59,    62,    58,   154,    27,    27,    62,
       1,   110,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   147,   128,   147,   147,   142,    27,    28,
     144,    27,    25,    27,   121,   147,   130,    27,    28,   132,
     147,   134,     1,   110,    27,    26,    27,    27,     1,     1,
     155,   159,     1,    24,     1,    21,   164,    13,   152,   162,
      21,    23,    23,   150,    25,    56,    23,    26,    26,   110,
      22,    56,   147,   147,   127,   147,     1,    26,    59,    25,
      27,   147,   126,   147,   147,   135,    27,    28,   136,    27,
     121,    27,    27,   153,   153,     1,   110,    62,    12,   154,
       1,    13,    15,    30,   154,    23,    26,    59,   154,    56,
      56,    25,    23,   150,   154,   147,   123,     1,    26,     1,
      26,    59,   147,   147,   125,   147,    27,   156,   160,    56,
       1,    24,   154,     1,    53,   154,    56,    26,   154,   154,
      59,    62,    23,    26,   122,     1,    26,   147,     6,    10,
     154,     1,   110,   165,    27,   154,     1,    53,    58,    26,
      26,    26,   157,    56,    30,    27,    27,   154,   110,   153,
     154,    27,    25,   158,    59,    62,     7,    26,    26
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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
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
    while (0)
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
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr,					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname[yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
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
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
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
      size_t yyn = 0;
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

#endif /* YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
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
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()
    ;
#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


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
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to look-ahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
        case 4:
#line 104 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("USLESS '}' NAMESPACE DECLARATION EXPECTED");;}
    break;

  case 5:
#line 105 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("USLESS '}' NAMESPACE DECLARATION EXPECTED");;}
    break;

  case 7:
#line 111 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->NameSpace_Action((yyvsp[-1].my_implement)->implement,line,true);;}
    break;

  case 8:
#line 112 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->NameSpace_Action((yyvsp[-3].my_implement)->implement,line,false);;}
    break;

  case 9:
#line 114 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("ERROR IN NAMESPACE DEFINATION"); my_action->sure=false;;}
    break;

  case 10:
#line 114 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure=true;;}
    break;

  case 11:
#line 115 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'{' EXPECTED"); my_action->sure=false;;}
    break;

  case 12:
#line 115 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure=true;;}
    break;

  case 13:
#line 116 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'{' MISSING"); ;}
    break;

  case 22:
#line 138 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->Class_Action((yyvsp[-7].my_modifier)->modi,(yyvsp[-1].my_QIDList)->lists,(yyvsp[-3].my_implement),(yyvsp[-5].sval),line);;}
    break;

  case 23:
#line 138 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->closeClass_Action(line);;}
    break;

  case 24:
#line 140 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Inherit_Struct=new my_implements("Object"); my_action->Class_Action((yyvsp[-5].my_modifier)->modi,(yyvsp[-1].my_QIDList)->lists,Inherit_Struct,(yyvsp[-3].sval),line);;}
    break;

  case 25:
#line 140 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->closeClass_Action(line);;}
    break;

  case 26:
#line 142 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {keke.clear(); my_action->Class_Action((yyvsp[-5].my_modifier)->modi,keke,(yyvsp[-1].my_implement),(yyvsp[-3].sval),line);;}
    break;

  case 27:
#line 142 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->closeClass_Action(line);;}
    break;

  case 28:
#line 144 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Inherit_Struct=new my_implements("Object"); keke.clear(); my_action->Class_Action((yyvsp[-3].my_modifier)->modi,keke,Inherit_Struct,(yyvsp[-1].sval),line);;}
    break;

  case 29:
#line 144 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->closeClass_Action(line);;}
    break;

  case 30:
#line 146 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {meme.clear(); my_action->Class_Action(meme,(yyvsp[-1].my_QIDList)->lists,(yyvsp[-3].my_implement),(yyvsp[-5].sval),line);;}
    break;

  case 31:
#line 146 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->closeClass_Action(line);;}
    break;

  case 32:
#line 148 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {meme.clear(); Inherit_Struct=new my_implements("Object"); my_action->Class_Action(meme,(yyvsp[-1].my_QIDList)->lists,Inherit_Struct,(yyvsp[-3].sval),line);;}
    break;

  case 33:
#line 148 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->closeClass_Action(line);;}
    break;

  case 34:
#line 150 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {keke.clear(); meme.clear(); my_action->Class_Action(meme,keke,(yyvsp[-1].my_implement),(yyvsp[-3].sval),line);;}
    break;

  case 35:
#line 150 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->closeClass_Action(line);;}
    break;

  case 36:
#line 152 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Inherit_Struct=new my_implements("Object"); meme.clear(); keke.clear(); my_action->Class_Action(meme,keke,Inherit_Struct,(yyvsp[-1].sval),line);;}
    break;

  case 37:
#line 152 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->closeClass_Action(line);;}
    break;

  case 38:
#line 154 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("ERROR IN IMPLEMENTATION LIST"); my_action->sure_=false;;}
    break;

  case 39:
#line 154 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 40:
#line 155 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("ERROR IN IMPLEMENTATION LIST");my_action->sure_=false;;}
    break;

  case 41:
#line 155 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 42:
#line 157 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("ERROR IN INHERITANCE LIST"); my_action->sure_=false;;}
    break;

  case 43:
#line 157 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 44:
#line 158 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("ERROR IN INHERITANCE LIST");my_action->sure_=false;;}
    break;

  case 45:
#line 158 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 46:
#line 160 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("ERROR IN CLASS DEFINATION");my_action->sure_=false;;}
    break;

  case 47:
#line 160 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 48:
#line 161 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("ERROR IN CLASS DEFINATION");my_action->sure_=false;;}
    break;

  case 49:
#line 161 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 50:
#line 163 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD EXPECTED");my_action->sure_=false;;}
    break;

  case 51:
#line 163 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 52:
#line 164 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD EXPECTED"); my_action->sure_=false;;}
    break;

  case 53:
#line 164 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 54:
#line 165 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD EXPECTED");my_action->sure_=false;;}
    break;

  case 55:
#line 165 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 56:
#line 166 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD EXPECTED");my_action->sure_=false;;}
    break;

  case 57:
#line 166 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 58:
#line 168 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' or 'IMPLEMENTS' KEYWORD EXPECTED");my_action->sure_=false; ;}
    break;

  case 59:
#line 168 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 60:
#line 169 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' or 'IMPLEMENTS' KEYWORD EXPECTED"); my_action->sure_=false;;}
    break;

  case 61:
#line 169 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 62:
#line 171 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' or 'IMPLEMENTS' or 'INHERITS' KEYWORD EXPECTED"); my_action->sure_=false;;}
    break;

  case 63:
#line 171 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 64:
#line 172 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' or 'IMPLEMENTS' or 'INHERITS' KEYWORD EXPECTED"); my_action->sure_=false;;}
    break;

  case 65:
#line 172 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 66:
#line 175 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD MISSING");;}
    break;

  case 67:
#line 176 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD MISSING");;}
    break;

  case 68:
#line 177 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD MISSING");;}
    break;

  case 69:
#line 178 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD MISSING");;}
    break;

  case 70:
#line 179 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD MISSING");;}
    break;

  case 71:
#line 180 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD MISSING");;}
    break;

  case 72:
#line 181 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD MISSING");;}
    break;

  case 73:
#line 182 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD MISSING");;}
    break;

  case 75:
#line 186 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'END' KEYWORD EXPECTED CAN NOT DECLARE AN INNER NAMESPACE/INTERFACE/CLASS");;}
    break;

  case 76:
#line 190 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyvsp[-2].my_implement)->add_implement((yyvsp[0].sval)); (yyval.my_implement)=(yyvsp[-2].my_implement);;}
    break;

  case 77:
#line 191 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.my_implement)=new my_implements((yyvsp[0].sval));;}
    break;

  case 78:
#line 194 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyvsp[-2].my_QIDList)->add_list((yyvsp[0].my_implement)); (yyval.my_QIDList)=(yyvsp[-2].my_QIDList);;}
    break;

  case 79:
#line 195 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.my_QIDList)=new my_QIDList((yyvsp[0].my_implement));;}
    break;

  case 80:
#line 198 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyvsp[-2].my_parameterss)->add_parameter((yyvsp[0].my_parameter));(yyval.my_parameterss)=(yyvsp[-2].my_parameterss);;}
    break;

  case 81:
#line 199 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.my_parameterss)=new my_parameters((yyvsp[0].my_parameter));;}
    break;

  case 82:
#line 202 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.my_parameter)=new Variable((yyvsp[-2].sval),(yyvsp[0].my_implement),paraNum); paraNum++;;}
    break;

  case 83:
#line 203 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("TYPE EXPECTED AFTER ':' IN VARIABLE DEFINATION"); ;}
    break;

  case 84:
#line 204 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("':' MISSING");;}
    break;

  case 91:
#line 221 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->VariablesClass_Action((yyvsp[-3].my_modifier)->modi,(yyvsp[0].my_implement),(yyvsp[-2].sval),line);;}
    break;

  case 93:
#line 222 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {meme.clear(); my_action->VariablesClass_Action(meme,(yyvsp[0].my_implement),(yyvsp[-2].sval),line);;}
    break;

  case 95:
#line 223 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("TYPE EXPECTED"); my_action->sure=false;;}
    break;

  case 96:
#line 223 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure=true;;}
    break;

  case 97:
#line 224 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("TYPE EXPECTED"); my_action->sure=false;;}
    break;

  case 98:
#line 224 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure=true;;}
    break;

  case 99:
#line 226 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("';' OR '[' OR '<-' MISSING");;}
    break;

  case 100:
#line 227 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("';' OR '[' OR '<-' MISSING");;}
    break;

  case 101:
#line 230 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->ArraysClass_Action((yyvsp[-7].my_modifier)->modi,(yyvsp[-4].my_implement),(yyvsp[-6].sval),(yyvsp[-2].ival),line);}
    break;

  case 102:
#line 232 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {meme.clear(); my_action->ArraysClass_Action(meme,(yyvsp[-4].my_implement),(yyvsp[-6].sval),(yyvsp[-2].ival),line);}
    break;

  case 103:
#line 234 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->DynArraysClass_Action((yyvsp[-6].my_modifier)->modi,(yyvsp[-3].my_implement),(yyvsp[-5].sval),line);}
    break;

  case 104:
#line 235 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {meme.clear(); my_action->DynArraysClass_Action(meme,(yyvsp[-3].my_implement),(yyvsp[-5].sval),line);}
    break;

  case 105:
#line 237 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("1 Demonitions is the max for arrays");;}
    break;

  case 106:
#line 238 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("1 Demonitions is the max for arrays");;}
    break;

  case 108:
#line 242 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("']' MISSING");;}
    break;

  case 109:
#line 243 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("MUST DEFINE ARRAY LENGTH AT DECLARATION TIME");;}
    break;

  case 110:
#line 244 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("MUST DEFINE AN INTEGER ARRAY LENGTH");;}
    break;

  case 113:
#line 247 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("']' MISSING"); ;}
    break;

  case 114:
#line 248 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("MUST DEFINE ARRAY LENGTH AT DECLARATION TIME");;}
    break;

  case 115:
#line 249 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("MUST DEFINE AN INTEGER ARRAY LENGTH");;}
    break;

  case 117:
#line 253 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->MethodsClass_Action((yyvsp[-7].my_modifier)->modi,(yyvsp[-4].my_parameterss)->parameter,(yyvsp[-1].my_implement),(yyvsp[-6].sval),line);;}
    break;

  case 118:
#line 253 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {paraNum = 0;;}
    break;

  case 119:
#line 255 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {para.clear(); my_action->MethodsClass_Action((yyvsp[-6].my_modifier)->modi,para,(yyvsp[-1].my_implement),(yyvsp[-5].sval),line);;}
    break;

  case 121:
#line 257 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {meme.clear(); my_action->MethodsClass_Action(meme,(yyvsp[-4].my_parameterss)->parameter,(yyvsp[-1].my_implement),(yyvsp[-6].sval),line);;}
    break;

  case 122:
#line 257 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {paraNum = 0;;}
    break;

  case 123:
#line 259 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {para.clear(); meme.clear(); my_action->MethodsClass_Action(meme,para,(yyvsp[-1].my_implement),(yyvsp[-5].sval),line);;}
    break;

  case 125:
#line 261 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("')' MISSING"); my_action->sure__=false;;}
    break;

  case 126:
#line 261 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 127:
#line 262 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("RETURN TYPE EXPECTED"); my_action->sure__=false;;}
    break;

  case 128:
#line 262 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 129:
#line 263 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("':' MISSING");my_action->sure__=false;;}
    break;

  case 130:
#line 263 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 131:
#line 264 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD EXPECTED");my_action->sure__=false;;}
    break;

  case 132:
#line 264 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 133:
#line 266 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("')' MISSING");my_action->sure__=false; ;}
    break;

  case 134:
#line 266 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 135:
#line 267 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("':' MISSING");my_action->sure__=false;;}
    break;

  case 136:
#line 267 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 137:
#line 268 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("RETURN TYPE EXPECTED");my_action->sure__=false; ;}
    break;

  case 138:
#line 268 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 139:
#line 269 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD EXPECTED");my_action->sure__=false;;}
    break;

  case 140:
#line 269 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 141:
#line 271 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("')' MISSING");my_action->sure__=false; ;}
    break;

  case 142:
#line 271 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 143:
#line 272 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("':' MISSING");my_action->sure__=false;;}
    break;

  case 144:
#line 272 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 145:
#line 273 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("RETURN TYPE EXPECTED");my_action->sure__=false;;}
    break;

  case 146:
#line 273 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 147:
#line 274 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD EXPECTED"); my_action->sure__=false;;}
    break;

  case 148:
#line 274 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 149:
#line 276 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("')' MISSING"); my_action->sure__=false;;}
    break;

  case 150:
#line 276 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 151:
#line 277 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("RETURN TYPE EXPECTED"); my_action->sure__=false;;}
    break;

  case 152:
#line 277 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 153:
#line 278 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("':' MISSING");my_action->sure__=false;;}
    break;

  case 154:
#line 278 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 155:
#line 279 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IS' KEYWORD EXPECTED");my_action->sure__=false;;}
    break;

  case 156:
#line 279 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure__=true;;}
    break;

  case 157:
#line 286 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("ERROR IN CLASS MEMBER DEFINATION"); ;}
    break;

  case 158:
#line 288 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("':' OR '(' MISSING");;}
    break;

  case 159:
#line 289 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("':' OR '(' MISSING");;}
    break;

  case 160:
#line 293 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->AbsMethodsClass_Action((yyvsp[-7].my_modifier)->modi,(yyvsp[-4].my_parameterss)->parameter,(yyvsp[-1].my_implement),(yyvsp[-6].sval),line);;}
    break;

  case 161:
#line 294 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {para.clear(); my_action->AbsMethodsClass_Action((yyvsp[-6].my_modifier)->modi,para,(yyvsp[-1].my_implement),(yyvsp[-5].sval),line);;}
    break;

  case 162:
#line 296 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->My_ref->addRefuse((yyvsp[-5].sval)," : must declared as abstract",(yyvsp[-5].sval),method,line,*new bool);;}
    break;

  case 163:
#line 297 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->My_ref->addRefuse((yyvsp[-6].sval)," : must declared as abstract",(yyvsp[-6].sval),method,line,*new bool);;}
    break;

  case 164:
#line 301 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {
					if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__))
					{
						if ((yyvsp[-1].my_Node)!=NULL)
						{
							my_action->currVariable->val=new Node();
							if (my_action->laterTree)
							{
								Node* expr = new Assignment_Node(new ID_Node(my_action->currVariable),(yyvsp[-1].my_Node));
								my_action->my_laterDef->pointAtAST(expr,my_action->currNamespace,my_action->currClass,NULL,NULL,line);
								my_action->currVariable->val=(yyvsp[-1].my_Node);
							}
							else if (my_action->checkAssignment(my_action->currVariable,new ID_Node(my_action->currVariable),(yyvsp[-1].my_Node),line)->grp!=EMPTY)
								my_action->currVariable->val=(yyvsp[-1].my_Node);
						}
						my_action->laterTree = false;
					}
				;}
    break;

  case 165:
#line 320 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {
					if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__))
					{
						if (my_modifiers::found(my_action->currVariable->modi,Readonly))
						{
							my_action->currVariable->val=new Node();
							my_action->My_ref->addRefuse("readonly variable should assign value at declaration time",my_action->currVariable->name,variable,line,*new bool);
						}
						else
						{
							my_action->currVariable->val=new Node();
							my_action->currVariable->val=Const_Node::buildDefaultConst(my_action->currVariable->varType->implement);
						}
					}
				;}
    break;

  case 166:
#line 337 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->EndFunction(my_action->currClass,(yyvsp[-1].my_AST),line);;}
    break;

  case 167:
#line 338 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->EndFunction(my_action->currClass,NULL,line);;}
    break;

  case 168:
#line 346 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.modi)=Public;;}
    break;

  case 169:
#line 347 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.modi)=Protected;;}
    break;

  case 170:
#line 348 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.modi)=Internal;;}
    break;

  case 171:
#line 349 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.modi)=Private;;}
    break;

  case 172:
#line 350 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.modi)=Static;;}
    break;

  case 173:
#line 351 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.modi)= Readonly;;}
    break;

  case 174:
#line 352 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.modi)=Abstract;;}
    break;

  case 175:
#line 353 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.modi)=Sealed;;}
    break;

  case 176:
#line 354 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.modi)=Override;;}
    break;

  case 177:
#line 355 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.modi)=Virtual;;}
    break;

  case 178:
#line 356 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.modi)=New;;}
    break;

  case 179:
#line 359 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyvsp[-1].my_modifier)->add_modifier((yyvsp[0].modi)); (yyval.my_modifier)=(yyvsp[-1].my_modifier);}
    break;

  case 180:
#line 360 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.my_modifier) = new my_modifiers((yyvsp[0].modi));;}
    break;

  case 181:
#line 365 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyvsp[-2].my_AST)->addNode((yyvsp[0].my_Node)); (yyval.my_AST)=(yyvsp[-2].my_AST);;}
    break;

  case 182:
#line 366 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.my_AST) = new AST((yyvsp[0].my_Node));;}
    break;

  case 183:
#line 369 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyvsp[-6].my_variable)->add_variable(my_action->LetVarDeclaration((yyvsp[-4].sval),(yyvsp[-2].my_implement),line,(yyvsp[0].my_Node))); (yyval.my_variable)=(yyvsp[-6].my_variable);;}
    break;

  case 184:
#line 370 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyvsp[-4].my_variable)->add_variable(my_action->LetVarDeclaration((yyvsp[-2].sval),(yyvsp[0].my_implement),line,Const_Node::buildDefaultConst((yyvsp[0].my_implement)->implement))); (yyval.my_variable)=(yyvsp[-4].my_variable);;}
    break;

  case 185:
#line 371 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("TYPE EXPEXTED");;}
    break;

  case 186:
#line 372 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("':' MISSING");;}
    break;

  case 187:
#line 373 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'IN' KEYWORD EXPECTED");;}
    break;

  case 188:
#line 375 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_variable) = new my_variables(my_action->LetVarDeclaration((yyvsp[-4].sval),(yyvsp[-2].my_implement),line,(yyvsp[0].my_Node)));;}
    break;

  case 189:
#line 376 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_variable) = new my_variables(my_action->LetVarDeclaration((yyvsp[-2].sval),(yyvsp[0].my_implement),line,Const_Node::buildDefaultConst((yyvsp[0].my_implement)->implement)));;}
    break;

  case 190:
#line 377 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("TYPE EXPEXTED");;}
    break;

  case 191:
#line 378 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("':' MISSING");;}
    break;

  case 192:
#line 383 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {
					if ((yyvsp[-3].my_Node)->grp==CONST)
					{
						if ((yyvsp[-5].my_caseExpr) != NULL)
							(yyvsp[-5].my_caseExpr)->addExpr((Const_Node *)(yyvsp[-3].my_Node),(yyvsp[-1].my_Node));
						else
							(yyvsp[-5].my_caseExpr)=new Case_Expr((Const_Node *)(yyvsp[-3].my_Node),(yyvsp[-1].my_Node));
					}
					else
						my_action->My_ref->addRefuse("case expression should be constant","caseExpr",variable,line,*new bool);
					(yyval.my_caseExpr)=(yyvsp[-5].my_caseExpr);
				;}
    break;

  case 193:
#line 395 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("';' MISSING"); ;}
    break;

  case 194:
#line 396 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'=>' MISSING"); ;}
    break;

  case 195:
#line 397 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'ESAC' KEYWORD EXPECTED"); ;}
    break;

  case 196:
#line 400 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {
					if ((yyvsp[-3].my_Node)->grp==CONST) 
						(yyval.my_caseExpr)=new Case_Expr((Const_Node *)(yyvsp[-3].my_Node),(yyvsp[-1].my_Node));
					else
					{
						my_action->My_ref->addRefuse("case expression should be constant","caseExpr",variable,line,ok);
						(yyval.my_caseExpr) = NULL;
					}
				;}
    break;

  case 197:
#line 409 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("';' MISSING");;}
    break;

  case 198:
#line 410 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'=>' MISSING");;}
    break;

  case 199:
#line 414 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {
				my_action->FirstDad=true;
				my_action->laterTree = false;
				if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__))
				{
					if ((yyvsp[-1].my_Node)->grp!=EMPTY)
					{
						if ((yyvsp[-2].my_AST)!=NULL)
							(yyvsp[-2].my_AST)->addNode((yyvsp[-1].my_Node));
						else
							(yyvsp[-2].my_AST) = new AST((yyvsp[-1].my_Node));
					}
					(yyval.my_AST)=(yyvsp[-2].my_AST);
				}
			;}
    break;

  case 200:
#line 431 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {
				my_action->FirstDad=true;
				my_action->laterTree = false;
				if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__))
					if ((yyvsp[-1].my_Node)->grp!=EMPTY)
						(yyval.my_AST) = new AST((yyvsp[-1].my_Node));
			;}
    break;

  case 201:
#line 438 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.my_AST) = (yyvsp[-2].my_AST);;}
    break;

  case 202:
#line 439 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.my_AST) = new AST();;}
    break;

  case 203:
#line 441 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.my_AST) = new AST();;}
    break;

  case 204:
#line 445 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->VariableDeclaration((yyvsp[0].my_implement),(yyvsp[-2].sval),line,Const_Node::buildDefaultConst((yyvsp[0].my_implement)->implement));;}
    break;

  case 205:
#line 446 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->ArrayDeclaration((yyvsp[-3].my_implement),(yyvsp[-5].sval),(yyvsp[-1].ival),line,Const_Node::buildDefaultConst((yyvsp[-3].my_implement)->implement));;}
    break;

  case 206:
#line 447 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node)=my_action->VariableDeclaration((yyvsp[-2].my_implement),(yyvsp[-4].sval),line,(yyvsp[0].my_Node));;}
    break;

  case 207:
#line 448 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->DynArrayDeclaration((yyvsp[-2].my_implement),(yyvsp[-4].sval),line,Const_Node::buildDefaultConst((yyvsp[-2].my_implement)->implement));;}
    break;

  case 208:
#line 449 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_implements* Qid = new my_implements((yyvsp[-10].sval)); my_implements* imp = new my_implements((yyvsp[-1].sval)); if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) my_action->DynArrayDeclaration((yyvsp[-8].my_implement),(yyvsp[-10].sval),line,Const_Node::buildDefaultConst((yyvsp[-8].my_implement)->implement)); (yyval.my_Node) = my_action->InitDynArray(Qid,(yyvsp[-3].my_implement),my_action->CallVariable(imp,false,line),line);;}
    break;

  case 209:
#line 450 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_implements* Qid = new my_implements((yyvsp[-10].sval)); Const_Type CT; CT.iv=(yyvsp[-1].ival); CT.type=1; Const_Node * n =new Const_Node(CT);  if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) my_action->DynArrayDeclaration((yyvsp[-8].my_implement),(yyvsp[-10].sval),line,Const_Node::buildDefaultConst((yyvsp[-8].my_implement)->implement)); (yyval.my_Node) = my_action->InitDynArray(Qid,(yyvsp[-3].my_implement),n,line);;}
    break;

  case 210:
#line 453 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node)=my_action->CallVariable((yyvsp[0].my_implement),false,line);;}
    break;

  case 211:
#line 455 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Const_Type CT; CT.iv=(yyvsp[-1].ival); CT.type=1; Const_Node * n =new Const_Node(CT); if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node)=my_action->CallArrVar((yyvsp[-3].my_implement),n,line);;}
    break;

  case 212:
#line 456 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_implements* imp = new my_implements((yyvsp[-1].sval)); if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node)=my_action->CallArrVar((yyvsp[-3].my_implement),my_action->CallVariable(imp,false,line),line);;}
    break;

  case 213:
#line 458 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node)=my_action->AssignVariable((yyvsp[-2].my_implement),(yyvsp[0].my_Node),line);;}
    break;

  case 214:
#line 459 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Const_Type CT; CT.iv=(yyvsp[-3].ival); CT.type=1; Const_Node * n =new Const_Node(CT); if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node)=my_action->AssignArrVar((yyvsp[-5].my_implement),n,(yyvsp[0].my_Node),line);;}
    break;

  case 215:
#line 460 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_implements* imp = new my_implements((yyvsp[-3].sval)); if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node)=my_action->AssignArrVar((yyvsp[-5].my_implement),my_action->CallVariable(imp,false,line),(yyvsp[0].my_Node),line);;}
    break;

  case 216:
#line 463 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->CallFunction((yyvsp[-2].my_implement),new AST(),line);;}
    break;

  case 217:
#line 464 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->CallFunction((yyvsp[-3].my_implement),(yyvsp[-1].my_AST),line);;}
    break;

  case 218:
#line 467 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->CallConstructor((yyvsp[-2].my_implement),new AST(),line);;}
    break;

  case 219:
#line 468 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->CallConstructor((yyvsp[-3].my_implement),(yyvsp[-1].my_AST),line);;}
    break;

  case 220:
#line 469 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->CallFather(new AST(),line);;}
    break;

  case 221:
#line 470 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->CallFather((yyvsp[-1].my_AST),line);;}
    break;

  case 222:
#line 472 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_implements* imp = new my_implements((yyvsp[-1].sval)); if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->InitDynArray((yyvsp[-6].my_implement),(yyvsp[-3].my_implement),my_action->CallVariable(imp,false,line),line);;}
    break;

  case 223:
#line 473 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Const_Type CT; CT.iv=(yyvsp[-1].ival); CT.type=1; Const_Node * n =new Const_Node(CT);  if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->InitDynArray((yyvsp[-6].my_implement),(yyvsp[-3].my_implement),n,line);;}
    break;

  case 224:
#line 476 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->AssignClassVar((yyvsp[-4].my_Node),(yyvsp[-2].sval),(yyvsp[0].my_Node),line);;}
    break;

  case 225:
#line 477 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->CallClassVar((yyvsp[-2].my_Node),(yyvsp[0].sval),line);;}
    break;

  case 226:
#line 483 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->CallClassFunc((yyvsp[-4].my_Node),(yyvsp[-2].sval),new AST(),new my_implements(),line);;}
    break;

  case 227:
#line 484 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->CallClassFunc((yyvsp[-5].my_Node),(yyvsp[-3].sval),(yyvsp[-1].my_AST),new my_implements(),line);;}
    break;

  case 228:
#line 487 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.my_Node)=(yyvsp[-1].my_Node);;}
    break;

  case 229:
#line 490 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->Casting((yyvsp[0].my_implement),(yyvsp[-2].my_Node),line);;}
    break;

  case 230:
#line 493 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if (my_action->laterTree) laterLoop=true; my_action->laterTree = false; Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(tmp); my_action->currMethod->LocalScopes.push_back(my_action->currScope);;}
    break;

  case 231:
#line 494 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->currScope->Body=(yyvsp[0].my_AST); prevScope = my_action->currScope;;}
    break;

  case 232:
#line 495 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(my_action->currScope->parent); my_action->currMethod->LocalScopes.push_back(my_action->currScope);;}
    break;

  case 233:
#line 496 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->currScope->Body=(yyvsp[0].my_AST);;}
    break;

  case 234:
#line 497 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(); my_action->currScope = tmp->parent;
			if (laterLoop)
			{
				(yyval.my_Node) = new IF_Node((yyvsp[-9].my_Node),prevScope,tmp);
				my_action->my_laterDef->pointAtAST((yyval.my_Node),my_action->currNamespace,my_action->currClass,my_action->currMethod,my_action->currScope,line);
			}
			else
				(yyval.my_Node) = my_action->IfStmt((yyvsp[-9].my_Node),prevScope,tmp,line);
			laterLoop = false;;}
    break;

  case 235:
#line 508 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if (my_action->laterTree) laterLoop=true; my_action->laterTree = false; Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(tmp); my_action->currMethod->LocalScopes.push_back(my_action->currScope);;}
    break;

  case 236:
#line 509 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->currScope->Body=(yyvsp[0].my_AST);;}
    break;

  case 237:
#line 510 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(); my_action->currScope = tmp->parent;
			if (laterLoop)
			{
				(yyval.my_Node) = new WHILE_Node((yyvsp[-5].my_Node),tmp);
				my_action->my_laterDef->pointAtAST((yyval.my_Node),my_action->currNamespace,my_action->currClass,my_action->currMethod,my_action->currScope,line);
			}
			else
				(yyval.my_Node) = my_action->WhileStmt((yyvsp[-5].my_Node),tmp,line);
			laterLoop = false;;}
    break;

  case 238:
#line 521 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(tmp); my_action->currMethod->LocalScopes.push_back(my_action->currScope);;}
    break;

  case 239:
#line 522 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->currScope->Body=(yyvsp[0].my_AST);;}
    break;

  case 240:
#line 523 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(); my_action->currScope =tmp->parent;(yyval.my_Node)=tmp;;}
    break;

  case 241:
#line 525 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->My_wrn->addWarn("SCOPE WITHOUT BODY. Droped","SCOPE",line); (yyval.my_Node) = new Node();;}
    break;

  case 242:
#line 528 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)&&(my_action->currMethod!=NULL)) {Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(tmp);};}
    break;

  case 243:
#line 529 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)&&(my_action->currMethod!=NULL)) {my_action->currScope->addLocals(*(yyvsp[0].my_variable));};}
    break;

  case 244:
#line 529 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)&&(my_action->currMethod!=NULL)) my_action->currScope->Body=new AST((yyvsp[0].my_Node));;}
    break;

  case 245:
#line 530 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)&&(my_action->currMethod!=NULL)) {(yyval.my_Node) = my_action->LetStmt(my_action->currScope,line); Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope=new Scope();my_action->currScope = tmp->parent;};}
    break;

  case 246:
#line 533 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {(yyval.my_Node)=my_action->CaseStmt((yyvsp[-3].my_Node),*(yyvsp[-1].my_caseExpr),ok,line);;}
    break;

  case 247:
#line 536 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->ArthmExpr(SUM,(yyvsp[-2].my_Node),(yyvsp[0].my_Node),line);;}
    break;

  case 248:
#line 537 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->ArthmExpr(SUB,(yyvsp[-2].my_Node),(yyvsp[0].my_Node),line);;}
    break;

  case 249:
#line 538 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->ArthmExpr(MULT,(yyvsp[-2].my_Node),(yyvsp[0].my_Node),line);;}
    break;

  case 250:
#line 539 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->ArthmExpr(DIVS,(yyvsp[-2].my_Node),(yyvsp[0].my_Node),line);;}
    break;

  case 251:
#line 540 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->ComparisonExpr(LESS,(yyvsp[-2].my_Node),(yyvsp[0].my_Node),line);;}
    break;

  case 252:
#line 541 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->ComparisonExpr(LSEQ,(yyvsp[-2].my_Node),(yyvsp[0].my_Node),line);;}
    break;

  case 253:
#line 542 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->ComparisonExpr(MORE,(yyvsp[-2].my_Node),(yyvsp[0].my_Node),line);;}
    break;

  case 254:
#line 543 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->ComparisonExpr(MREQ,(yyvsp[-2].my_Node),(yyvsp[0].my_Node),line);;}
    break;

  case 255:
#line 544 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->ComparisonExpr(EQL,(yyvsp[-2].my_Node),(yyvsp[0].my_Node),line);;}
    break;

  case 256:
#line 545 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->LogicExpr(AND,(yyvsp[-2].my_Node),(yyvsp[0].my_Node),line);;}
    break;

  case 257:
#line 546 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->LogicExpr(OR,(yyvsp[-2].my_Node),(yyvsp[0].my_Node),line);;}
    break;

  case 258:
#line 549 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->UnaryExpr(NULLCHECK,(yyvsp[0].my_Node),line);;}
    break;

  case 259:
#line 550 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->UnaryExpr(LCOMP,(yyvsp[0].my_Node),line);;}
    break;

  case 260:
#line 551 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->UnaryExpr(COMP,(yyvsp[0].my_Node),line);;}
    break;

  case 261:
#line 552 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->UnaryExpr(DEL,(yyvsp[0].my_Node),line);;}
    break;

  case 262:
#line 554 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) (yyval.my_Node) = my_action->ReturnExpr((yyvsp[0].my_Node),line); else (yyval.my_Node)=new Node();;}
    break;

  case 263:
#line 557 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Const_Type CT; CT.iv=-(yyvsp[0].ival); CT.type=1; (yyval.my_Node)=new Const_Node(CT);;}
    break;

  case 264:
#line 558 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Const_Type CT; CT.iv=(yyvsp[0].ival); CT.type=1; (yyval.my_Node)=new Const_Node(CT);;}
    break;

  case 265:
#line 559 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Const_Type CT; CT.iv=(yyvsp[0].ival); CT.type=1; (yyval.my_Node)=new Const_Node(CT);;}
    break;

  case 266:
#line 560 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Const_Type CT; CT.fv=(yyvsp[0].fval); CT.type=2; (yyval.my_Node)=new Const_Node(CT);;}
    break;

  case 267:
#line 561 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {char * s = new char; s = (yyvsp[0].sval); Const_Type CT; CT.chv=s; CT.type=3; (yyval.my_Node)=new Const_Node(CT);;}
    break;

  case 268:
#line 562 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Const_Type CT; CT.bv=true; CT.type=4; (yyval.my_Node)=new Const_Node(CT);;}
    break;

  case 269:
#line 563 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Const_Type CT; CT.bv=false; CT.type=4; (yyval.my_Node)=new Const_Node(CT);;}
    break;

  case 270:
#line 564 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {Const_Type CT; CT.type=0; (yyval.my_Node)=new Const_Node(CT);;}
    break;

  case 271:
#line 574 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("TYPE EXPECTED"); ;}
    break;

  case 272:
#line 586 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("TYPE EXPECTED");;}
    break;

  case 273:
#line 604 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'OF' KEYWORD EXPECTED");;}
    break;

  case 274:
#line 607 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'false' KEYWORD EXPECTED"); ;}
    break;

  case 275:
#line 608 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'true' KEYWORD EXPECTED"); ;}
    break;

  case 276:
#line 613 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->Interface_Action((yyvsp[-5].my_modifier)->modi,(yyvsp[-1].my_QIDList)->lists,(yyvsp[-3].sval),line);;}
    break;

  case 277:
#line 613 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->closeInterface_Action(line);;}
    break;

  case 278:
#line 615 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {keke.clear(); my_action->Interface_Action((yyvsp[-3].my_modifier)->modi,keke,(yyvsp[-1].sval),line);;}
    break;

  case 279:
#line 615 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->closeInterface_Action(line);;}
    break;

  case 280:
#line 617 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {meme.clear(); my_action->Interface_Action(meme,(yyvsp[-1].my_QIDList)->lists,(yyvsp[-3].sval),line);;}
    break;

  case 281:
#line 617 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->closeInterface_Action(line);;}
    break;

  case 282:
#line 619 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {meme.clear(); keke.clear(); my_action->Interface_Action(meme,keke,(yyvsp[-1].sval),line);;}
    break;

  case 283:
#line 619 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->closeInterface_Action(line);;}
    break;

  case 284:
#line 621 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'{' MISSING"); my_action->sure_=false;;}
    break;

  case 285:
#line 621 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 286:
#line 622 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("ERROR IN INHERITANCE LIST"); my_action->sure_=false;;}
    break;

  case 287:
#line 622 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 288:
#line 623 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'{' MISSING or 'INHERITS' KEYWORD EXPECTED"); my_action->sure_=false;;}
    break;

  case 289:
#line 623 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 290:
#line 624 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("ERROR IN INTERFACE DEFINATION"); my_action->sure_=false;;}
    break;

  case 291:
#line 624 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 292:
#line 626 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'{' MISSING"); my_action->sure_=false;;}
    break;

  case 293:
#line 626 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 294:
#line 627 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("ERROR IN INHERITANCE LIST"); my_action->sure_=false;;}
    break;

  case 295:
#line 627 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 296:
#line 628 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'{' MISSING or 'INHERITS' KEYWORD EXPECTED"); my_action->sure_=false;;}
    break;

  case 297:
#line 628 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 298:
#line 629 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("ERROR IN INTERFACE DEFINATION"); my_action->sure_=false;;}
    break;

  case 299:
#line 629 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->sure_=true;;}
    break;

  case 300:
#line 631 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'{' MISSING");;}
    break;

  case 301:
#line 632 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'{' MISSING");;}
    break;

  case 302:
#line 633 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'{' MISSING");;}
    break;

  case 303:
#line 634 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'{' MISSING");;}
    break;

  case 305:
#line 638 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror(" '}' MISSING CAN NOT DECLARE AN INNER NAMESPACE/INTERFACE/CLASS");;}
    break;

  case 309:
#line 647 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {para.clear(); my_action->MehtodsInterface_Action(para,(yyvsp[-1].my_implement),(yyvsp[-5].sval),line);;}
    break;

  case 310:
#line 648 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {my_action->MehtodsInterface_Action((yyvsp[-4].my_parameterss)->parameter,(yyvsp[-1].my_implement),(yyvsp[-6].sval),line);;}
    break;

  case 311:
#line 650 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("';' MISSING");;}
    break;

  case 312:
#line 651 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("')' MISSING");;}
    break;

  case 313:
#line 652 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("'(' MISSING ");;}
    break;

  case 314:
#line 653 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("ERROR IN FUNCTION DEFINATION");;}
    break;

  case 315:
#line 655 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("';' MISSING");;}
    break;

  case 316:
#line 656 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("')' MISSING");;}
    break;

  case 317:
#line 657 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("INTERFACE FUNCTIONS CAN NOT HAVE BODY");;}
    break;

  case 318:
#line 658 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("INTERFACE FUNCTIONS CAN NOT HAVE BODY");;}
    break;

  case 319:
#line 659 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("INTERFACE FUNCTIONS CAN NOT HAVE BODY");;}
    break;

  case 320:
#line 660 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"
    {yyerror("INTERFACE FUNCTIONS CAN NOT HAVE BODY");;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3554 "yacc.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;


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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  int yytype = YYTRANSLATE (yychar);
	  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
	  YYSIZE_T yysize = yysize0;
	  YYSIZE_T yysize1;
	  int yysize_overflow = 0;
	  char *yymsg = 0;
#	  define YYERROR_VERBOSE_ARGS_MAXIMUM 5
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;

#if 0
	  /* This is so xgettext sees the translatable formats that are
	     constructed on the fly.  */
	  YY_("syntax error, unexpected %s");
	  YY_("syntax error, unexpected %s, expecting %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
#endif
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
	  int yychecklim = YYLAST - yyn;
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
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + yystrlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow && yysize <= YYSTACK_ALLOC_MAXIMUM)
	    yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg)
	    {
	      /* Avoid sprintf, as that infringes on the user's name space.
		 Don't have undefined behavior even if the translation
		 produced a string with the wrong number of "%s"s.  */
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
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
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      goto yyexhaustedlab;
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (0)
     goto yyerrorlab;

yyvsp -= yylen;
  yyssp -= yylen;
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


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK;
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 663 "c:\\Users\\SONY\\Desktop\\compiler - with code generate - Copy - Copy\\LexTest\\yacc.y"

   /***********UserCode**************/

void yyerror(char *s) 
{
  //fprintf(stderr, "%s\n", s);
  Error_info *R=new Error_info();
  R->msg=s ;  R->line=line;   R->col=col;
  my_action->My_err-> insert_Err (R);
}

int yylex()
{
	return lexer->yylex();
}

char * copystr(const char* s)
{
	char * res;
	if (s==NULL) return NULL;
	if( (res=(char*)malloc(strlen(s)+1))!=NULL)
		strcpy(res,s);
	else{
		yyerror("there are not enough memory");
		return 0;
	}		
	return res;
}

//======================================//

void main(void)
{
	//const char* A="read.txt" ;
	//ifstream *in=new ifstream(A);
	//if (in)
	//	lexer->yyrestart(in);
	//else
	//	cout <<"ERORR FILE NOT FOUND";
	
	Parser* p = new Parser();
	p->parse();
	my_action->scanBottomUp();
	if (!my_action->my_check->checkEntryPoint())
		my_action->My_ref->addRefuse("entry point ambigious: should be main():SELF_TYPE","main",method,0,*new bool);
	
	cout <<"My Symbol Table is "<<endl;
	my_action->Print_SymbolTable();
	cout<<endl;
 
	cout <<"My Errors are "<<endl;
	my_action->My_err->printList();
	cout<<endl;
    
	cout <<"My Refuse Addings are "<<endl;
	my_action->My_ref->printList();
	cout<<endl;

	cout <<"My Warnings are "<<endl;
	my_action->My_wrn->printList();
	
	if (my_action->hasNoErrors())
		my_action->generateCode();
}

//==================================//
