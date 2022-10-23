#include "../../includes/minishell.h"

void	exec_paren(t_tree_node *root)
{
	char	*cmd_line;

	cmd_line = exec_rm_char(root->tokens);
	ft_putstr_fd(cmd_line, STDOUT_FILENO);
}