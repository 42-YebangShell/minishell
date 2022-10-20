#include "../../includes/minishell.h"

void execution(t_tree_node	*r_node)
{
	t_tree_node	*tmp;

	execution(r_node->left);
	if (tmp->type == TN_AND)
	{
		if (!g_var.status)
			return ;
	}
	else if (tmp->type == TN_OR)
	{
		if (g_var.status)
			return ;
	}
	if (tmp->type == TN_PIPE)
	{
			//fd..
			//while
			//fork...
	}
	else
		execution(r_node->right);
}