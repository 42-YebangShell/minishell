#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/get_next_line/get_next_line.h"

# include "struct.h"

t_global	g_var;
void		rl_replace_line (const char *text, int clear_undo);

/*	utils	*/
/*	utils-welcome_screen	*/
void		welcome_screen(void);
/*	utils-perror	*/
void		ft_perror(char *str);
/*	utils-utils	*/
int			str_len(char *str, char c, int i, int type);
int			str_parens(char *str, int i);
/*	utils-token	*/
t_token		*new_token(t_token token);
void		add_token(t_token **token_list, t_token *new);
t_token		*get_last_token(t_token *tokens);
void		*delete_token(t_token *tokens);
/*	utils-tree_node	*/
t_tree_node	*create_btree_node(t_token *tokens);
void		delete_node(t_tree_node *node);
int			tree_node_type(int type);

/*	env		*/
t_environ	*get_envp_list(char **envp);

/*	parser	*/
/*	parser-tokenizer	*/
void		tokenizer(t_token **tokens, char *cmd_line);
t_token		check_quote(int *i, char *line);
t_token		check_parens(int *i, char *line);
t_token		check_and_or_pipe(int *i, char *line);
t_token		check_redir(int *i, char *line);
t_token		check_cmd_or_option(int *i, char *line);
/*	parser-set_btree	*/
void	set_btree_node(t_tree_node **node);




void	show_tokens_data(t_token *tokens);
#endif
