#ifndef EXEC_H
# define EXEC_H

/* execution.c */
void	execution(t_info *info);
void	exec_set(char *cmd_line);
void	execute_btree_node(t_info *info, t_tree_node *root);

/* exec_and_or.c */
void	exec_and_or(t_info *info, t_tree_node *root);

/* exec_paren.c */
void	exec_paren(t_tree_node *root);

/* exec_pipe.c */
int	exec_pipe(t_info *info, t_tree_node *root);

/* exec_word.c */
int	exec_single_word(t_info *info, t_tree_node *root);
int exec_word(t_info *info, t_tree_node *root);
int	exec_word_child(t_info *info, t_tree_node *root);
int	exec_last_word_child(t_info *info, t_tree_node *root, t_pipe p);

#endif