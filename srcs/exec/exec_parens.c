#include "../../includes/minishell.h"

void	exec_parens(t_tree_node *root)
{
	char	*cmd_line;

	cmd_line = exec_rm_char(root->tokens);
	if (cmd_line)
		exec_set(cmd_line);
}
