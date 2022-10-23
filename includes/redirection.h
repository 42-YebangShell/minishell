#ifndef REDIRECTION_H
# define REDIRECTION_H

int	apply_redirection(t_info *info, t_tree_node *root);
int	redir_open_fd(t_info *info, t_token *token);
int redir_open_file(char *filename, t_token *token);

int	redir_here_doc(char *limiter);
void	redir_here_doc_child(int fd, char *limiter);

#endif
