#include "../../includes/minishell.h"

int	exec_parens(t_tree_node *root)
{
	int		status;
	char	*cmd_line;

	status = 0;
	cmd_line = exec_rm_char(root->tokens);
	if (cmd_line)
		status = exec_set(cmd_line);
	return (status);
}
