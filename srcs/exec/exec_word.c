#include "../../includes/minishell.h"

static void	exec_restore_fd(int *prev_fd);

int	exec_single_word(t_info *info, t_tree_node *root)
{
	pid_t	pid;
	int		status;

	if (root->type == TN_PARENS)
		return (exec_parens(root));
	else
	{
		if (check_builtin(root->command) == EXIT_SUCCESS)
			return (run_builtin(info, root));
		pid = fork();
		if (pid == -1)
			exit(0);
		if (pid == 0)
		{
			status = exec_word_child(info, root);
			exit(status);
		}
		waitpid(pid, &g_var.status, 0);
		return (check_status(g_var.status));
	}
}

int	exec_word(t_info *info, t_tree_node *root) //왜 && || 반대로 나오냐..이유는 부모프로세스로 실패했다는 사실을 전달해야 함
{
	pid_t	pid;
	int		status;
	int		pid_status;
	int fds[2];
	char buf[3];

	buf[0] = 'o';
	buf[1] = 'k';
	buf[2] = '\0';
	status = EXIT_SUCCESS;//
	pipe(fds);
	signal(SIGINT, &sig_exec);
	signal(SIGQUIT, &sig_exec);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		if (root->type == TN_PARENS)
			return (exec_parens(root));

		status = exec_word_child(info, root);
		if (status == EXIT_FAILURE)
		{
			buf[0] = 'e';
			buf[1] = 'r';
			buf[2] = '\0';
			close(fds[0]);
			write(fds[1], buf, 3);
		}
		exit(status);
	}
	waitpid(pid, &pid_status, 0);
	close(fds[1]);
	read(fds[0], buf, 3);
	if (ft_strncmp(buf, "er", 2) == 0)
		status = EXIT_FAILURE;
	return (check_status(status));
}


int	exec_last_word_child(t_info *info, t_tree_node *root, t_pipe p)
{
	dup2(p.prev_fd, STDIN_FILENO);
	close(p.prev_fd);
	if (root->type == TN_PARENS)
		exec_parens(root);
	else
	{
		if (check_builtin(root->command) == EXIT_SUCCESS)
			p.status = run_builtin(info, root);
		else
			p.status = exec_word_child(info, root);
	}
	return (p.status);
}

int	exec_word_child(t_info *info, t_tree_node *root)
{
	char	*cmd;
	char	*path;
	char	**env;
	char	**cmd_list;
	int		r_status;

	if (root->redir)
	{
		r_status = redirection(info, root);
		if (r_status != EXIT_FAILURE)
			return (r_status);
	}
	if (root->command)
	{
		cmd_list = exec_token_str_list(root->command);
		cmd = ft_strjoin("/", cmd_list[0]);
		env = exec_env_str_list();
		path = exec_find_path(cmd, env);
		free(cmd);
		if (execve(path, cmd_list, env) == -1)
		{
			error_exit("command not found\n");
			g_var.status = 127;
			return (g_var.status);
		}
	}
	return (EXIT_SUCCESS);
}

static void	exec_restore_fd(int *prev_fd)
{
	int		fd[2];

	fd[READ_END] = dup(STDIN_FILENO);
	fd[WRITE_END] = dup(STDOUT_FILENO);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	dup2(prev_fd[READ_END], STDIN_FILENO);
	close(prev_fd[READ_END]);
	dup2(prev_fd[WRITE_END], STDOUT_FILENO);
	close(prev_fd[WRITE_END]);
}
