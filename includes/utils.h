#ifndef UTILS_H
# define UTILS_H

// utils.c
int	str_len(char *str, char c, int i, int type);
int	str_parens(char *str, int i);
void	ft_display_ctrlx_set(int flag);
int	check_status(int status);

// util_tree.c
t_tree_node	*create_btree_node(t_token *tokens);
void	delete_node(t_tree_node *node);
int	tree_node_type(int type);

// util_token.c
t_token	*new_token(t_token token);
void	add_token(t_token **token_list, t_token *new);
t_token	*get_last_token(t_token *tokens);
int		get_token_length(t_token *tokens);
void	*delete_token(t_token *tokens);

// util_signal
void	sig_readline(int signo);
void	sig_exec(int sig);
void	sig_here_doc(int sig);

// util_redirection.c 
int	redir_check_here_doc(t_info *info);

// util_exec.c
char	*exec_rm_paren(t_token *tk_parens);

// util_error.c
void	error_exit(char *str);
void	ft_perror(char *err_msg1, char *err_msg2);
int	check_syntax_error(t_token *token);

// util_exec.c
void	exec_make_env_str(char *env[]);
char	**exec_env_str_list(void);
char	**exec_token_str_list(t_token *token);
char	*exec_find_path(char *cmd, char *envp[]);

// util_builtin.c
#endif
