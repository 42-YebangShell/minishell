#ifndef DEFINE_H
# define DEFINE_H

# define ERROR -1
# define NODISPLAY 0
# define DISPLAY 	1

enum	e_token_type
{
	NONE,
	OR,
	AND,
	PIPE,
	CMD,
	OPTION,
	S_QUOTE,
	D_QUOTE,
	INP_RDIR,
	OUT_RDIR,
	APP_RDIR,
	HERE_DOC,
	PARENS,
};

enum	e_node_type
{
	TK_OR,
	TK_AND,
	TK_PIPE,
	TK_WORD,
	TK_PARENS
};

#endif