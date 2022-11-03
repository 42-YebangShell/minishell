#include "../../includes/minishell.h"

int	exec_parens(t_tree_node *root)
{
	pid_t	pid;
	int		status;
	char	*cmd_line;
	pid_t	pid;

	status = 0;
	cmd_line = exec_rm_char(root->tokens);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		if (cmd_line)
			status = exec_set(cmd_line);
		exit(0);
	}
	waitpid(pid, &status, 0);
	return (status);
}