#include "../../includes/minishell.h"

int	apply_redirection(t_info *info, t_tree_node *root)
{
	t_token	*token;
	int		r_status;

	r_status = 0;
	token = root->redir;
	while (token)
	{
		if (token->type == HERE_DOC)
			apply_heredoc(info, token);
		else
			r_status = redir_open_fd(info, token);
		token = token->next;
	}
	return (r_status);
}

int	redir_open_fd(t_info *info, t_token *token)
{
	int		r_status;
	char	*filename;

	filename = NULL;
	if (!token->next)
		return (EXIT_FAILURE);
	filename = token->next->content;
	if (!filename)
		return (EXIT_FAILURE);
	r_status = redir_open_file(filename, token);
	if (r_status)
		return (EXIT_FAILURE);
	return (r_status);
}

int redir_open_file(char *filename, t_token *token)
{
	int	fd;

	fd = -1;
	if (token->type == INP_RDIR && access(filename, F_OK))
	{
		fd = open(filename, O_RDONLY | O_CLOEXEC, 0777);
		dup2(fd, STDIN_FILENO);
	}
	else if (!token->type == INP_RDIR)
	{
		if (token->type == OUT_RDIR)
			fd = open(filename, O_TRUNC | O_CREAT | O_RDWR, 0644);
		else if (token->type == APP_RDIR)
			fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	if (fd == -1)
	{
		ft_perror(filename, ": No such file or directory");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

void	line_write(int fd, char *limiter)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			exit(EXIT_SUCCESS);
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

int	apply_heredoc(t_info *info, t_token *token)
{
	pid_t	pid;
	int		fd[2];
	char	*limiter;

	limiter = token->next->next;
	if (pipe(fd) == -1)
		ft_perror("pipe error", "\n");
	pid = fork();
	if (pid == -1)
		ft_perror("fork error", "\n");
	if (pid == 0)
		line_write(fd[WRITE_END], limiter);
	else
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		waitpid(pid, NULL, WNOHANG);
	}
}