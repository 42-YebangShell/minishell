#ifndef UTILS_H
# define UTILS_H

// builtin
int	check_builtin(t_token *token);
char	*exec_rm_char(t_token *token);

int	run_builtin(t_info *info, t_tree_node *root);
/*	perror.c	*/
void	ft_perror(char *str);
int	check_syntax_error(t_token *token);
/*	redirection.c	*/
/*	signal_handler.c	*/
void	sig_readline(int signo);
void	sig_exec(int sig);
/*	token.c	*/
t_token	*new_token(t_token token);
void	add_token(t_token **token_list, t_token *new);
t_token	*get_last_token(t_token *tokens);
void	*delete_token(t_token *tokens);
/*	tree_node.c	*/
t_tree_node	*create_btree_node(t_token *tokens);
void	delete_node(t_tree_node *node);
int	tree_node_type(int type);
/*	utils.c	*/
int	str_len(char *str, char c, int i, int type);
int	str_parens(char *str, int i);
/*	welcome_screen.c	*/
void	welcome_screen(void);

#endif
