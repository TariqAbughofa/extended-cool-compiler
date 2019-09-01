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
/* Line 1447 of yacc.c.  */
#line 205 "yacc.hpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



