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
#line 1 "1805068_parser.y"

#	include <iostream>
#	include <cstdlib>
#	include <cstring>
#	include <cmath>
#	include "1805068_SymbolTable.h"
#	include "Assembly.h"
#	include "util.h"
#	include <string>
#	include <regex>
using namespace std;

int yyparse(void);
int yylex(void);

extern int yylineno;
extern FILE *yyin;
int errorCount = 0;

SymbolTable *table;

FILE *logFile;
FILE *errorFile;
FILE *inputFile;
FILE *codeFile;

string str;
string vartype;
string program = "";
string statementsStr = "";
string returnType;

int returnLineNo;

// ASM  Variables
int funcVariableCount = 0;
int funcParameterCount = 0;
int addOrSub = 0;
SymbolInfo *currentFunction;
bool inFactorArgList = false;
int labelCount = 0;

string logicOpLabel1, logicOpLabel2, logicOpLabel3;
string ifLabel1, ifLabel2, ifLabel3;
string forLabel1, forLabel2, forLabel3, forExprStmt;

void yyerror(char *s)
{
	fprintf(logFile, "Error at line %d: %s\n\n", yylineno, s);
	fprintf(errorFile, "Error at line %d: %s\n\n", yylineno, s);
	errorCount++;
}

string newLabel()
{
	return "label_" + to_string(labelCount++);
}

#line 130 "1805068_parser.tab.c"

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

#include "1805068_parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_FOR = 5,                        /* FOR  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_ID = 7,                         /* ID  */
  YYSYMBOL_LPAREN = 8,                     /* LPAREN  */
  YYSYMBOL_RPAREN = 9,                     /* RPAREN  */
  YYSYMBOL_SEMICOLON = 10,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 11,                     /* COMMA  */
  YYSYMBOL_LCURL = 12,                     /* LCURL  */
  YYSYMBOL_RCURL = 13,                     /* RCURL  */
  YYSYMBOL_INT = 14,                       /* INT  */
  YYSYMBOL_FLOAT = 15,                     /* FLOAT  */
  YYSYMBOL_VOID = 16,                      /* VOID  */
  YYSYMBOL_LTHIRD = 17,                    /* LTHIRD  */
  YYSYMBOL_CONST_INT = 18,                 /* CONST_INT  */
  YYSYMBOL_RTHIRD = 19,                    /* RTHIRD  */
  YYSYMBOL_PRINTLN = 20,                   /* PRINTLN  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_ASSIGNOP = 22,                  /* ASSIGNOP  */
  YYSYMBOL_LOGICOP = 23,                   /* LOGICOP  */
  YYSYMBOL_RELOP = 24,                     /* RELOP  */
  YYSYMBOL_MULOP = 25,                     /* MULOP  */
  YYSYMBOL_ADDOP = 26,                     /* ADDOP  */
  YYSYMBOL_CONST_FLOAT = 27,               /* CONST_FLOAT  */
  YYSYMBOL_NOT = 28,                       /* NOT  */
  YYSYMBOL_INCOP = 29,                     /* INCOP  */
  YYSYMBOL_DECOP = 30,                     /* DECOP  */
  YYSYMBOL_DOUBLE = 31,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 32,                      /* CHAR  */
  YYSYMBOL_MAIN = 33,                      /* MAIN  */
  YYSYMBOL_CONST_CHAR = 34,                /* CONST_CHAR  */
  YYSYMBOL_STRING = 35,                    /* STRING  */
  YYSYMBOL_UNRECOG = 36,                   /* UNRECOG  */
  YYSYMBOL_LOWER_THAN_ELSE = 37,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_start = 39,                     /* start  */
  YYSYMBOL_40_1 = 40,                      /* $@1  */
  YYSYMBOL_program = 41,                   /* program  */
  YYSYMBOL_unit = 42,                      /* unit  */
  YYSYMBOL_func_declaration = 43,          /* func_declaration  */
  YYSYMBOL_func_definition = 44,           /* func_definition  */
  YYSYMBOL_45_2 = 45,                      /* $@2  */
  YYSYMBOL_46_3 = 46,                      /* $@3  */
  YYSYMBOL_parameter_list = 47,            /* parameter_list  */
  YYSYMBOL_compound_statement = 48,        /* compound_statement  */
  YYSYMBOL_49_4 = 49,                      /* $@4  */
  YYSYMBOL_50_5 = 50,                      /* $@5  */
  YYSYMBOL_var_declaration = 51,           /* var_declaration  */
  YYSYMBOL_type_specifier = 52,            /* type_specifier  */
  YYSYMBOL_declaration_list = 53,          /* declaration_list  */
  YYSYMBOL_statements = 54,                /* statements  */
  YYSYMBOL_statement = 55,                 /* statement  */
  YYSYMBOL_56_6 = 56,                      /* $@6  */
  YYSYMBOL_57_7 = 57,                      /* $@7  */
  YYSYMBOL_58_8 = 58,                      /* $@8  */
  YYSYMBOL_59_9 = 59,                      /* $@9  */
  YYSYMBOL_60_10 = 60,                     /* $@10  */
  YYSYMBOL_dummy = 61,                     /* dummy  */
  YYSYMBOL_expression_statement = 62,      /* expression_statement  */
  YYSYMBOL_variable = 63,                  /* variable  */
  YYSYMBOL_expression = 64,                /* expression  */
  YYSYMBOL_65_11 = 65,                     /* $@11  */
  YYSYMBOL_logic_expression = 66,          /* logic_expression  */
  YYSYMBOL_67_12 = 67,                     /* $@12  */
  YYSYMBOL_rel_expression = 68,            /* rel_expression  */
  YYSYMBOL_69_13 = 69,                     /* $@13  */
  YYSYMBOL_simple_expression = 70,         /* simple_expression  */
  YYSYMBOL_71_14 = 71,                     /* $@14  */
  YYSYMBOL_term = 72,                      /* term  */
  YYSYMBOL_73_15 = 73,                     /* $@15  */
  YYSYMBOL_unary_expression = 74,          /* unary_expression  */
  YYSYMBOL_factor = 75,                    /* factor  */
  YYSYMBOL_76_16 = 76,                     /* $@16  */
  YYSYMBOL_argument_list = 77,             /* argument_list  */
  YYSYMBOL_arguments = 78                  /* arguments  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   221

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  163

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


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
      35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    77,    77,    77,    86,    93,   101,   106,   110,   116,
     161,   207,   246,   288,   287,   473,   472,   634,   640,   646,
     652,   658,   669,   677,   677,   688,   688,   699,   707,   766,
     808,   809,   810,   813,   819,   825,   831,   836,   844,   850,
     859,   865,   869,   869,   876,   880,   886,   875,   901,   913,
     912,   926,   932,   960,   972,   986,   995,  1000,  1004,  1010,
    1016,  1025,  1043,  1080,  1085,  1084,  1159,  1164,  1163,  1187,
    1192,  1191,  1232,  1237,  1236,  1270,  1282,  1282,  1351,  1356,
    1361,  1367,  1398,  1398,  1478,  1483,  1492,  1496,  1530,  1564,
    1568,  1574,  1580
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
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "FOR",
  "WHILE", "ID", "LPAREN", "RPAREN", "SEMICOLON", "COMMA", "LCURL",
  "RCURL", "INT", "FLOAT", "VOID", "LTHIRD", "CONST_INT", "RTHIRD",
  "PRINTLN", "RETURN", "ASSIGNOP", "LOGICOP", "RELOP", "MULOP", "ADDOP",
  "CONST_FLOAT", "NOT", "INCOP", "DECOP", "DOUBLE", "CHAR", "MAIN",
  "CONST_CHAR", "STRING", "UNRECOG", "LOWER_THAN_ELSE", "$accept", "start",
  "$@1", "program", "unit", "func_declaration", "func_definition", "$@2",
  "$@3", "parameter_list", "compound_statement", "$@4", "$@5",
  "var_declaration", "type_specifier", "declaration_list", "statements",
  "statement", "$@6", "$@7", "$@8", "$@9", "$@10", "dummy",
  "expression_statement", "variable", "expression", "$@11",
  "logic_expression", "$@12", "rel_expression", "$@13",
  "simple_expression", "$@14", "term", "$@15", "unary_expression",
  "factor", "$@16", "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-103)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-43)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -103,    31,    48,  -103,  -103,  -103,  -103,    48,  -103,  -103,
    -103,  -103,    45,  -103,    37,    10,    74,    -1,   112,  -103,
      77,    14,    23,    50,    62,  -103,    87,    81,    92,  -103,
      88,    43,    48,  -103,  -103,  -103,  -103,    86,  -103,   100,
    -103,   101,  -103,    88,   123,   113,    21,   111,   129,   131,
      52,    21,  -103,  -103,  -103,   139,    21,    21,  -103,    21,
     140,  -103,   151,   128,  -103,    88,  -103,    57,    17,  -103,
     137,    54,   142,  -103,  -103,  -103,  -103,  -103,  -103,   155,
      21,    15,    21,  -103,    21,   164,   168,    64,    95,  -103,
    -103,   165,   184,    58,  -103,   172,  -103,  -103,  -103,  -103,
    -103,   170,  -103,  -103,  -103,  -103,  -103,  -103,   177,  -103,
     179,    21,   162,  -103,   186,   183,  -103,  -103,   156,   136,
     180,    21,  -103,    21,    21,    21,    21,  -103,    15,   184,
    -103,   192,   195,  -103,    75,  -103,  -103,  -103,    82,  -103,
    -103,   181,   142,  -103,   184,  -103,  -103,  -103,    21,   193,
    -103,  -103,   204,    21,  -103,  -103,  -103,  -103,   184,   200,
    -103,   184,  -103
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,    30,    31,    32,     3,     5,     7,
       8,     6,     0,     4,    36,     0,     0,     0,     0,    28,
       0,     0,     0,     0,     0,    29,     0,    33,     0,    11,
       0,     0,     0,    21,    19,    37,    34,     0,    12,     0,
      16,     0,     9,     0,    18,     0,     0,     0,     0,     0,
      61,     0,    57,    27,    85,     0,     0,     0,    86,     0,
      25,    40,     0,     0,    38,     0,    41,    81,     0,    63,
      66,    69,    72,    75,    80,    10,    14,    17,    35,     0,
       0,     0,     0,    82,     0,     0,     0,     0,    81,    78,
      79,     0,     0,    36,    22,     0,    39,    43,    64,    87,
      88,     0,    58,    67,    70,    73,    76,    59,     0,    44,
       0,    90,     0,    84,     0,     0,    54,    24,     0,     0,
      36,     0,    60,     0,     0,     0,     0,    56,     0,     0,
      92,     0,    89,    62,     0,    55,    26,    15,     0,    65,
      68,    71,    74,    77,     0,    45,    51,    83,     0,     0,
      52,    13,    48,     0,    91,    53,    49,    46,     0,     0,
      50,     0,    47
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -103,  -103,  -103,  -103,   206,  -103,   175,  -103,  -103,    96,
     -30,  -103,  -103,    90,    -2,  -103,   124,   -62,  -103,  -103,
    -103,  -103,  -103,  -103,   -78,   -53,   -44,  -103,  -102,  -103,
      94,  -103,    97,  -103,    93,  -103,   -49,  -103,  -103,  -103,
    -103
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     7,     8,     9,    10,    43,    30,    22,
      40,    91,    92,    61,    95,    15,    63,    64,    65,   128,
     153,   159,   158,   144,    66,    67,    68,   121,    69,   123,
      70,   124,    71,   125,    72,   126,    73,    74,   111,   131,
     132
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      12,    96,    79,   109,    88,    12,    88,    85,    89,   130,
      90,    18,    87,    76,    23,    28,    46,    24,   101,   139,
      19,    20,    50,    51,    29,    52,   -15,   102,    50,    51,
      44,     3,    31,    54,    32,    97,   108,    62,   110,    54,
     112,    57,    58,    59,    41,    16,   154,    57,    58,    59,
     145,    33,    14,    42,    17,   -13,    96,    34,    88,   -20,
      83,   -20,     4,     5,     6,   115,   119,   146,    88,    84,
      88,    88,    88,    88,   116,    17,   149,   143,   104,    98,
     105,    35,   152,    21,    27,   150,    99,   100,     4,     5,
       6,   151,    11,    32,    36,    88,   160,    11,    37,   162,
      39,    46,    38,    47,    45,    48,    49,    50,    51,   157,
      52,    75,   -42,    53,     4,     5,     6,    23,    54,    80,
      55,    56,    25,    26,    99,   100,    57,    58,    59,    46,
      77,    47,    78,    48,    49,    50,    51,    81,    52,    82,
     -42,    94,     4,     5,     6,   137,    54,    86,    55,    56,
       4,     5,     6,   -23,    57,    58,    59,    46,    93,    47,
     103,    48,    49,    50,    51,   107,    52,   106,   -42,   136,
       4,     5,     6,   113,    54,   114,    55,    56,   117,   120,
     122,   133,    57,    58,    59,    46,   127,    47,   129,    48,
      49,    50,    51,   135,    52,   134,   -42,    17,     4,     5,
       6,   147,    54,   155,    55,    56,   148,   105,   156,   161,
      57,    58,    59,    13,    60,   138,   118,   140,   142,     0,
       0,   141
};

static const yytype_int16 yycheck[] =
{
       2,    63,    46,    81,    57,     7,    59,    51,    57,   111,
      59,     1,    56,    43,    16,     1,     1,    18,     1,   121,
      10,    11,     7,     8,    10,    10,    12,    10,     7,     8,
      32,     0,     9,    18,    11,    65,    80,    39,    82,    18,
      84,    26,    27,    28,     1,     8,   148,    26,    27,    28,
     128,     1,     7,    10,    17,    12,   118,     7,   111,     9,
       8,    11,    14,    15,    16,     1,     8,   129,   121,    17,
     123,   124,   125,   126,    10,    17,     1,   126,    24,    22,
      26,    19,   144,     9,     7,    10,    29,    30,    14,    15,
      16,     9,     2,    11,     7,   148,   158,     7,    17,   161,
      12,     1,    10,     3,    18,     5,     6,     7,     8,   153,
      10,    10,    12,    13,    14,    15,    16,   119,    18,     8,
      20,    21,    10,    11,    29,    30,    26,    27,    28,     1,
       7,     3,    19,     5,     6,     7,     8,     8,    10,     8,
      12,    13,    14,    15,    16,     9,    18,     8,    20,    21,
      14,    15,    16,    13,    26,    27,    28,     1,     7,     3,
      23,     5,     6,     7,     8,    10,    10,    25,    12,    13,
      14,    15,    16,     9,    18,     7,    20,    21,    13,     7,
      10,    19,    26,    27,    28,     1,     9,     3,     9,     5,
       6,     7,     8,    10,    10,     9,    12,    17,    14,    15,
      16,     9,    18,    10,    20,    21,    11,    26,     4,     9,
      26,    27,    28,     7,    39,   119,    92,   123,   125,    -1,
      -1,   124
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    39,    40,     0,    14,    15,    16,    41,    42,    43,
      44,    51,    52,    42,     7,    53,     8,    17,     1,    10,
      11,     9,    47,    52,    18,    10,    11,     7,     1,    10,
      46,     9,    11,     1,     7,    19,     7,    17,    10,    12,
      48,     1,    10,    45,    52,    18,     1,     3,     5,     6,
       7,     8,    10,    13,    18,    20,    21,    26,    27,    28,
      44,    51,    52,    54,    55,    56,    62,    63,    64,    66,
      68,    70,    72,    74,    75,    10,    48,     7,    19,    64,
       8,     8,     8,     8,    17,    64,     8,    64,    63,    74,
      74,    49,    50,     7,    13,    52,    55,    48,    22,    29,
      30,     1,    10,    23,    24,    26,    25,    10,    64,    62,
      64,    76,    64,     9,     7,     1,    10,    13,    54,     8,
       7,    65,    10,    67,    69,    71,    73,     9,    57,     9,
      66,    77,    78,    19,     9,    10,    13,     9,    47,    66,
      68,    70,    72,    74,    61,    62,    55,     9,    11,     1,
      10,     9,    55,    58,    66,    10,     4,    64,    60,    59,
      55,     9,    55
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    40,    39,    41,    41,    42,    42,    42,    43,
      43,    43,    43,    45,    44,    46,    44,    47,    47,    47,
      47,    47,    48,    49,    48,    50,    48,    48,    51,    51,
      52,    52,    52,    53,    53,    53,    53,    53,    54,    54,
      55,    55,    56,    55,    57,    58,    59,    55,    55,    60,
      55,    55,    55,    55,    55,    55,    61,    62,    62,    62,
      62,    63,    63,    64,    65,    64,    66,    67,    66,    68,
      69,    68,    70,    71,    70,    72,    73,    72,    74,    74,
      74,    75,    76,    75,    75,    75,    75,    75,    75,    77,
      77,    78,    78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     1,     1,     6,
       7,     5,     6,     0,     7,     0,     6,     4,     3,     2,
       1,     2,     3,     0,     4,     0,     5,     2,     3,     4,
       1,     1,     1,     3,     4,     6,     1,     4,     1,     2,
       1,     1,     0,     2,     0,     0,     0,    10,     6,     0,
       9,     5,     5,     6,     3,     4,     0,     1,     2,     3,
       3,     1,     4,     1,     0,     4,     1,     0,     4,     1,
       0,     4,     1,     0,     4,     1,     0,     4,     2,     2,
       1,     1,     0,     5,     3,     1,     1,     2,     2,     1,
       0,     3,     1
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
#line 77 "1805068_parser.y"
        { initializeASMFile(codeFile);}
#line 1324 "1805068_parser.tab.c"
    break;

  case 3: /* start: $@1 program  */
