#include "../../includes/minishell.h"

void	exec_paren(t_tree_node *root)
{
	char	*cmd_line;

	cmd_line = exec_rm_paren(root->tokens);
	if (cmd_line)
		set_excute(cmd_line);
}
