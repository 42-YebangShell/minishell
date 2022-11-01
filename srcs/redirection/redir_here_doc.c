#include "../../includes/minishell.h"

static void	redir_here_doc_child(char *limiter);

int	redir_here_doc(t_info *info, t_token *token)
{
	int		file_cnt;
	int		hd_fd;
	char	*hd_filename;

	file_cnt = redir_here_doc_file_number(info, token);
	hd_filename = ft_strjoin(".here_doc", ft_itoa(file_cnt));
	hd_fd = redir_open_file(hd_filename, O_RDONLY);
	if (hd_fd == -1)
	{
		error_exit("ERR) HEREDOC: File creation failed!");
		return (hd_fd);
	}
	dup2(hd_fd, STDIN_FILENO);
	close(hd_fd);
	return (hd_fd);
}

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
	return (EXIT_SUCCESS);
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
		error_exit("ERR) HEREDOC: File creation failed!");
	line = readline("> ");
	while (line && ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		ft_putstr_fd(line, hd_fd);
		ft_putstr_fd("\n", hd_fd);
		free(line);
		line = readline("> ");
	}
	close(hd_fd);
	exit(EXIT_FAILURE);
}
