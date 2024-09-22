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
    T_INCLUDE = 258,               /* T_INCLUDE  */
    T_IDH = 259,                   /* T_IDH  */
    T_TYPE = 260,                  /* T_TYPE  */
    T_RETURN = 261,                /* T_RETURN  */
    T_COUT = 262,                  /* T_COUT  */
    T_CIN = 263,                   /* T_CIN  */
    T_IDENTIFIER = 264,            /* T_IDENTIFIER  */
    T_ADDEQ = 265,                 /* T_ADDEQ  */
    T_MINEQ = 266,                 /* T_MINEQ  */
    T_MULEQ = 267,                 /* T_MULEQ  */
    T_DIVEQ = 268,                 /* T_DIVEQ  */
    T_FOR = 269,                   /* T_FOR  */
    T_IF = 270,                    /* T_IF  */
    T_ELSE = 271,                  /* T_ELSE  */
    T_LTEQ = 272,                  /* T_LTEQ  */
    T_GTEQ = 273,                  /* T_GTEQ  */
    T_NEQEQ = 274,                 /* T_NEQEQ  */
    T_EQEQ = 275,                  /* T_EQEQ  */
    T_OROR = 276,                  /* T_OROR  */
    T_ANDAND = 277,                /* T_ANDAND  */
    T_OR = 278,                    /* T_OR  */
    T_AND = 279,                   /* T_AND  */
    T_XOR = 280,                   /* T_XOR  */
    T_LRSHIFT = 281,               /* T_LRSHIFT  */
    T_LLSHIFT = 282,               /* T_LLSHIFT  */
    T_WHILE = 283,                 /* T_WHILE  */
    T_MAIN = 284,                  /* T_MAIN  */
    T_STRING = 285,                /* T_STRING  */
    T_STRUCT = 286,                /* T_STRUCT  */
    T_CLASS = 287,                 /* T_CLASS  */
    T_PRIVATE = 288,               /* T_PRIVATE  */
    T_PUBLIC = 289,                /* T_PUBLIC  */
    T_PROTECTED = 290,             /* T_PROTECTED  */
    T_ADDADD = 291,                /* T_ADDADD  */
    T_MINMIN = 292,                /* T_MINMIN  */
    T_STRING_VAL = 293,            /* T_STRING_VAL  */
    T_CHAR_VAL = 294,              /* T_CHAR_VAL  */
    T_INTEGER_VAL = 295,           /* T_INTEGER_VAL  */
    T_FLOAT_VAL = 296              /* T_FLOAT_VAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define T_INCLUDE 258
#define T_IDH 259
#define T_TYPE 260
#define T_RETURN 261
#define T_COUT 262
#define T_CIN 263
#define T_IDENTIFIER 264
#define T_ADDEQ 265
#define T_MINEQ 266
#define T_MULEQ 267
#define T_DIVEQ 268
#define T_FOR 269
#define T_IF 270
#define T_ELSE 271
#define T_LTEQ 272
#define T_GTEQ 273
#define T_NEQEQ 274
#define T_EQEQ 275
#define T_OROR 276
#define T_ANDAND 277
#define T_OR 278
#define T_AND 279
#define T_XOR 280
#define T_LRSHIFT 281
#define T_LLSHIFT 282
#define T_WHILE 283
#define T_MAIN 284
#define T_STRING 285
#define T_STRUCT 286
#define T_CLASS 287
#define T_PRIVATE 288
#define T_PUBLIC 289
#define T_PROTECTED 290
#define T_ADDADD 291
#define T_MINMIN 292
#define T_STRING_VAL 293
#define T_CHAR_VAL 294
#define T_INTEGER_VAL 295
#define T_FLOAT_VAL 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 38 "icg_grammar.y"

    	char cval;
		int ival;
		float fval;
		char *sval;
		//valtypes *allval;
		struct{
			char* next;
			char code[1500];
			char addr[50]; 
			char* true_label;
			char* false_label;
		}node;		

#line 164 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
