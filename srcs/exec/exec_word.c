#include "../../includes/minishell.h"

static void	exec_restore_fd(int *prev_fd);

int		exec_word(t_info *info, t_tree_node *root)
{
	ft_putstr_fd("exec_word\n", STDOUT_FILENO);
	return (0);
}

int		exec_single_word(t_info *info, t_tree_node *root)
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
		if (r_status == EXIT_FAILURE)
		{
			exec_restore_fd(fd);
			return (r_status);
		}
	}
	execute_btree_node(info, root->right);
	if (root->redir)
		exec_restore_fd(fd);
	return (g_var.status);
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