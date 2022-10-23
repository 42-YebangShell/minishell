#ifndef UTILS_H
# define UTILS_H

// builtin
int			check_builtin(t_token *token);
int			run_builtin(t_info *info, t_tree_node *root);

// error
void		error_exit(char *str);
void		ft_perror(char *err_msg1, char *err_msg2);
int			check_syntax_error(t_token *token);

// exec
void		exec_make_env_str(char *env[]);
char		**exec_env_str_list(void);
char		**exec_token_str_list(t_token *token);
char		*exec_find_path(char *cmd, char *envp[]);
char		*exec_rm_char(t_token *token);

// redirection
int			redir_check_here_doc(t_info *info);

// signal
void		sig_readline(int signo);
void		sig_exec(int sig);
void		sig_here_doc(int sig);

// token
t_token		*new_token(t_token token);
void		add_token(t_token **token_list, t_token *new);
t_token		*get_last_token(t_token *tokens);
int			get_token_length(t_token *tokens);
void		*delete_token(t_token *tokens);

// tree
t_tree_node	*create_btree_node(t_token *tokens);
void		delete_node(t_tree_node *node);
int			tree_node_type(int type);

// utils
int			str_len(char *str, char c, int i, int type);
int			str_parens(char *str, int i);
void		ft_display_ctrlx_set(int flag);
int			check_status(int status);
void		add_str();

void		welcome_screen(void);

#endif
