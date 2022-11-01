#include "../../includes/minishell.h"

static void	redir_here_doc_child(char *limiter);

int	redir_here_doc_file(t_token *token)
{
	pid_t	pid;
	int		status;
	char	*limiter;

	limiter = exec_rm_char(token->next);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		signal(SIGINT, &sig_here_doc);
		redir_here_doc_child(limiter);
		exit(EXIT_FAILURE);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &pid, 0);
		if (check_status(pid) == 130)
			return (EXIT_FAILURE);
	}
	return (SUCCESS);
}

static void	redir_here_doc_child(char *limiter)
{
	int		hd_fd;
	char	*line;
	char	*hd_filename;

	signal(SIGINT, SIG_DFL);
	hd_filename = ft_strjoin(".here_doc", ft_itoa(g_var.hd_cnt));
	hd_fd = open(hd_filename, O_CREAT | O_RDWR | O_TRUNC, 0744);
	if (hd_fd == -1)
	{
		error_exit("ERR) HEREDOC: File creation failed!");
		exit(EXIT_FAILURE);
	}
	line = readline("> ");
	while (line && ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		ft_putstr_fd(line, hd_fd);
		ft_putstr_fd("\n", hd_fd);
		free(line);
		line = readline("> ");
	}
	close(hd_fd);
	exit(EXIT_SUCCESS);
}
