#ifndef EXEC_H
# define EXEC_H

void	execution(t_info *info);
int		execute_btree_node(t_info *info, t_tree_node *root);

int		exec_and_or(t_info *info, t_tree_node *root);

int		exec_word(t_info *info, t_tree_node *root);
int		exec_single_word(t_info *info, t_tree_node *root);
int		exec_cmd_child(t_info *info, t_tree_node *root);

int		exec_pipe(t_info *info, t_tree_node *root);

#endif