/*
Z88-DK Z80ASM - Z80 Assembler

Copyright (C) Gunther Strube, InterLogic 1993-99
Copyright (C) Paulo Custodio, 2011-2021
License: The Artistic License 2.0, http://www.perlfoundation.org/artistic_license_2_0
Repository: https://github.com/z88dk/z88dk

Define ragel-based parser. 
*/

#include "class.h"
#include "codearea.h"
#include "die.h"
#include "directives.h"
#include "expr.h"
#include "if.h"
#include "listfile.h"
#include "module.h"
#include "opcodes.h"
#include "parse.h"
#include "scan.h"
#include "str.h"
#include "strutil.h"
#include "sym.h"
#include "symtab.h"
#include "utarray.h"
#include "utstring.h"
#include "zutils.h"
#include <ctype.h>

/*-----------------------------------------------------------------------------
* 	Array of tokens
*----------------------------------------------------------------------------*/
static UT_icd ut_Sym_icd = { sizeof(Sym), NULL, NULL, NULL };

/*-----------------------------------------------------------------------------
* 	Current parse context
*----------------------------------------------------------------------------*/
ParseCtx *ParseCtx_new(void)
{
	ParseCtx *ctx = m_new(ParseCtx);

	utarray_new(ctx->tokens, &ut_Sym_icd);
	utarray_new(ctx->token_strings, &ut_str_icd);
	utarray_new(ctx->exprs, &ut_exprs_icd);

	ctx->current_sm = SM_MAIN;

	return ctx;
}

void ParseCtx_delete(ParseCtx *ctx)
{
	utarray_free(ctx->exprs);
	utarray_free(ctx->token_strings);
	utarray_free(ctx->tokens);
	m_free(ctx);
}

/*-----------------------------------------------------------------------------
*   Parse expression and push it to exprs
*----------------------------------------------------------------------------*/

/* save the current scanner context and parse the given expression */
struct Expr *parse_expr(const char *expr_text)
{
	Expr *expr;
	int num_errors;

	save_scan_state();
	{
		sfile_hold_input();
		{
			SetTemporaryLine(expr_text);
			num_errors = get_num_errors();
			found_EOL = false;
			scan_expect_operands();
			GetSym();
			expr = expr_parse();		/* may output error */
			if (sym.tok != TK_END && sym.tok != TK_NEWLINE &&
				num_errors == get_num_errors()) {
				error_syntax();
				OBJ_DELETE(expr);
				expr = NULL;
			}
		}
		sfile_unhold_input();
	}
	restore_scan_state();
	
	return expr;
}

/* push current expression */
static void push_expr(ParseCtx *ctx)
{
	STR_DEFINE(expr_text, STR_SIZE);
	Expr *expr;
	Sym  *expr_p;

	/* build expression text - split constant prefixes from numbers and names */
	Str_clear(expr_text);
	bool last_was_prefix = false;
	for (expr_p = ctx->expr_start; expr_p < ctx->p; expr_p++)
	{
		if (last_was_prefix && expr_p->tlen > 0 &&
			(isalnum(*expr_p->tstart) || *expr_p->tstart == '"'))
		{
			Str_append_char(expr_text, ' ');
			last_was_prefix = false;
		}

		Str_append_n(expr_text, expr_p->tstart, expr_p->tlen);

		if (expr_p->tlen > 0)
		{
			switch (expr_p->tstart[expr_p->tlen - 1])
			{
			case '@':
			case '%':
			case '$':
				last_was_prefix = true;
				break;

			default:
				last_was_prefix = false;
			}
		}
	}
	
	/* parse expression */
	expr = parse_expr(Str_data(expr_text));

	/* push the new expression, or NULL on error */
	utarray_push_back(ctx->exprs, &expr);

	STR_DELETE(expr_text);
}

