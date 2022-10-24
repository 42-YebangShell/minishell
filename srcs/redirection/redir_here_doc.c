#include "../../includes/minishell.h"

static void	redir_here_doc_child(char *limiter);

int	redir_here_doc(void)
{
	int		hd_fd;
	char	*hd_filename;

	// 파일 명 찾는 함수 ?? 로직 추가 필요합니다.. 
	hd_filename = ft_strjoin(".here_doc", ft_itoa(0));
	hd_fd = redir_open_file(hd_filename, INP_RDIR);
	if (hd_fd == -1)
	{
		error_exit("ERR) HEREDOC: File creation failed!");
		return (hd_fd);
	}
	dup2(hd_fd, STDIN_FILENO);
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
