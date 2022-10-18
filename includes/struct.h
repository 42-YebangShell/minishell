#ifndef STRUCT_H
# define STRUCT_H

# include <termios.h>
# include "define.h"

typedef struct s_environ
{
	char				*key;
	char				*value;
	struct s_environ	*next;
}	t_environ;

typedef struct s_global
{
	int				status;
	t_environ		*env_list;
	struct termios	 settings;
} t_global;

typedef struct s_token
{
	enum e_token_type	type;
	char				*contents;
	struct s_token		*prev;
	struct s_token		*next;
}	t_token;

typedef struct s_tree_node
{
	enum e_node_type	type;
	t_token				*tokens;
	t_token				*words;
	t_token				*redir;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

typedef struct s_info
{
	t_tree_node	*root;
	t_token		*tokens;
}	t_info;

#endif