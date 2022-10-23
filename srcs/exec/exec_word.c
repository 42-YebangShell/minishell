#include "../../includes/minishell.h"

static void	exec_restore_fd(int *prev_fd);

int	exec_single_word(t_info *info, t_tree_node *root)
{
	int	fd[2];
	int	r_status;

	r_status = EXIT_FAILURE;
	if (root->redir)
	{
		fd[READ_END] = dup(STDIN_FILENO);
		fd[WRITE_END] = dup(STDOUT_FILENO);
		if (fd[READ_END] == -1 || fd[WRITE_END] == -1)
			exit(EXIT_FAILURE);
		r_status = redirection(info, root);
		if (r_status)
		{
			exec_restore_fd(fd);
			return (r_status);
		}
	}
	g_var.status = execute_bt_node(info, root->right);
	if (root->redir)
		exec_restore_fd(fd);
	return (g_var.status);
}

int exec_word(t_info *info, t_tree_node *root)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, &sig_exec);
	signal(SIGQUIT, &sig_exec);
	if (check_builtin(root))
		return (builtin(info, root));
	else
	{
		pid = fork();
		if (pid == -1)
			exit(0);
		else
		{
			status = exec_word_child(info, root);
			exit(status);
		}
		waitpid(pid, &g_var.status, 0);
		return (check_status(g_var.status));
	}
}

int	exec_word_child(t_info *info, t_tree_node *root)
{
	char	*cmd;
	char	*path;
	char	**env;
	char	**cmd_list;
	int		r_status;

	r_status = redirection(info, root);
	if (r_status)
		return (r_status);
	if (root->command)
	{
		cmd_list = exec_token_str_list(root->command);
		cmd = ft_strjoin("/", cmd_list[0]);
		env = exec_env_str_list();
		path = exec_find_path(cmd, env);
		free(cmd);
		if (execve(path, cmd_list, env) == -1)
			exit_msg("command not found\n", 127);
	}
}

int	exec_last_word_child(t_info *info, t_tree_node *root, t_pipe p)
{
	dup2(p.prev_fd, STDIN_FILENO);
	close(p.prev_fd);
	if (root->type == TN_PARENS)
		exec_paren(root);
	else
	{
		if (check_builtin(root->command))
			p.status = run_builtin(info, root);
		else
			p.status = exec_word_child(info, root);
	}
	return (p.status);
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