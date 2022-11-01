#include "../../includes/minishell.h"

static int	exec_count_pipe(t_tree_node *root);
static void	exec_pipe_child(t_info *info, t_tree_node *root, t_pipe p);
static int	exec_last_pipe(t_info *info, t_tree_node *root, t_pipe p);
static void	exit_wait(int cnt);

int	exec_pipe(t_info *info, t_tree_node *root)
{
	t_pipe	p;
	int		i;

	i = 0;
	p.prev_fd = -1;
	p.cnt = exec_count_pipe(root);
	while (i++ < p.cnt)
	{
		if (pipe(p.fd) == -1)
			exit_wait(i - 1);
		p.pid = fork();
		if (p.pid == -1)
			exit_wait(i - 1);
		if (p.pid == 0)
			exec_pipe_child(info, root->left, p);
		else
		{
			close(p.fd[WRITE_END]);
			if (p.prev_fd != -1)
				close(p.prev_fd);
			p.prev_fd = p.fd[READ_END];
			root = root->right;
		}
	}
	return (exec_last_pipe(info, root, p));
}

static int	exec_count_pipe(t_tree_node *root)
{
	int	cnt;

	cnt = 0;
	while (root->type == TN_PIPE)
	{
		cnt++;
		root = root->right;
	}
	return (cnt);
}

static void	exec_pipe_child(t_info *info, t_tree_node *root, t_pipe p)
{
	if (root->type == TN_PARENS)
		exec_parens(root);
	if (p.prev_fd != -1)
	{
		dup2(p.prev_fd, STDIN_FILENO);
		close(p.prev_fd);
	}
	close(p.fd[READ_END]);
	dup2(p.fd[WRITE_END], STDOUT_FILENO);
	close(p.fd[WRITE_END]);
	if (root->type != TN_PARENS)
	{
		if (check_builtin(root->command) == EXIT_SUCCESS)
			p.status = run_builtin(info, root);
		else
			p.status = exec_word_child(info, root);
	}
	exit(p.status);
}

static int	exec_last_pipe(t_info *info, t_tree_node *root, t_pipe p)
{
	int	i;
	int	status;

	i = 0;
	p.pid = fork();
	if (p.pid == -1)
		exit_wait(p.cnt);
	else if (p.pid == 0)
	{
		status = exec_last_word_child(info, root, p);
		exit(status);
	}
	close(p.prev_fd);
	while (i++ < p.cnt + 1)
	{
		if (waitpid(-1, &p.status, 0) == p.pid)
			status = p.status;
	}
	return (check_status(status));
}

static void	exit_wait(int cnt)
{
	while (cnt > 0)
	{
		waitpid(-1, NULL, WNOHANG);
		cnt--;
	}
	exit(EXIT_FAILURE);
}