#line 78 "1805068_parser.y"
        {
		//write your code in this block in all the similar blocks below
		(yyval.name) = (yyvsp[0].name);
		logData(logFile, yylineno, "start : program", "");
		endASMFile(codeFile);
	}
#line 1335 "1805068_parser.tab.c"
    break;

  case 4: /* program: program unit  */
#line 86 "1805068_parser.y"
                                                {
										program += "\n";
										program += (yyvsp[0].name);
										(yyval.name) = new char [program.size() + 1];
										std::strcpy((yyval.name), program.c_str());
										logData(logFile, yylineno, "program : program unit", (yyval.name));
									}
#line 1347 "1805068_parser.tab.c"
    break;

  case 5: /* program: unit  */
#line 93 "1805068_parser.y"
                                                                {
										program += (yyvsp[0].name);
										(yyval.name) = new char [program.size() + 1];
										std::strcpy((yyval.name), program.c_str());
										logData(logFile, yylineno, "program : unit", (yyval.name));
									}
#line 1358 "1805068_parser.tab.c"
    break;

  case 6: /* unit: var_declaration  */
#line 101 "1805068_parser.y"
                                                {
										(yyval.name) = (yyvsp[0].name);
										logData(logFile, yylineno, "unit : var_declaration", (yyval.name));

									}
#line 1368 "1805068_parser.tab.c"
    break;

  case 7: /* unit: func_declaration  */
#line 106 "1805068_parser.y"
                                                { 
		 								(yyval.name) = (yyvsp[0].name);
										logData(logFile, yylineno, "unit : func_declaration", (yyval.name));
									}
#line 1377 "1805068_parser.tab.c"
    break;

  case 8: /* unit: func_definition  */
#line 110 "1805068_parser.y"
                                                { 
		 								(yyval.name) = (yyvsp[0].name);
										logData(logFile, yylineno, "unit : func_definition", (yyval.name));
									}
#line 1386 "1805068_parser.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 117 "1805068_parser.y"
                                                                                                                {
															string type = (yyvsp[-5].name), name = (yyvsp[-4].sym)->name;
															SymbolInfo *current = table->lookUp(name);

															if (current == NULL)
															{
																// not declared
																vector<Parameter> declaredParamList = getParamList((yyvsp[-2].name));
																SymbolInfo symbolInfo;
																symbolInfo.setName(name);
																symbolInfo.setType(type);
																symbolInfo.setDefined(false);
																symbolInfo.setFunc(true);
																// now add parameters to the function by opening a new scope
																table->enterScope();
																// if possible to enter symbol in ST, then add the parameter, otherwise show error
																// but if parameter name = " ", then can be added no worries
																for (int i = 0; i < declaredParamList.size(); i++)
																{
																	if (declaredParamList[i].name != " ")
																	{
																		if (!table->insert(declaredParamList[i].name, declaredParamList[i].type))
																		{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Redeclaration of parameter");
																		}
																	}
																}
																table->exitScope();
																symbolInfo.setParams(declaredParamList);
																table->insert(symbolInfo);
															}
															else
															{
																// function already declared, redeclaration
																errorCount++;
																logError(logFile, errorFile, yylineno, "Redeclaration of function");
															}

															str = (yyvsp[-5].name); str += " "; str += ((yyvsp[-4].sym)->name); str += "("; str += (yyvsp[-2].name); str += ");";
															(yyval.name) = new char [str.size() + 1];
															std::strcpy((yyval.name), str.c_str());
															logData(logFile, yylineno, "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", (yyval.name));
														}
