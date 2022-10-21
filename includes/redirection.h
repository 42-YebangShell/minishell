#ifndef REDIRECTION_H
# define REDIRECTION_H

int	apply_redirection(t_info *info, t_tree_node *root);
int	redir_open_fd(t_info *info, t_token *token);
int redir_open_file(char *filename, t_token *token);
void	line_write(int fd, char *limiter);
int	apply_heredoc(t_info *info, t_token *token);

#endif
