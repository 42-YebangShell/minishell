#include "../../includes/minishell.h"

int	exec_single_word(t_info *info, t_tree_node *root)
{
	int	fd[2];
	int r_status;

	r_status = 0;
	if (root->redir)
	{
		r_status = apply_redirection(info, root);
		
	}
	if (r_status)
	{

	}
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
			status = exec_cmd_child(info, root);
			exit(status);
		}
		waitpid(pid, &g_var.status, 0);
		return (check_status(g_var.status));
	}
}

int	exec_cmd_child(t_info *info, t_tree_node *root)
{
	int	r_status;

	r_status = (info, root);
	if (r_status)
		return (r_status);
	if (!root)
		return (EXIT_SUCCESS);
	find_path(root->)
}