#line 1435 "1805068_parser.tab.c"
    break;

  case 10: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN error SEMICOLON  */
#line 162 "1805068_parser.y"
                                                                                                                {
															string type = (yyvsp[-6].name), name = (yyvsp[-5].sym)->name;
															SymbolInfo *current = table->lookUp(name);

															if (current == NULL)
															{
																// not declared
																vector<Parameter> declaredParamList = getParamList((yyvsp[-3].name));
																SymbolInfo symbolInfo;
																symbolInfo.setName(name);
																symbolInfo.setType(type);
																symbolInfo.setDefined(false);
																symbolInfo.setFunc(true);
																// now add parameters to the function by opening a new scope
																table->enterScope();
																// if possible to enter symbol in ST, then add the parameter, otherwise show error
																// but if parameter name = " ", then can be added no worries
																for (int i = 0; i < declaredParamList.size(); i++)
																{
																	if (declaredParamList[i].name != " ")
																	{
																		if (!table->insert(declaredParamList[i].name, declaredParamList[i].type))
																		{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Redeclaration of parameter");
																		}
																	}
																}
																table->exitScope();
																symbolInfo.setParams(declaredParamList);
																table->insert(symbolInfo);
															}
															else
															{
																// function already declared, redeclaration
																errorCount++;
																logError(logFile, errorFile, yylineno, "Redeclaration of function");
															}

															str = (yyvsp[-6].name); str += " "; str += ((yyvsp[-5].sym)->name); str += "("; str += (yyvsp[-3].name); str += ");";
															(yyval.name) = new char [str.size() + 1];
															std::strcpy((yyval.name), str.c_str());
															logData(logFile, yylineno, "func_declaration : type_specifier ID LPAREN parameter_list RPAREN", (yyval.name));
														}
#line 1484 "1805068_parser.tab.c"
    break;

  case 11: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 207 "1805068_parser.y"
                                                                        {
															string type = (yyvsp[-4].name), name = (yyvsp[-3].sym)->name;
															SymbolInfo *current = table->lookUp(name);
															
															if (current == NULL) {

																// not declared

																vector<Parameter> parameters;
																SymbolInfo symbolInfo;
																symbolInfo.setName(name);
																symbolInfo.setParams(parameters);
																symbolInfo.setType(type);
																symbolInfo.setDefined(false);
																symbolInfo.setFunc(true);

																// enter and exit scope
																table->enterScope();
																table->exitScope();

																table->insert(symbolInfo);

															}
															else 
															{
																// enter and exit scope
																table->enterScope();
																table->exitScope();
																
																// previously declared as function or otherwise
																errorCount++;
																logError(logFile, errorFile, yylineno, "Previous declaration");
															}

															str = (yyvsp[-4].name); str += " "; str += ((yyvsp[-3].sym)->name); str += "();";
															(yyval.name) = new char [str.size() + 1];
															std::strcpy((yyval.name), str.c_str());
															logData(logFile, yylineno, "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON", (yyval.name));
														}
#line 1528 "1805068_parser.tab.c"
    break;

  case 12: /* func_declaration: type_specifier ID LPAREN RPAREN error SEMICOLON  */
#line 246 "1805068_parser.y"
                                                                  {
															string type = (yyvsp[-5].name), name = (yyvsp[-4].sym)->name;
															SymbolInfo *current = table->lookUp(name);
															
															if (current == NULL) {

																// not declared

																vector<Parameter> parameters;
																SymbolInfo symbolInfo;
																symbolInfo.setName(name);
																symbolInfo.setParams(parameters);
																symbolInfo.setType(type);
																symbolInfo.setDefined(false);
																symbolInfo.setFunc(true);

																// enter and exit scope
																table->enterScope();
																table->exitScope();

																table->insert(symbolInfo);

															}
															else 
															{
																// enter and exit scope
																table->enterScope();
																table->exitScope();
																
																// previously declared as function or otherwise
																errorCount++;
																logError(logFile, errorFile, yylineno, "Previous declaration");
															}

															str = (yyvsp[-5].name); str += " "; str += ((yyvsp[-4].sym)->name); str += "();";
															(yyval.name) = new char [str.size() + 1];
															std::strcpy((yyval.name), str.c_str());
															logData(logFile, yylineno, "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON", (yyval.name));
														}
#line 1572 "1805068_parser.tab.c"
    break;

  case 13: /* $@2: %empty  */
#line 288 "1805068_parser.y"
                                                                                                                {
															currentFunction = (yyvsp[-3].sym);
															string type = (yyvsp[-4].name);
															string name = (yyvsp[-3].sym)->name;
															returnType = "";
															string ASMText = name + " PROC";
															printToASM(ASMText, codeFile);
															printToASM("PUSH BP", codeFile);
															printToASM("MOV BP, SP", codeFile);
															vector<Parameter> paramList = getParamList((yyvsp[-1].name));
													
															SymbolInfo *current = table->lookUp(name);
															if (current == NULL)
															{
																// does not exist
																SymbolInfo functionInfo;
																functionInfo.setName(name);
																functionInfo.setType(type);
																functionInfo.setDefined(true);
																functionInfo.setFunc(true);
																functionInfo.setParams(paramList);
																table->insert(functionInfo);

																table->enterScope();

																for (int i = 0; i < paramList.size(); i++)
																{
																	funcParameterCount++;
																	if (paramList[i].name == " ")
																	{
																		errorCount++;
																		string errorStr = to_string(i+1) + "th parameter's name not given in function definition of " + name;
																		logError(logFile, errorFile, yylineno, errorStr);
																	}
																	else
																	{
																		SymbolInfo parameterInfo;
																		parameterInfo.setName(paramList[i].name);
																		parameterInfo.setType(paramList[i].type);
																		parameterInfo.setOffset(2*(funcParameterCount+1));
																		if (!(table->insert(parameterInfo)))
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Multiple declaration of " + paramList[i].name + " in parameter");
																		}
																	}
																	
																}
															}
															else
															{
																bool isConsistent = true;
																// declared, check for function or not
																if (!current->isFunc() || current->isDefined())
																{
																	errorCount++;
																	logError(logFile, errorFile, yylineno, "Multiple declaration of " + name);
																	isConsistent = false;
																}

																// function declared, not defined
																// time to check whether declaration consistent with definition 
																// check return types

																string declaredRetType = current->getType();
																if (type != declaredRetType && isConsistent)
																{
																	isConsistent = false;
																	errorCount++;
																	logError(logFile, errorFile, yylineno, "Return type mismatch with function declaration in function " + name);
																}

																// if declaration parameter number and definition number do not match, show error

																int declaredParameterNumber = current->getParamList().size();
																int definedParameterNumber = paramList.size();

																if (declaredParameterNumber != definedParameterNumber && isConsistent)
																{
																	isConsistent = false;
																	errorCount++;
																	logError(logFile, errorFile, yylineno, "Total number of arguments mismatch with declaration in function " + name);
																}
																else
																{
																	// parameter numbers match at this point
																	// check for parameter sequencing: if parameter numbers match and they are not 0
																	vector<Parameter> declaredParamList = current->getParamList();
																	if (declaredParameterNumber != 0)
																	{
																		for (int i = 0; i < declaredParameterNumber; i++)
																		{
																			string declaredType = declaredParamList[i].type;
																			string definedType = paramList[i].type;
																			if (declaredType != definedType)
																			{
																				isConsistent = false;
																				errorCount++;
																				logError(logFile, errorFile, yylineno, "Parameter sequence incorrect");
																			}
																		}
																	}
																}

																// table->printAllScopeTables(logFile);
																table->remove(name);
																SymbolInfo newSymbolInfo;
																newSymbolInfo.setName(name);
																newSymbolInfo.setType(type);
																newSymbolInfo.setParams(paramList);
																newSymbolInfo.setDefined(true);
																newSymbolInfo.setFunc(true);

																table->insert(newSymbolInfo);

																// now open a new scope and insert the parameters individually
																table->enterScope();

																for (int i = 0; i < paramList.size(); i++)
																{
																	if(!(table->insert(paramList[i].name, paramList[i].type)))
																	{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Redeclaration of parameter");
																	}
																}																		
															}
														}
#line 1705 "1805068_parser.tab.c"
    break;

  case 14: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@2 compound_statement  */
#line 416 "1805068_parser.y"
                                                                                                                                                        {
																						// check for return type
																						string compoundStatement = (yyvsp[0].name);
																						if ((yyvsp[-6].name) == "void")
																						{
																							if (returnType != "")
																							{
																								errorCount++;
																								logError(logFile, errorFile, returnLineNo, "Void function returns something");
																							}
																						}

																						else
																						{
																							if (returnType != (yyvsp[-6].name))
																							{
																								if (returnType == "")
																								{
																									errorCount++;
																									
																									string errorStr = "Function of type "; errorStr += (yyvsp[-6].name); errorStr += " does not return a value";
																									logError(logFile, errorFile, yylineno, errorStr);
																								}
																								else
																								{
			
																									if (!((yyvsp[-6].name) == "float" && returnType == "int"))
																									{
																										errorCount++;
																										logError(logFile, errorFile, returnLineNo, "Return type in body mismatched with definition");
																									}
																								}
																							}
																						}
																						if (funcVariableCount > 0)
																						{
																							// add stack pointer by 2*funcVariableCount (DW)
																							string temp = "ADD SP, ";
																							temp += to_string(2*funcVariableCount);
																							printToASM(temp, codeFile);
																						}
																						writeFunctionExitLabel((yyvsp[-5].sym)->name, codeFile);
																						printToASM("POP BP", codeFile);
																						char ASMCode[10];
																						sprintf(ASMCode, "RET %d", 2*funcParameterCount);
																						printToASM(ASMCode, codeFile);
																						string ASMText = (yyvsp[-5].sym)->name + " ENDP";
																						printToASM(ASMText, codeFile);
																						str = (yyvsp[-6].name); str += " "; str += (yyvsp[-5].sym)->name; str += "(";
																						str += (yyvsp[-3].name); str += ")"; str += (yyvsp[0].name);
																						(yyval.name) = new char [str.size() + 1];
																						std::strcpy((yyval.name), str.c_str());
																						logData(logFile, yylineno, "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement", (yyval.name));
																						funcVariableCount = 0;
																						funcParameterCount = 0;
																					}
#line 1766 "1805068_parser.tab.c"
    break;

  case 15: /* $@3: %empty  */
