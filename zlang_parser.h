/*
    Parser header generated by unicc from zlang_v1.par.
    DO NOT EDIT THIS FILE MANUALLY, IT WILL GO AWAY!
*/

#ifndef ZLANG_PARSER_H
#define ZLANG_PARSER_H

/* Wide character processing enabled? */
#ifndef UNICC_WCHAR
#define UNICC_WCHAR					0
#endif

/* UTF-8 processing enabled? */
#if !UNICC_WCHAR
#ifndef UNICC_UTF8
#	define UNICC_UTF8				1
#endif
#else
#	ifdef UNICC_UTF8
#	undef UNICC_UTF8
#	endif
#	define UNICC_UTF8				0
#endif

/* UNICC_CHAR is used as character type for internal processing */
#ifndef UNICC_CHAR
#if UNICC_UTF8 || UNICC_WCHAR
#	define UNICC_CHAR				wchar_t
#	define UNICC_CHAR_FORMAT		"%S"
#else
#	define UNICC_CHAR				char
#	define UNICC_CHAR_FORMAT		"%s"
#endif
#endif /* UNICC_CHAR */

/* UNICC_SCHAR defines the character type for semantic action procession */
#ifndef UNICC_SCHAR
#if UNICC_WCHAR
#	define UNICC_SCHAR				wchar_t
#	define UNICC_SCHAR_FORMAT		"%S"
#else
#	define UNICC_SCHAR				char
#	define UNICC_SCHAR_FORMAT		"%s"
#endif
#endif /* UNICC_SCHAR */

/* Boolean */
#ifndef UNICC_BOOLEAN
#define UNICC_BOOLEAN			short
#endif

/* Debug level */
#ifndef UNICC_DEBUG
#define UNICC_DEBUG				0
#endif

/* Stack debug switch */
#ifndef UNICC_STACKDEBUG
#define UNICC_STACKDEBUG		0
#endif

/* Parse error macro */
#ifndef UNICC_PARSE_ERROR
#define UNICC_PARSE_ERROR( pcb ) \
    fprintf( stderr, "line %d, column %d: syntax error on symbol %d, token '" \
        UNICC_SCHAR_FORMAT "'\n", \
    ( pcb )->line, ( pcb )->column, pcb->sym, zlang_lexem( pcb ) )
#endif

/* Input buffering clean-up */
#ifndef UNICC_CLEARIN
#define UNICC_CLEARIN( pcb )		zlang_clear_input( pcb )
#endif

/*TODO:*/
#ifndef UNICC_NO_INPUT_BUFFER
#define UNICC_NO_INPUT_BUFFER	0
#endif

/* Memory allocation step size for dynamic stack- and buffer allocation */
#ifndef UNICC_MALLOCSTEP
#define UNICC_MALLOCSTEP		128
#endif

/* Call this when running out of memory during memory allocation */
#ifndef UNICC_OUTOFMEM
#define UNICC_OUTOFMEM( pcb )	fprintf( stderr, \
                                    "Fatal error, ran out of memory\n" ), \
                                exit( 1 )
#endif

/* Static switch */
#ifndef UNICC_STATIC
#define UNICC_STATIC			static
#endif

#ifdef UNICC_PARSER
#undef UNICC_PARSER
#endif
#define UNICC_PARSER			"zlang" "debug"

/* Don't change next three defines below! */
#ifndef UNICC_ERROR
#define UNICC_ERROR				0
#endif
#ifndef UNICC_REDUCE
#define UNICC_REDUCE			1
#endif
#ifndef UNICC_SHIFT
#define UNICC_SHIFT				2
#endif
#ifndef UNICC_SUCCESS
#define UNICC_SUCCESS			4
#endif

/* Error delay after recovery */
#ifndef UNICC_ERROR_DELAY
#define UNICC_ERROR_DELAY		3
#endif

/* Enable/Disable terminal selection in semantic actions */
#ifndef UNICC_SEMANTIC_TERM_SEL
#define UNICC_SEMANTIC_TERM_SEL	0
#endif

/* Value Types */
typedef union zlang_VTYPE
{
    char* value_0;
    int value_1;
} zlang_vtype;



/* Typedef for symbol information table */
typedef struct
{
    char*			name;
    char*			emit;
    short			type;
    UNICC_BOOLEAN	lexem;
    UNICC_BOOLEAN	whitespace;
    UNICC_BOOLEAN	greedy;
} zlang_syminfo;

/* Typedef for production information table */
typedef struct
{
    char*	definition;
    char*	emit;
    int		length;
    int		lhs;
} zlang_prodinfo;

/* Abstract Syntax Tree */
typedef struct zlang_AST zlang_ast;

struct zlang_AST
{
    char*			emit;
    UNICC_SCHAR*	token;

    zlang_ast*	parent;
    zlang_ast*	child;
    zlang_ast*	prev;
    zlang_ast*	next;
};

/* Stack Token */
typedef struct
{
    zlang_vtype		value;
    zlang_ast*		node;

    zlang_syminfo*	symbol;

    int					state;
    unsigned int		line;
    unsigned int		column;
} zlang_tok;


/* Parser Control Block */
typedef struct
{
    /* Is this PCB allocated by parser? */
    char				is_internal;

    /* Stack */
    zlang_tok*		stack;
    zlang_tok*		tos;

    /* Stack size */
    unsigned int		stacksize;

    /* Values */
    zlang_vtype		ret;
    zlang_vtype		test;

    /* State */
    int					act;
    int					idx;
    int					lhs;

    /* Lookahead */
    int					sym;
    int					old_sym;
    unsigned int		len;

    /* Input buffering */
    UNICC_SCHAR*		lexem;
    UNICC_CHAR*			buf;
    UNICC_CHAR*			bufend;
    UNICC_CHAR*			bufsize;

    /* Lexical analysis */
    UNICC_CHAR			next;
    UNICC_CHAR			eof;
    UNICC_BOOLEAN		is_eof;

    /* Error handling */
    int					error_delay;
    int					error_count;

    unsigned int		line;
    unsigned int		column;

    /* Abstract Syntax Tree */
    zlang_ast*		ast;

    /* User-defined components */
    

} zlang_pcb;

#endif /* ZLANG_PARSER_H */