/*-----------------------------------------------------------------------------
*   Pop and return expression
*----------------------------------------------------------------------------*/
static Expr *pop_expr(ParseCtx *ctx)
{
	Expr *expr;

	expr = *((Expr **)utarray_back(ctx->exprs));
	*((Expr **)utarray_back(ctx->exprs)) = NULL;		/* do not destroy */
	
	utarray_pop_back(ctx->exprs);

	return expr;
}

/*-----------------------------------------------------------------------------
*   Pop and compute expression, issue error on failure
*----------------------------------------------------------------------------*/
static void pop_eval_expr(ParseCtx *ctx, int *pvalue, bool *perror)
{
	Expr *expr;

	*pvalue = 0;
	*perror = false;

	expr = pop_expr(ctx);
	if (expr == NULL)
	{
		*perror = true;				/* error output by push_expr() */
		return;
	}

	/* eval and discard expression */
	*pvalue = Expr_eval(expr, true);
	*perror = (expr->result.not_evaluable);
	OBJ_DELETE(expr);
}

/*-----------------------------------------------------------------------------
*   return new auto-label in strpool
*----------------------------------------------------------------------------*/
const char *autolabel(void)
{
	STR_DEFINE(label, STR_SIZE);
	static int n;
	const char *ret;

	Str_sprintf(label, "__autolabel_%04d", ++n);
	ret = spool_add(Str_data(label));

	STR_DELETE(label);
	return ret;
}

/*-----------------------------------------------------------------------------
*   String pool for the current statement
*----------------------------------------------------------------------------*/
static char *token_strings_add(ParseCtx *ctx, char *str)
{
	if (!str)		/* NULL string */
		return NULL;

	utarray_push_back(ctx->token_strings, &str);
	return *((char **)utarray_back(ctx->token_strings));
}

/*-----------------------------------------------------------------------------
*   Read tokens from the current statement into tokensd[], to be parsed
*	by state machine
*----------------------------------------------------------------------------*/
static void read_token(ParseCtx *ctx)
{
	STR_DEFINE(buffer, STR_SIZE);
	Sym sym_copy;
	int p_index;
	int expr_start_index;

	p_index = ctx->p ? ctx->p - (Sym *)utarray_front(ctx->tokens) : -1;
	expr_start_index = ctx->expr_start ? ctx->expr_start - (Sym *)utarray_front(ctx->tokens) : -1;

	sym_copy = sym;

	/* make text to be used while concatenating tokens to build an expression to parse */
	switch (sym_copy.tok)
	{
	case TK_NUMBER:
		Str_sprintf(buffer, "%d", sym_copy.number);
		sym_copy.tstart = token_strings_add(ctx, Str_data(buffer));
		sym_copy.tlen = Str_len(buffer);
		break;

	case TK_NAME:
	case TK_LABEL:
	case TK_STRING:
		break;

	case TK_END:
		sym_copy.tstart = "";
		sym_copy.tlen = 0;
		break;

	default:;
//		if (!*(sym_copy.text))
//			xassert(*(sym_copy.text));
	}
//	sym_copy.string = token_strings_add(sym.string);
	utarray_push_back(ctx->tokens, &sym_copy);

	ctx->p = (Sym *)utarray_front(ctx->tokens) + (p_index >= 0 ? p_index : 0);
	ctx->pe = (Sym *)utarray_back(ctx->tokens) + 1;

	if (sym.tok == TK_END)
		ctx->eof_ = ctx->pe;
	else
		ctx->eof_ = NULL;

	ctx->expr_start = expr_start_index >= 0 ? ((Sym *)utarray_front(ctx->tokens)) + expr_start_index : NULL;

	// if symbol is a prefix, set scanner to get an opcode
	if (sym.tok == TK_ALTD || sym.tok == TK_IOE || sym.tok == TK_IOI)
		scan_expect_opcode();

	GetSym();

	STR_DELETE(buffer);
}