#line 473 "1805068_parser.y"
                                                                                                                                                                        {
																						currentFunction = (yyvsp[-2].sym);
																						string type = (yyvsp[-3].name);
																						string name = (yyvsp[-2].sym)->name;	
																						returnType = "";
																						string ASMText = name + " PROC";
																						printToASM(ASMText, codeFile);
																						printToASM("PUSH BP", codeFile);
																						printToASM("MOV BP, SP", codeFile);
																						SymbolInfo *current = table->lookUp(name);

																						if (name == "main")
																						{
																							printToASM("MOV AX, @DATA", codeFile);
																							printToASM("MOV DS, AX", codeFile);
																						}

																						if (current == NULL)
																						{
																							// does not exist at all
																							SymbolInfo symbolInfo;
																							symbolInfo.setFunc(true);
																							symbolInfo.setDefined(true);
																							symbolInfo.setName(name);
																							symbolInfo.setType(type);
																							
																							table->insert(symbolInfo);
																						}
																						else
																						{
																							// has been declared at least	
																							// check whether it is a function
																							if (current->isFunc())
																							{
																								// check whether it has been previously defined
																								if (current->isDefined())
																								{
																									errorCount++;
																									string errorStr = current->name + " has previously been defined";
																									logError(logFile, errorFile, yylineno, errorStr);
																								}
																								else
																								{
																									// function has been declared but not defined
																									// this is good
																									// now to check whether function definition is consistent with declaration

																									bool isConsistent = true;

																									// check whether parameter number is not zero

																									int declaredParamNumber = current->getParamList().size();
																									if (declaredParamNumber != 0)
																									{
																										isConsistent = false;
																										errorCount++;
																										logError(logFile, errorFile, yylineno, "Inconsistent number of parameters with declaration");
																									}

																									// check whether function return types match

																									string declaredRetType = current->getType();
																									if (declaredRetType != type)
																									{
																										isConsistent = false;
																										errorCount++;
																										logError(logFile, errorFile, yylineno, "Inconsistent return types");

																									}

																									// since no parameters, sequence checking is not needed

																									if (isConsistent)
																									{
																										// remove the original declaration and now add the definition
																										table->remove(name);

																										vector<Parameter> params;

																										SymbolInfo symbolInfo;
																										symbolInfo.setFunc(true);
																										symbolInfo.setDefined(true);
																										symbolInfo.setName(name);
																										symbolInfo.setType(type);
																										symbolInfo.setParams(params);

																										table->insert(symbolInfo);
																									}
																								}
																							}
																							else
																							{
																								// not a function, so log the error
																								string errorStr = current->name;
																								errorStr += " is not a function";
																								errorCount++;
																								logError(logFile, errorFile, yylineno, errorStr);
																							}
																						
																						}
																						table->enterScope();										
																					}
#line 1873 "1805068_parser.tab.c"
    break;

  case 16: /* func_definition: type_specifier ID LPAREN RPAREN $@3 compound_statement  */
#line 575 "1805068_parser.y"
                                                                                                                                                        {
																						if ((yyvsp[-5].name) == "void")
																						{
																							if (returnType != "")
																							{
																								errorCount++;
																								logError(logFile, errorFile, returnLineNo, "Void function returns something");
																							}
																						}

																						else
																						{
																							if (returnType != (yyvsp[-5].name))
																							{
																								if (returnType == "")
																								{
																									errorCount++;
																									string errorStr = "Function of type "; errorStr += (yyvsp[-5].name); errorStr += " does not return a value";
																									logError(logFile, errorFile, yylineno, errorStr);
																								}
																								else
																								{
																									if (!((yyvsp[-5].name) == "float" && returnType == "int"))
																									{
																										errorCount++;
																										logError(logFile, errorFile, returnLineNo, "Return type in body mismatched with definition");
																									}
																								}
																							}		
																						}

																						str = (yyvsp[-5].name); str += " "; str += (yyvsp[-4].sym)->name; str+="()";
																						str += (yyvsp[0].name);
																						if (funcVariableCount > 0)
																						{
																							// add stack pointer by 2*funcVariableCount (DW)
																							string temp = "ADD SP, ";
																							temp += to_string(2*funcVariableCount);
																							printToASM(temp, codeFile);
																						}
																						writeFunctionExitLabel((yyvsp[-4].sym)->name, codeFile);
																						printToASM("POP BP", codeFile);
																						if ((yyvsp[-4].sym)->name == "main")
																						{
																							printToASM("MOV AH, 4CH", codeFile);
																							printToASM("INT 21H", codeFile);
																						}
																						printToASM("RET 0", codeFile);
																						string ASMText = (yyvsp[-4].sym)->name + " ENDP";
																						printToASM(ASMText, codeFile);
																						(yyval.name) = new char [str.size() + 1];
																						std::strcpy((yyval.name), str.c_str());
																						logData(logFile, yylineno, "func_definition : type_specifier ID LPAREN RPAREN compound_statement", (yyval.name));
																						funcVariableCount = 0;
																						funcParameterCount = 0;
																					}
#line 1934 "1805068_parser.tab.c"
    break;

  case 17: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 634 "1805068_parser.y"
                                                                {
																str = (yyvsp[-3].name); str += ","; str += (yyvsp[-1].name); str += " "; str += (yyvsp[0].sym)->name;
																(yyval.name) = new char [str.size() + 1];
																std::strcpy((yyval.name), str.c_str());
																logData(logFile, yylineno, "parameter_list : parameter_list COMMA type_specifier ID", (yyval.name));
															}
#line 1945 "1805068_parser.tab.c"
    break;

  case 18: /* parameter_list: parameter_list COMMA type_specifier  */
#line 640 "1805068_parser.y"
                                                                                {
																str = (yyvsp[-2].name); str += ","; str += (yyvsp[0].name);
																(yyval.name) = new char [str.size() + 1];
																std::strcpy((yyval.name), str.c_str());
																logData(logFile, yylineno, "parameter_list : parameter_list COMMA type_specifier", (yyval.name));
															}
#line 1956 "1805068_parser.tab.c"
    break;

  case 19: /* parameter_list: type_specifier ID  */
#line 646 "1805068_parser.y"
                                                                                                        {
																str = (yyvsp[-1].name); str += " "; str += (yyvsp[0].sym)->name;
																(yyval.name) = new char [str.size() + 1];
																std::strcpy((yyval.name), str.c_str());
																logData(logFile, yylineno, "parameter_list : type_specifier ID", (yyval.name));
															}
#line 1967 "1805068_parser.tab.c"
    break;

  case 20: /* parameter_list: type_specifier  */
#line 652 "1805068_parser.y"
                                                                                                        {
																str = (yyvsp[0].name);
																(yyval.name) = new char[str.size() + 1];
																std::strcpy((yyval.name), str.c_str());
																logData(logFile, yylineno, "parameter_list : type_specifier", (yyval.name));
															}
#line 1978 "1805068_parser.tab.c"
    break;

  case 21: /* parameter_list: type_specifier error  */
#line 658 "1805068_parser.y"
                                                                                                {
																yyclearin;
																yyerrok;
																str = (yyvsp[-1].name);
																(yyval.name) = new char[str.size() + 1];
																std::strcpy((yyval.name), str.c_str());
																logData(logFile, yylineno, "parameter_list : type_specifier", (yyval.name));
															}
#line 1991 "1805068_parser.tab.c"
    break;

  case 22: /* compound_statement: LCURL statements RCURL  */
#line 669 "1805068_parser.y"
                                                                                {
																str = "{\n"; str += (yyvsp[-1].name); str += "\n}";
																(yyval.name) = new char [str.size() + 1];
																std::strcpy((yyval.name), str.c_str());
																logData(logFile, yylineno, "compound_statement : LCURL statements RCURL", (yyval.name));
																table->printAllScopeTables(logFile);
																table->exitScope();
															}
#line 2004 "1805068_parser.tab.c"
    break;

  case 23: /* $@4: %empty  */
#line 677 "1805068_parser.y"
                                                                                                {
																errorCount++;
																logError(logFile, errorFile, yylineno, "Invalid scoping of function");
			}
#line 2013 "1805068_parser.tab.c"
    break;

  case 24: /* compound_statement: LCURL func_definition $@4 RCURL  */
#line 680 "1805068_parser.y"
                                                                                                                {
																str = "{\n"; str += "\n}";
																(yyval.name) = new char [str.size() + 1];
																std::strcpy((yyval.name), str.c_str());
																logData(logFile, yylineno, "compound_statement : LCURL RCURL", (yyval.name));
																table->printAllScopeTables(logFile);
																table->exitScope();
															}
#line 2026 "1805068_parser.tab.c"
    break;

  case 25: /* $@5: %empty  */
#line 688 "1805068_parser.y"
                                                                                                {
																errorCount++;
																logError(logFile, errorFile, yylineno, "Invalid scoping of function");
			}
#line 2035 "1805068_parser.tab.c"
    break;

  case 26: /* compound_statement: LCURL func_definition $@5 statements RCURL  */
#line 691 "1805068_parser.y"
                                                                                                        {
																str = "{\n"; str += (yyvsp[-1].name); str += "\n}";
																(yyval.name) = new char [str.size() + 1];
																std::strcpy((yyval.name), str.c_str());
																logData(logFile, yylineno, "compound_statement : LCURL statements RCURL", (yyval.name));
																table->printAllScopeTables(logFile);
																table->exitScope();
															}
#line 2048 "1805068_parser.tab.c"
    break;

  case 27: /* compound_statement: LCURL RCURL  */
#line 699 "1805068_parser.y"
                                                                                                        {
				 												(yyval.name) = "{}";
																logData(logFile, yylineno, "compound_statement : LCURL RCURL", (yyval.name));
																table->printAllScopeTables(logFile);
																table->exitScope();
			 												}
