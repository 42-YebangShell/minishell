#include "../../includes/minishell.h"

int	redir_here_doc(char *limiter)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		redir_here_doc_child(fd[WRITE_END], limiter);
	else
	{
		signal(SIGINT, SIG_IGN);
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		waitpid(pid, &g_var.status, WNOHANG);
	}
	if (check_status(g_var.status) == EXIT_SUCCESS)
		return (TRUE);
	return (FALSE);
}

void	redir_here_doc_child(int fd, char *limiter)
{
	char	*line;

	signal(SIGINT, sig_here_doc);
	while (1)
	{
		line = readline("> ");
		// line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			exit(EXIT_SUCCESS);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
}
