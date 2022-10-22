#ifndef UTILS_H
# define UTILS_H

int			run_builtin(t_info *info, t_tree_node *root);

int			check_status(int status);
int			check_builtin(t_token *token);

void		ft_perror(char *str);
int			check_syntax_error(t_token *token);

void		sig_readline(int signo);
void		sig_exec(int sig);
void		sig_here_doc(int sig);

t_token		*new_token(t_token token);
void		add_token(t_token **token_list, t_token *new);
t_token		*get_last_token(t_token *tokens);
void		*delete_token(t_token *tokens);

t_tree_node	*create_btree_node(t_token *tokens);
void		delete_node(t_tree_node *node);
int			tree_node_type(int type);

int			str_len(char *str, char c, int i, int type);
int			str_parens(char *str, int i);
void		ft_display_ctrlx_set(int flag);
void		set_excute(char *cmd_line);

void		welcome_screen(void);

#endif