static void free_tokens(ParseCtx *ctx)
{
	utarray_clear(ctx->tokens);
	utarray_clear(ctx->token_strings);
	if (ctx->current_sm != SM_DMA_PARAMS) {		// DMA_PARAMS needs to preserve exprs between lines
		utarray_clear(ctx->exprs);
	}
}

/*-----------------------------------------------------------------------------
*   IF, IFDEF, IFNDEF, ELSE, ELIF, ELIFDEF, ELIFNDEF, ENDIF
*----------------------------------------------------------------------------*/
void parse_const_expr_eval(const char* expr_text, int* result, bool* error) {
	*result = 0;
	*error = false;
	struct Expr* expr = parse_expr(expr_text);
	if (!expr)
		*error = true;
	else {
		// eval and discard expression
		*result = Expr_eval(expr, true);
		*error = (expr->result.not_evaluable);
		OBJ_DELETE(expr);
	}
}

void parse_expr_eval_if_condition(const char* expr_text, bool* condition, bool* error) {
	*condition = *error = false;
	struct Expr *expr = parse_expr(expr_text);
	if (expr)
		*condition = check_if_condition(expr);
	else
		*error = true;
}

bool check_if_condition(Expr *expr) {
	int value;
	bool condition;

	// eval and discard expression, ignore errors
	value = Expr_eval(expr, false);
	if (value == 0)				// ignore expr->result.not_evaluable, as undefined values result in 0
		condition = false;
	else
		condition = true;

	OBJ_DELETE(expr);

	return condition;
}

bool check_ifdef_condition(const char *name) {
	Symbol *symbol;

	symbol = find_symbol(name, CURRENTMODULE->local_symtab);
	if (symbol != NULL && (symbol->is_defined || (symbol->scope == SCOPE_EXTERN || symbol->scope == SCOPE_GLOBAL)))
		return true;

	symbol = find_symbol(name, global_symtab);
	if (symbol != NULL && (symbol->is_defined || (symbol->scope == SCOPE_EXTERN || symbol->scope == SCOPE_GLOBAL)))
		return true;

	return false;
}

/*-----------------------------------------------------------------------------
*   Import parser generated by ragel
*----------------------------------------------------------------------------*/
#include "parse_rules.h"

/*-----------------------------------------------------------------------------
*   parse the given assembly file, return false if failed
*----------------------------------------------------------------------------*/
static void parseline(ParseCtx *ctx)
{
	int start_num_errors;

	next_PC();				/* update assembler program counter */
	found_EOL = false;			/* reset END OF LINE flag */

	start_num_errors = get_num_errors();

	scan_expect_opcode();
	GetSym();

	if (get_num_errors() != start_num_errors)		/* detect errors in GetSym() */
		Skipline();
	else if (!parse_statement(ctx))
	{
		if (get_num_errors() == start_num_errors) {	/* no error output yet */
			error_syntax();
			ctx->current_sm = SM_MAIN;				/* reset state machine */
		}

		Skipline();
	}
}

void parse_file(const char* filename)
{
	ParseCtx* ctx = ParseCtx_new();
	{
		if (sfile_open(filename, true)) {
			if (opts.verbose)
				printf("Reading '%s' = '%s'\n",
					path_canon(filename), path_canon(sfile_filename()));	/* display name of file */

			sym.tok = TK_NIL;
			while (sym.tok != TK_END)
				parseline(ctx);				/* before parsing it */
		}

		sym.tok = TK_NEWLINE;				/* when called recursively, need to make tok != TK_NIL */
	}
	ParseCtx_delete(ctx);
}

/*-----------------------------------------------------------------------------
*   Parse one statement, if possible
*----------------------------------------------------------------------------*/
bool parse_statement(ParseCtx *ctx)
{
	bool parse_ok;

	save_scan_state();
	{
		parse_ok = _parse_statement(ctx);
		free_tokens(ctx);
	}
	if (parse_ok)
		drop_scan_state();
	else
		restore_scan_state();

	return parse_ok;
}
