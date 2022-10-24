#include "../../includes/minishell.h"

static void	redir_here_doc_child(int fd, char *limiter);

int	redir_here_doc(t_token *token)
{
	pid_t	pid;
	int		fd[2];
	char	*limiter;

	if (!token->next)
		return (EXIT_FAILURE);
	if (token->next->content[0] == (char)'\'' || token->next->content[0] == (char)'\"' )
		limiter = exec_rm_char(token->next);
	else
		limiter = token->next->content;
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
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static void	redir_here_doc_child(int fd, char *limiter)
{
	char	*line;
	char	*hd_filename;

	hd_filename = ft_strjoin(".here_doc", ft_itoa(g_var.hd_cnt));
	signal(SIGINT, &sig_here_doc);
	fd = open(hd_filename, O_CREAT | O_WRONLY | O_TRUNC, 0744);
	if (fd == -1)
		error_exit("heredoc failed");
	ft_putstr_fd("why??\n", 2);////
	while (1)
	{
		signal(SIGINT, &sig_here_doc);
		// line = readline("> ");
		ft_putstr_fd("> ", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
			exit(EXIT_SUCCESS);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
}