#line 2059 "1805068_parser.tab.c"
    break;

  case 28: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 707 "1805068_parser.y"
                                                                                {	 	
																		string varType = (yyvsp[-2].name);
																		string varName = (yyvsp[-1].name);
																		// check for void variable type

																		if (varType == "void")
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Variable type cannot be void");
																		}
																		else
																		{
																			vector<string> strings = split(varName, ',');
																			for (string s: strings) {
																				SymbolInfo symbolInfo;
																				
																				if (isArray(s)) {
																					int size = getArraySize(s);
																					string name = getArrayName(s);
																					symbolInfo.setAsArray(name, (varType + "*"), size);
																					funcVariableCount += size;
																					symbolInfo.setOffset(funcVariableCount*-2);
																					
																					char ASMCode[15];
																					sprintf(ASMCode, "SUB SP, %d", size*2);
																					printToASM(ASMCode, codeFile);
																					
																				}
																				else {
																					symbolInfo.setName(s);
																					symbolInfo.setType(varType);
																					
																					// if the variable is in global scope, add to global variables
																					if (regex_match(table->getScopeID(), regex("\\d+")))
																						addGlobalVariable((char*) s.c_str(), codeFile);
																					else {
																						// add as local variable
																						funcVariableCount++;
																						symbolInfo.setOffset(funcVariableCount*-2);
																						// printf("C %d", symbolInfo.getOffset());
																						printToASM("SUB SP, 2", codeFile);
																					}
																				}

																				if (!table->insert(symbolInfo))
																				{
																					// multiple declaration
																					errorCount++;
																					string errorStr = "Multiple declaration of " + symbolInfo.getName();
																					logError(logFile, errorFile, yylineno, errorStr);
																				}
																			}
																		}
																		string str2 = (yyvsp[-1].name);
																		str = (yyvsp[-2].name); str += " "; str = str + str2; str+= ";";
																		(yyval.name) = new char [str.size() + 1];
																		std::strcpy((yyval.name), str.c_str());
																		logData(logFile, yylineno, "var_declaration : type_specifier declaration_list SEMICOLON", (yyval.name));
																	}
#line 2123 "1805068_parser.tab.c"
    break;

  case 29: /* var_declaration: type_specifier declaration_list error SEMICOLON  */
#line 766 "1805068_parser.y"
                                                                                        {	 	
																		string varType = (yyvsp[-3].name);
																		string varName = (yyvsp[-2].name);
																		// check for void variable type

																		if (varType == "void")
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Variable type cannot be void");
																		}
																		else
																		{
																			vector<string> strings = split(varName, ',');
																			for (string s: strings) {
																				SymbolInfo symbolInfo;
																				if (isArray(s)) {
																					int size = getArraySize(s);
																					string name = getArrayName(s);
																					symbolInfo.setAsArray(name, (varType + "*"), size);
																				}
																				else {
																					symbolInfo.setName(s);
																					symbolInfo.setType(varType);
																				}

																				if (!table->insert(symbolInfo))
																				{
																					// multiple declaration
																					errorCount++;
																					string errorStr = "Multiple declaration of " + symbolInfo.getName();
																					logError(logFile, errorFile, yylineno, errorStr);
																				}
																			}
																		}
																		string str2 = (yyvsp[-2].name);
																		str = (yyvsp[-3].name); str += " "; str = str + str2; str+= ";";
																		(yyval.name) = new char [str.size() + 1];
																		std::strcpy((yyval.name), str.c_str());
																		logData(logFile, yylineno, "var_declaration : type_specifier declaration_list SEMICOLON", (yyval.name));
																	}
#line 2168 "1805068_parser.tab.c"
    break;

  case 30: /* type_specifier: INT  */
#line 808 "1805068_parser.y"
                                                { (yyval.name) = (char *)"int"; logData(logFile, yylineno, "type_specifier : INT", (yyval.name)); }
#line 2174 "1805068_parser.tab.c"
    break;

  case 31: /* type_specifier: FLOAT  */
#line 809 "1805068_parser.y"
                                                                { (yyval.name) = (char *)"float"; logData(logFile, yylineno, "type_specifier : FLOAT", (yyval.name)); }
#line 2180 "1805068_parser.tab.c"
    break;

  case 32: /* type_specifier: VOID  */
#line 810 "1805068_parser.y"
                                                                { (yyval.name) = (char *)"void"; logData(logFile, yylineno, "type_specifier : VOID", (yyval.name)); }
#line 2186 "1805068_parser.tab.c"
    break;

  case 33: /* declaration_list: declaration_list COMMA ID  */
#line 813 "1805068_parser.y"
                                                                                { 
																	str = (yyvsp[-2].name); str += ","; str += (yyvsp[0].sym)->name;
																	(yyval.name) = new char [str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "declaration_list : declaration_list COMMA ID", (yyval.name));
																}
#line 2197 "1805068_parser.tab.c"
    break;

  case 34: /* declaration_list: declaration_list error COMMA ID  */
#line 819 "1805068_parser.y"
                                                                                                { 
																	str = (yyvsp[-3].name); str += ","; str += (yyvsp[0].sym)->name;
																	(yyval.name) = new char [str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "declaration_list : declaration_list COMMA ID", (yyval.name));
																}
