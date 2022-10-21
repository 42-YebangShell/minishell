#include "../../includes/minishell.h"

int exec_cmd(t_info *info, t_tree_node *root)
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
		waitpid(pid, g_var.status, 0);
		return (g_var.status);
	}
}
