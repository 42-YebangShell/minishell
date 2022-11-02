#ifndef EXEC_H
# define EXEC_H

// execution
int		exec_set(char *cmd_line);
void	execution(t_info	*info);
void	execute_btree_node(t_info *info, t_tree_node *root);
void	expand(t_token **token);

// exec_parens
int		exec_parens(t_tree_node *root);

// exec_and_or
void	exec_and_or(t_info *info, t_tree_node *root);

// exec_pipe
int		exec_pipe(t_info *info, t_tree_node *root);

// exec_word
int		exec_single_word(t_info *info, t_tree_node *root);
int		exec_word(t_info *info, t_tree_node *root);
int		exec_word_child(t_info *info, t_tree_node *root);
int		exec_last_word_child(t_info *info, t_tree_node *root, t_pipe p);

#endif