#line 2208 "1805068_parser.tab.c"
    break;

  case 35: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 825 "1805068_parser.y"
                                                                        {
			   														str = (yyvsp[-5].name); str += ","; str += (yyvsp[-3].sym)->name; str += "["; str += (yyvsp[-1].sym)->name; str += "]";
																	(yyval.name) = new char [str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD", (yyval.name));
		   														}
#line 2219 "1805068_parser.tab.c"
    break;

  case 36: /* declaration_list: ID  */
#line 831 "1805068_parser.y"
                                                                                                                        {
			   														(yyval.name) = new char[(yyvsp[0].sym)->name.size() + 1];
																	std::strcpy((yyval.name), (yyvsp[0].sym)->name.c_str());
																	logData(logFile, yylineno, "declaration_list : ID", (yyval.name));
																}
#line 2229 "1805068_parser.tab.c"
    break;

  case 37: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 836 "1805068_parser.y"
                                                                                                { 
			   														str = (yyvsp[-3].sym)->name; str += "["; str += (yyvsp[-1].sym)->name; str += "]";
																	(yyval.name) = new char[str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "declaration_list : ID LTHIRD CONST_INT RTHIRD", (yyval.name));
		   														}
#line 2240 "1805068_parser.tab.c"
    break;

  case 38: /* statements: statement  */
#line 844 "1805068_parser.y"
                                                                                                        {
																	str = (yyvsp[0].name); 
																	(yyval.name) = new char[str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "statements : statement", (yyval.name));
																}
#line 2251 "1805068_parser.tab.c"
    break;

  case 39: /* statements: statements statement  */
#line 850 "1805068_parser.y"
                                                                                                        {
		   															str = (yyvsp[-1].name);
																	str += "\n"; str += (yyvsp[0].name); 
																	(yyval.name) = new char[str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "statements : statements statement", (yyval.name));
	   															}
#line 2263 "1805068_parser.tab.c"
    break;

  case 40: /* statement: var_declaration  */
#line 859 "1805068_parser.y"
                                                                                                        { 
																	str = (yyvsp[0].name);
																	(yyval.name) = new char[str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "statement : var_declaration", (yyval.name));
 																}
#line 2274 "1805068_parser.tab.c"
    break;

  case 41: /* statement: expression_statement  */
#line 865 "1805068_parser.y"
                                                                                                        { 
		  															(yyval.name) = (yyvsp[0].name);
																	logData(logFile, yylineno, "statement : expression_statement", (yyval.name));
	   															}
#line 2283 "1805068_parser.tab.c"
    break;

  case 42: /* $@6: %empty  */
#line 869 "1805068_parser.y"
  { table->enterScope(); }
#line 2289 "1805068_parser.tab.c"
    break;

  case 43: /* statement: $@6 compound_statement  */
#line 869 "1805068_parser.y"
                                                                                {
																	str = (yyvsp[0].name);
																	(yyval.name) = new char[str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "statement : compound_statement", (yyval.name));
																}
#line 2300 "1805068_parser.tab.c"
    break;

  case 44: /* $@7: %empty  */
#line 876 "1805068_parser.y"
                                                                                                                                {
																	forLabel1 = newLabel();
																	printToASM(forLabel1 + ":", codeFile);
																}
#line 2309 "1805068_parser.tab.c"
    break;

  case 45: /* $@8: %empty  */
#line 880 "1805068_parser.y"
                                                                                                        {
																	forLabel2 = newLabel();
																	printToASM("JCXZ " + forLabel2, codeFile);
																	// place a marker
																	printToASM("expr_marker", codeFile);
	  															}
#line 2320 "1805068_parser.tab.c"
    break;

  case 46: /* $@9: %empty  */
#line 886 "1805068_parser.y"
                                                                                                                {
		  															// collect everything from expr_marker into a string
																	forExprStmt = collectExprStmt(codeFile);
	  															}
#line 2329 "1805068_parser.tab.c"
    break;

  case 47: /* statement: FOR LPAREN expression_statement $@7 expression_statement $@8 expression $@9 RPAREN statement  */
#line 891 "1805068_parser.y"
                                                                                                                                {
																	str = "for("; str += (yyvsp[-7].name); str += (yyvsp[-5].name); str += (yyvsp[-3].sym)->name; str += ")"; str += (yyvsp[0].name);
																	(yyval.name) = new char[str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement", (yyval.name));

																	printToASM(forExprStmt, codeFile);
																	printToASM("JMP " + forLabel1, codeFile);
																	printToASM(forLabel2 + ":", codeFile);
																}
#line 2344 "1805068_parser.tab.c"
    break;

  case 48: /* statement: IF LPAREN expression RPAREN dummy statement  */
#line 902 "1805068_parser.y"
                                                                                                                                { 
																	str = "if ("; str += (yyvsp[-3].sym)->name; str += ")"; str += (yyvsp[-1].name);
																	(yyval.name) = new char[str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "statement : IF LPAREN expression RPAREN statement", str);
																	string label = newLabel();
																	printToASM("JMP " + label, codeFile);
																	printToASM(ifLabel1 + ":", codeFile);
																	printToASM(label + ":", codeFile);
	   															}
#line 2359 "1805068_parser.tab.c"
    break;

  case 49: /* $@10: %empty  */
#line 913 "1805068_parser.y"
                                                                                                                                {
																	ifLabel2 = newLabel();
																	printToASM("JMP " + ifLabel2, codeFile);
																	printToASM(ifLabel1 + ":", codeFile);
																}
#line 2369 "1805068_parser.tab.c"
    break;

  case 50: /* statement: IF LPAREN expression RPAREN dummy statement ELSE $@10 statement  */
#line 918 "1805068_parser.y"
                        {
		  															str = "if ("; str += (yyvsp[-6].sym)->name; str += ")"; str += (yyvsp[-3].name); str += "\nelse\n"; str += (yyvsp[0].name);
																	(yyval.name) = new char[str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "statement : IF LPAREN expression RPAREN statement ELSE statement", str);

																	printToASM(ifLabel2 + ":", codeFile);
	  															}
#line 2382 "1805068_parser.tab.c"
    break;

  case 51: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 926 "1805068_parser.y"
                                                                                {
		  															str = "while ("; str += (yyvsp[-2].sym)->name; str += ")"; str += (yyvsp[0].name);
																	(yyval.name) = new char[str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "statement : WHILE LPAREN expression RPAREN statement", str);
	  															}
#line 2393 "1805068_parser.tab.c"
    break;

  case 52: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 932 "1805068_parser.y"
                                                                                        {
		  															str = "println("; str += (yyvsp[-2].sym)->name; str +=");";
																	(yyval.name) = new char[str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	SymbolInfo* current = table->lookUp((yyvsp[-2].sym)->name);
																	if (current == NULL)
																	{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Undeclared variable " + (yyvsp[-2].sym)->name);
																	}
																	else
																	{
																		char ASMCode[20];
																		sprintf(ASMCode, "MOV CX, %d[BP]", current->getOffset());
																		printToASM(ASMCode, codeFile);
																		printToASM("PUSH CX", codeFile);
																		if (current->getType() == "int")
																		{
																			printToASM("CALL println_int", codeFile);
																		}

																		else if (current->getType() == "float")
																		{
																			printToASM("CALL println_float", codeFile);
																		}
																	}
																	logData(logFile, yylineno, "statement : PRINTLN LPAREN ID RPAREN SEMICOLON", str);
	  															}
#line 2426 "1805068_parser.tab.c"
    break;

  case 53: /* statement: PRINTLN LPAREN ID RPAREN error SEMICOLON  */
#line 960 "1805068_parser.y"
                                                                                        {
		  															str = "printf("; str += (yyvsp[-3].sym)->name; str +=");";
																	(yyval.name) = new char[str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	SymbolInfo* current = table->lookUp((yyvsp[-3].sym)->name);
																	if (current == NULL)
																	{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Undeclared variable " + (yyvsp[-3].sym)->name);
																	}
																	logData(logFile, yylineno, "statement : PRINTLN LPAREN ID RPAREN SEMICOLON", str);
	  															}
#line 2443 "1805068_parser.tab.c"
    break;

  case 54: /* statement: RETURN expression SEMICOLON  */
#line 972 "1805068_parser.y"
                                                                                                {
		  															returnType = (yyvsp[-1].sym)->type;
																	returnLineNo = yylineno;
		  															str = (yyvsp[-1].sym)->name; str = "return " + str; str += ";";
																	(yyval.name) = new char [str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "statement : RETURN expression SEMICOLON", (yyval.name));
																	char ASMCode[20];
																	sprintf(ASMCode, "SUB SP, %d", -2*funcVariableCount);
																	printToASM(ASMCode, codeFile);
																	sprintf(ASMCode, "JMP %s_exit", (char*) currentFunction->getName().c_str());
																	printToASM(ASMCode, codeFile);
																	
	  															}
#line 2462 "1805068_parser.tab.c"
    break;

  case 55: /* statement: RETURN expression error SEMICOLON  */
#line 986 "1805068_parser.y"
                                                                                                {
		  															returnType = (yyvsp[-2].sym)->type;
		  															str = (yyvsp[-2].sym)->name; str = "return " + str; str += ";";
																	(yyval.name) = new char [str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "statement : RETURN expression SEMICOLON", (yyval.name));
	  															}
#line 2474 "1805068_parser.tab.c"
    break;

  case 56: /* dummy: %empty  */
#line 995 "1805068_parser.y"
                                                                                                                        {
																	ifLabel1 = newLabel();
																	printToASM("JCXZ " + ifLabel1, codeFile);
																}
#line 2483 "1805068_parser.tab.c"
    break;

  case 57: /* expression_statement: SEMICOLON  */
#line 1000 "1805068_parser.y"
                                                                                                {
																	(yyval.name) = ";";
																	logData(logFile, yylineno, "expression_statement : SEMICOLON", (yyval.name));
 																}
#line 2492 "1805068_parser.tab.c"
    break;

  case 58: /* expression_statement: expression SEMICOLON  */
#line 1004 "1805068_parser.y"
                                                                                                        {
																	str = (yyvsp[-1].sym)->name; str += ";";
																	(yyval.name) = new char[str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "expression_statement : expression SEMICOLON", (yyval.name));
																}
#line 2503 "1805068_parser.tab.c"
    break;

  case 59: /* expression_statement: error expression SEMICOLON  */
#line 1010 "1805068_parser.y"
                                                                                                {
																	str = (yyvsp[-1].sym)->name; str += ";";
																	(yyval.name) = new char[str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "expression_statement : expression SEMICOLON", (yyval.name));
																}
#line 2514 "1805068_parser.tab.c"
    break;

  case 60: /* expression_statement: expression error SEMICOLON  */
#line 1016 "1805068_parser.y"
                                                                                                {

																	str = (yyvsp[-2].sym)->name; str += ";";
																	(yyval.name) = new char[str.size() + 1];
																	std::strcpy((yyval.name), str.c_str());
																	logData(logFile, yylineno, "expression_statement : expression SEMICOLON", (yyval.name));
																}
#line 2526 "1805068_parser.tab.c"
    break;

  case 61: /* variable: ID  */
#line 1025 "1805068_parser.y"
                                                                                                                {
																	// check whether variable has been declared
																	SymbolInfo *current = table->lookUp((yyvsp[0].sym)->name);
																	// cout << current->name << ": " << current->getType() << endl;
																	if (current == NULL)
																	{
																		// undeclared
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Undeclared variable " + (yyvsp[0].sym)->name);
																		(yyval.sym) = new SymbolInfo((yyvsp[0].sym)->name, "ERROR");
																	}
																	else
																	{
																		(yyval.sym) = new SymbolInfo(current->name, current->getType());
																		(yyval.sym)->setInTable(true);
																	} 
																	logData(logFile, yylineno, "variable : ID", (yyval.sym)->name);
																}
#line 2549 "1805068_parser.tab.c"
    break;

  case 62: /* variable: ID LTHIRD expression RTHIRD  */
#line 1043 "1805068_parser.y"
                                                                                                {
		 															// check whether variable has been declared or not
																	SymbolInfo *current = table->lookUp((yyvsp[-3].sym)->name);
																	if (current == NULL)
																	{
																		errorCount++;
																		string errorStr = "Undeclared variable " + (yyvsp[-3].sym)->name;
																		logError(logFile, errorFile, yylineno, errorStr);
																		(yyval.sym) = new SymbolInfo((yyvsp[-3].sym)->name + "[" + (yyvsp[-1].sym)->name + "]", "ERROR");
																	}
																	else
																	{
																		// variable has been declared, check whether expression is in correct format
																		// since this is supposed to be an array, must check whether it is array or not
																		if (!current->isArray())
																		{
																			errorCount++;
																			string errorStr = (yyvsp[-3].sym)->name + " not an array";
																			logError(logFile, errorFile, yylineno, errorStr);
																			(yyval.sym) = new SymbolInfo((yyvsp[-3].sym)->name + "[" + (yyvsp[-1].sym)->name + "]", "ERROR");
																		}
																		else
																		{
																			// it is an array, now check whether expression is an integer or not
																			if ((yyvsp[-1].sym)->getType() != "int")
																			{
																				errorCount++;
																				logError(logFile, errorFile, yylineno, "Expression inside third brackets not an integer");
																			}
																			string name = (yyvsp[-3].sym)->name + "[" + (yyvsp[-1].sym)->name + "]";
																			(yyval.sym) = new SymbolInfo(name, (yyvsp[-1].sym)->getType());																		
																		}
																	}
																	logData(logFile, yylineno, "variable : ID LTHIRD expression RTHIRD", (yyval.sym)->name);
	  															}
#line 2589 "1805068_parser.tab.c"
    break;

  case 63: /* expression: logic_expression  */
#line 1080 "1805068_parser.y"
                                                                                                {
																	(yyval.sym) = (yyvsp[0].sym);
																	logData(logFile, yylineno, "expression : logic_expression", (yyval.sym)->name);
																}
#line 2598 "1805068_parser.tab.c"
    break;

  case 64: /* $@11: %empty  */
#line 1085 "1805068_parser.y"
           {
		   															SymbolInfo *current = table->lookUp(getArrayName((yyvsp[-1].sym)->name));
																	if (current->isArray())
																	{
																		printToASM("PUSH CX", codeFile);
																	}
	   }
#line 2610 "1805068_parser.tab.c"
    break;

  case 65: /* expression: variable ASSIGNOP $@11 logic_expression  */
#line 1092 "1805068_parser.y"
                                                                                                                {
		   															// check for type mismatch
																	// float = int is okay, int = float is not
																	// both sides same = ok

																	string leftType = (yyvsp[-3].sym)->getType();
																	string rightType = (yyvsp[0].sym)->getType();

																	if (leftType == "void" || rightType == "void")
																	{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Void function used in expression");
																	}

																	if (leftType != rightType)
																	{
																		if (leftType == "int" && (rightType == "float" || rightType == "CONST_FLOAT"))
																		{
																			// int is being assigned to float, type mismatch
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Type Mismatch");
																		}
																		// check for array mismatches
																		else if (leftType == "int*" || leftType == "float*")
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Type mismatch, " + (yyvsp[-3].sym)->name + " is an array");
																		}
																		else if (rightType == "int*" || rightType == "float*")
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Type mismatch, " + (yyvsp[0].sym)->name + " is an array");
																		}
																	}

																	char ASMCode[10];
																	SymbolInfo *originalSymbolInfo = table->lookUp(getArrayName((yyvsp[-3].sym)->getName()));
																	if (originalSymbolInfo->isArray())
																	{
																		printToASM("POP AX", codeFile);
																		printToASM("XCHG AX, CX", codeFile);
																		char ASMCode[10];
																		int index = getArraySize((yyvsp[-3].sym)->name);
																		printToASM("PUSH BP", codeFile);
																		printToASM("SAL CX, 1", codeFile);
																		sprintf(ASMCode, "ADD CX, %d", originalSymbolInfo->getOffset());
																		printToASM(ASMCode, codeFile);
																		printToASM("ADD BP, CX", codeFile);
																		printToASM("MOV PTR WORD [BP], AX", codeFile);
																		printToASM("MOV CX, AX", codeFile);
																		printToASM("POP BP", codeFile);

																	}
																	else
																	{
																		// assuming CX holds the required result:
																		sprintf(ASMCode, "MOV %d[BP], CX", originalSymbolInfo->getOffset());
																		printToASM(ASMCode, codeFile);
																	}

		   															str = (yyvsp[-3].sym)->name; str += "="; str += (yyvsp[0].sym)->name;
																	string retType = "expression";
																	(yyval.sym) = new SymbolInfo(str, retType);
																	logData(logFile, yylineno, "expression : variable ASSIGNOP logic_expression", (yyval.sym)->name);
	   															}
#line 2680 "1805068_parser.tab.c"
    break;

  case 66: /* logic_expression: rel_expression  */
#line 1159 "1805068_parser.y"
                                                                                                {
																	(yyval.sym) = (yyvsp[0].sym);
																	logData(logFile, yylineno, "logic_expression : rel_expression", (yyval.sym)->name);
																}
#line 2689 "1805068_parser.tab.c"
    break;

  case 67: /* $@12: %empty  */
#line 1164 "1805068_parser.y"
                                                                                                                                {
																	string logicOp = (yyvsp[0].sym)->name;
																	logicOpLabel1 = newLabel();
																	if (logicOp == "&&")
																	{
																		printToASM("JCXZ " + logicOpLabel1, codeFile);
																	}
																	else
																	{
																		printToASM("CMP CX, 0", codeFile);
																		printToASM("JNZ " + logicOpLabel1, codeFile);
																	}
																}
#line 2707 "1805068_parser.tab.c"
    break;

  case 68: /* logic_expression: rel_expression LOGICOP $@12 rel_expression  */
#line 1177 "1805068_parser.y"
                                                                                                                {
			 														str = (yyvsp[-3].sym)->name; str += (yyvsp[-2].sym)->name; str += (yyvsp[0].sym)->name;
																	(yyval.sym) = new SymbolInfo(str, "int");
																	logData(logFile, yylineno, "logic_expression : rel_expression LOGICOP rel_expression", (yyval.sym)->name);

																	// ASM Code
																	printToASM(logicOpLabel1 + ":", codeFile);
		 														}
#line 2720 "1805068_parser.tab.c"
    break;

  case 69: /* rel_expression: simple_expression  */
#line 1187 "1805068_parser.y"
                                                                                        {
																	(yyval.sym) = (yyvsp[0].sym);
																	logData(logFile, yylineno, "rel_expression : simple_expression", (yyval.sym)->name);
																}
#line 2729 "1805068_parser.tab.c"
    break;

  case 70: /* $@13: %empty  */
#line 1192 "1805068_parser.y"
                                                                                                                                {
																	printToASM("PUSH CX", codeFile);
																}
#line 2737 "1805068_parser.tab.c"
    break;

  case 71: /* rel_expression: simple_expression RELOP $@13 simple_expression  */
#line 1195 "1805068_parser.y"
                                                                                                                {
																	str = (yyvsp[-3].sym)->name; str += (yyvsp[-2].sym)->name; str += (yyvsp[0].sym)->name;
																	(yyval.sym) = new SymbolInfo(str, "int");
																	logData(logFile, yylineno, "rel_expression : simple_expression RELOP simple_expression", (yyval.sym)->name);

																	string label1 = newLabel();
																	string label2 = newLabel();
																	
																	// ASM Code
																	printToASM("POP AX", codeFile);
																	printToASM("CMP AX, CX", codeFile);

																	string relOp = (yyvsp[-2].sym)->name;

																	if (relOp == "<")
																		printToASM("JL " + label1, codeFile);
																	else if (relOp == ">")
																		printToASM("JG " + label1, codeFile);
																	else if (relOp == "==")
																		printToASM("JE " + label1, codeFile);
																	else if (relOp == ">=")
																		printToASM("JGE " + label1, codeFile);
																	else if (relOp == "<=")
																		printToASM("JLE " + label1, codeFile);
																	else if (relOp == "!=")
																		printToASM("JNE " + label1, codeFile);

																	printToASM("MOV CX, 0", codeFile);
																	printToASM("JMP " + label2, codeFile);
																	printToASM(label1 + ":", codeFile);
																	printToASM("MOV CX, 1", codeFile);
																	printToASM(label2 + ":", codeFile);
																	

																}
#line 2777 "1805068_parser.tab.c"
    break;

  case 72: /* simple_expression: term  */
#line 1232 "1805068_parser.y"
                                                                                                        {
																	(yyval.sym) = (yyvsp[0].sym);
																	logData(logFile, yylineno, "simple_expression : term", (yyval.sym)->name);
																}
#line 2786 "1805068_parser.tab.c"
    break;

  case 73: /* $@14: %empty  */
#line 1237 "1805068_parser.y"
                  {
			  if ((yyvsp[0].sym)->name == "+")
				// keep track that we are going to add
				addOrSub = 1;
			  else
			  	addOrSub = 0;
			// push current CX up
			printToASM("PUSH CX", codeFile);
		  }
#line 2800 "1805068_parser.tab.c"
    break;

  case 74: /* simple_expression: simple_expression ADDOP $@14 term  */
#line 1245 "1805068_parser.y"
                                                                        {
			  														// ASM code
																	printToASM("POP AX", codeFile);
																	if (addOrSub)
																		printToASM("ADD AX, CX", codeFile);
																	else
																		printToASM("SUB AX, CX", codeFile);
																	printToASM("MOV CX, AX", codeFile);
																	
			  														string retType;
																	// if any of them is a float, change final term to float
																	if ((yyvsp[-3].sym)->getType() == "float" || (yyvsp[0].sym)->getType() == "float")
																	{
																		retType = "float";
																	}
																	else
																	{
																		retType = "int";
																	}
			  														str = (yyvsp[-3].sym)->name; str += ((yyvsp[-2].sym)->name); str += (yyvsp[0].sym)->name;
																	(yyval.sym) = new SymbolInfo(str, retType);
																	logData(logFile, yylineno, "simple_expression : simple_expression ADDOP term", (yyval.sym)->name);
		  														}
#line 2828 "1805068_parser.tab.c"
    break;

  case 75: /* term: unary_expression  */
#line 1270 "1805068_parser.y"
                                                                                                        {
																	if ((yyvsp[0].sym)->isInTable())
																	{
																		// char ASMCode[10];
																		
																		// SymbolInfo *originalSymbolInfo = table->lookUp($1->getName());
																		// sprintf(ASMCode, "MOV CX, %d[BP]", originalSymbolInfo->getOffset());
																		// printToASM(ASMCode, codeFile);
																	}
																	(yyval.sym) = (yyvsp[0].sym);
																	logData(logFile, yylineno, "term : unary_expression", (yyval.sym)->name);
																}
#line 2845 "1805068_parser.tab.c"
    break;

  case 76: /* $@15: %empty  */
#line 1282 "1805068_parser.y"
                   {printToASM("PUSH CX", codeFile);}
#line 2851 "1805068_parser.tab.c"
    break;

  case 77: /* term: term MULOP $@15 unary_expression  */
#line 1282 "1805068_parser.y"
                                                                       {
		 															// check modulus integer type
																	string leftType = (yyvsp[-3].sym)->getType();
																	string rightType = (yyvsp[0].sym)->getType();
																	string symbol = (yyvsp[-2].sym)->getName();
																	string retType;
																	if (symbol == "%")
																	{
																		// check zero modulus
																		if ((yyvsp[0].sym)->name == "0")
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Modulus by Zero");
																		}
																		// check whether both sides of modulus integer or not
																		else if (leftType == "float" || leftType == "CONST_FLOAT" || rightType == "float" || rightType == "CONST_FLOAT" )
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Non-Integer operand on modulus operator");
																			retType = "ERROR";
																		}
																		else
																		{
																			retType = "int";
																		}
																	}
																	else
																	{
																		// if lval or rval float, ret type is float
																		if ((yyvsp[-3].sym)->getType() == "float" || (yyvsp[0].sym)->getType() == "float")
																		{
																			retType = "float";
																		}
																		else
																		{
																			retType = "int";
																		}
																	}

																	// check if function, and then function type
																	if (leftType == "void" || rightType == "void")
																	{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Void function used in expression");
																	}
		 															str = (yyvsp[-3].sym)->name; str += (yyvsp[-2].sym)->name; str += (yyvsp[0].sym)->name;
																	(yyval.sym) = new SymbolInfo(str, retType);
																	logData(logFile, yylineno, "term : term MULOP unary_expression", (yyval.sym)->name);
																	
																	string mulOp = (yyvsp[-2].sym)->name;
																	printToASM("POP AX", codeFile);
																	if (mulOp == "*")
																	{
																		printToASM("IMUL CX", codeFile);
																		printToASM("MOV CX, AX", codeFile);
																	}
																		
																	else
																	{
																		printToASM("CWD", codeFile);
																		printToASM("IDIV CX", codeFile);
																		if (mulOp == "%")
																			printToASM("MOV CX, DX", codeFile);
																		else
																			printToASM("MOV CX, AX", codeFile);
																	}
	 															}
#line 2923 "1805068_parser.tab.c"
    break;

  case 78: /* unary_expression: ADDOP unary_expression  */
#line 1351 "1805068_parser.y"
                                                                                        { 	
																	str = (yyvsp[-1].sym)->name + (yyvsp[0].sym)->name; 
																	(yyval.sym) = new SymbolInfo(str, (yyvsp[0].sym)->getType());
																	logData(logFile, yylineno, "unary_expression : ADDOP unary_expression", (yyval.sym)->name);
																}
#line 2933 "1805068_parser.tab.c"
    break;

  case 79: /* unary_expression: NOT unary_expression  */
#line 1356 "1805068_parser.y"
                                                                                                        {
			 														str = "!"; str += (yyvsp[0].sym)->name;
																	(yyval.sym) = new SymbolInfo(str, (yyvsp[0].sym)->getType());
																	logData(logFile, yylineno, "unary_expression : NOT unary_expression", (yyval.sym)->name);
		 														}
#line 2943 "1805068_parser.tab.c"
    break;

  case 80: /* unary_expression: factor  */
#line 1361 "1805068_parser.y"
                                                                                                                        {
																	(yyval.sym) = (yyvsp[0].sym);
																	logData(logFile, yylineno, "unary_expression : factor", (yyval.sym)->name);
																}
#line 2952 "1805068_parser.tab.c"
    break;

  case 81: /* factor: variable  */
#line 1367 "1805068_parser.y"
                                                                                                                {
																	(yyval.sym) = new SymbolInfo((yyvsp[0].sym)->name, (yyvsp[0].sym)->type);
																	(yyval.sym)->setInTable(true);
																	// cout << getArrayName($1->name) << endl;
																	logData(logFile, yylineno, "factor : variable", (yyval.sym)->name);

																	if (!inFactorArgList)
																	{
																		char ASMCode[10];	
																		SymbolInfo *current = table->lookUp(getArrayName((yyvsp[0].sym)->name));
																		if (!current->isArray())
																		{
																			sprintf(ASMCode, "MOV CX, %d[BP]", current->getOffset());
																			printToASM(ASMCode, codeFile);
																		}
																		else
																		{
																			// extract index;
																			char ASMCode[10];
																			
																			int index = getArraySize((yyvsp[0].sym)->name);
																			printToASM("PUSH BP", codeFile);
																			printToASM("SAL CX, 1", codeFile);
																			sprintf(ASMCode, "ADD CX, %d", current->getOffset());
																			printToASM(ASMCode, codeFile);
																			printToASM("ADD BP, CX", codeFile);
																			printToASM("MOV CX , PTR WORD [BP]", codeFile);
																			printToASM("POP BP", codeFile);
																		}
																	}
																}
#line 2988 "1805068_parser.tab.c"
    break;

  case 82: /* $@16: %empty  */
#line 1398 "1805068_parser.y"
                    { inFactorArgList = true; }
#line 2994 "1805068_parser.tab.c"
    break;

  case 83: /* factor: ID LPAREN $@16 argument_list RPAREN  */
#line 1399 "1805068_parser.y"
                                                                                                        {
																	// this is a function
																	// so the type of the symbolInfo should be the return type of the function.
																	SymbolInfo *symbolInfo = table->lookUp((yyvsp[-4].sym)->name);
																	string retType = "none";
																	// if this does not exist, show error
																	if (symbolInfo == NULL)
																	{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Undeclared function " + (yyvsp[-4].sym)->name);
																	}
																	else
																	{
																		// check whether ID is function or not
																		if (!symbolInfo->isFunc())
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Not a function");
																		}
																		else
																		{
																			
																			// check args
																			vector<string> argNames = split((yyvsp[-1].sym)->name, ',');
																			vector<string> argTypes = split((yyvsp[-1].sym)->type, ',');
																			vector<Parameter> paramList = symbolInfo->getParamList();
																			// check the number of args with declared no. of args
																			if (argNames.size() != paramList.size())
																			{
																				errorCount++;
																				logError(logFile, errorFile, yylineno, "Total number of arguments mismatch in function " + symbolInfo->name);
																			}
																			else
																			{
																				// number same, check for types
																				for (int i = 0; i < argNames.size(); i++)
																				{
																					// get the argument type
																					string declaredType = paramList[i].type;
																					if (declaredType != argTypes[i])
																					{
																						errorCount++;
																						string incorrectType = argTypes[i];
																						if (incorrectType == "int*" || incorrectType == "float*")
																							incorrectType = "array";
																						logError(logFile, errorFile, yylineno, "Type mismatch, " + argNames[i] + " is a " + incorrectType);
																					}																					
																				}

																				for (int i = argNames.size() - 1; i >= 0; i--)
																				{
																					// check whether it is a variable or a constant
																					SymbolInfo *current = table->lookUp(argNames[i]);	
																					if (current == NULL)
																					{
																						// is a const, so move const to CX

																					}
																					else
																					{
																						// is a variable, move from required offset to CX
																						char ASMCode[10];
																						sprintf(ASMCode, "MOV CX, %d[BP]", current->getOffset());
																						printToASM(ASMCode, codeFile);
																						printToASM("PUSH CX", codeFile);
																					}																			
																				}
																			}
																			// set return type equal to return type of function
																			retType = symbolInfo->getType();
																			string ASMCode = "CALL " + (yyvsp[-4].sym)->name;
																			printToASM(ASMCode, codeFile);
																		}
																	}
																	str = (yyvsp[-4].sym)->name; str += "("; str += (yyvsp[-1].sym)->name; str += ")";
																	(yyval.sym) = new SymbolInfo(str, retType);
																	logData(logFile, yylineno, "factor : ID LPAREN argument_list RPAREN", (yyval.sym)->name);
																	inFactorArgList = false;
		 														}
#line 3078 "1805068_parser.tab.c"
    break;

  case 84: /* factor: LPAREN expression RPAREN  */
#line 1478 "1805068_parser.y"
                                                                                                        { 
																	str = "("; str += (yyvsp[-1].sym)->name; str += ")";
																	(yyval.sym) = new SymbolInfo(str, (yyvsp[-1].sym)->type);
																	logData(logFile, yylineno, "factor : LPAREN expression RPAREN", (yyval.sym)->name);
																}
#line 3088 "1805068_parser.tab.c"
    break;

  case 85: /* factor: CONST_INT  */
#line 1483 "1805068_parser.y"
                                                                                                                {
																	(yyval.sym) = new SymbolInfo((yyvsp[0].sym)->name, "int");
																	if (!inFactorArgList)
																	{
																		string ASMCode = "MOV CX, " + (yyvsp[0].sym)->name;
																		printToASM(ASMCode, codeFile);
																	}
																	logData(logFile, yylineno, "factor : CONST_INT", (yyval.sym)->name);
	 															}
#line 3102 "1805068_parser.tab.c"
    break;

  case 86: /* factor: CONST_FLOAT  */
#line 1492 "1805068_parser.y"
                                                                                                                { 
																	(yyval.sym) = new SymbolInfo((yyvsp[0].sym)->name, "float");
																	logData(logFile, yylineno, "factor : CONST_FLOAT", (yyval.sym)->name);
	 															}
#line 3111 "1805068_parser.tab.c"
    break;

  case 87: /* factor: variable INCOP  */
#line 1496 "1805068_parser.y"
                                                                                                                {
																	str = (yyvsp[-1].sym)->name; str += "++";
																	(yyval.sym) = new SymbolInfo(str, (yyvsp[-1].sym)->getType());
																	logData(logFile, yylineno, "factor : variable INCOP", (yyval.sym)->name);

																	// ASM Code
																	// increase value of variable and save it again
																	SymbolInfo *current = table->lookUp(getArrayName((yyvsp[-1].sym)->name));
																	if (current->isArray())
																	{
																		char ASMCode[10];
																		
																		int index = getArraySize((yyvsp[-1].sym)->name);
																		printToASM("PUSH BP", codeFile);
																		printToASM("SAL CX, 1", codeFile);
																		sprintf(ASMCode, "ADD CX, %d", current->getOffset());
																		printToASM(ASMCode, codeFile);
																		printToASM("ADD BP, CX", codeFile);
																		printToASM("MOV CX , PTR WORD [BP]", codeFile);
																		printToASM("INC CX", codeFile);
																		printToASM("MOV PTR WORD [BP], CX", codeFile);
																		printToASM("POP BP", codeFile);
																	}
																	else
																	{
																		// bring to CX, add 1, send it back
																		char ASMCode[10];
																		sprintf(ASMCode, "MOV CX, %d[BP]", current->getOffset());
																		printToASM(ASMCode, codeFile);
																		printToASM("INC CX", codeFile);
																		sprintf(ASMCode, "MOV %d[BP], CX", current->getOffset());
																		printToASM(ASMCode, codeFile);
																	}
																}
#line 3150 "1805068_parser.tab.c"
    break;

  case 88: /* factor: variable DECOP  */
#line 1530 "1805068_parser.y"
                                                                                                                {
																	str = (yyvsp[-1].sym)->name; str += "--";
																	(yyval.sym) = new SymbolInfo(str, (yyvsp[-1].sym)->getType());
																	logData(logFile, yylineno, "factor : variable DECOP", (yyval.sym)->name);

																	SymbolInfo *current = table->lookUp(getArrayName((yyvsp[-1].sym)->name));
																	if (current->isArray())
																	{
																		char ASMCode[10];
																		
																		int index = getArraySize((yyvsp[-1].sym)->name);
																		printToASM("PUSH BP", codeFile);
																		printToASM("SAL CX, 1", codeFile);
																		sprintf(ASMCode, "ADD CX, %d", current->getOffset());
																		printToASM(ASMCode, codeFile);
																		printToASM("ADD BP, CX", codeFile);
																		printToASM("MOV CX , PTR WORD [BP]", codeFile);
																		printToASM("DEC CX", codeFile);
																		printToASM("MOV PTR WORD [BP], CX", codeFile);
																		printToASM("POP BP", codeFile);
																	}
																	else
																	{
																		// bring to CX, add 1, send it back
																		char ASMCode[10];
																		sprintf(ASMCode, "MOV CX, %d[BP]", current->getOffset());
																		printToASM(ASMCode, codeFile);
																		printToASM("DEC CX", codeFile);
																		sprintf(ASMCode, "MOV %d[BP], CX", current->getOffset());
																		printToASM(ASMCode, codeFile);
																	}
																}
#line 3187 "1805068_parser.tab.c"
    break;

  case 89: /* argument_list: arguments  */
#line 1564 "1805068_parser.y"
                                                                                                        {
																	(yyval.sym) = (yyvsp[0].sym);
																	logData(logFile, yylineno, "argument_list : arguments", (yyval.sym)->name);
																}
#line 3196 "1805068_parser.tab.c"
    break;

  case 90: /* argument_list: %empty  */
#line 1568 "1805068_parser.y"
                                                                                                                                {
																	(yyval.sym) = new SymbolInfo("", "none");
																	logData(logFile, yylineno, "argument_list : ", (yyval.sym)->name);
			  													}
#line 3205 "1805068_parser.tab.c"
    break;

  case 91: /* arguments: arguments COMMA logic_expression  */
#line 1574 "1805068_parser.y"
                                                                                {
																	str = (yyvsp[-2].sym)->name; str += ","; str += (yyvsp[0].sym)->name;
																	string argTypes = (yyvsp[-2].sym)->type + "," + (yyvsp[0].sym)->type;
																	(yyval.sym) = new SymbolInfo(str, argTypes);
																	logData(logFile, yylineno, "arguments : arguments COMMA logic_expression", (yyval.sym)->name);
																}
#line 3216 "1805068_parser.tab.c"
    break;

  case 92: /* arguments: logic_expression  */
#line 1580 "1805068_parser.y"
                                                                                                        {
			  														(yyval.sym) = (yyvsp[0].sym);
																	logData(logFile, yylineno, "arguments : logic_expression", (yyval.sym)->name);
		  														}
#line 3225 "1805068_parser.tab.c"
    break;


#line 3229 "1805068_parser.tab.c"

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

#line 1587 "1805068_parser.y"

int main(int argc,char *argv[])
{
	table = new SymbolTable(30);
	inputFile = fopen("input.txt", "r");
	codeFile = fopen("mycode.asm", "w");
	logFile = fopen("log.txt", "w");
	errorFile = fopen("error.txt", "w");
	yyin = inputFile;
	yyparse();
	table->printAllScopeTables(logFile);
	fprintf(logFile, "Total Lines: %d\n", yylineno);
	fprintf(logFile, "Total Errors: %d\n", errorCount);
	return 0;
}

