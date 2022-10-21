#include "../../includes/minishell.h"

void execution(t_info *info)
{
	signal(SIGINT, &sig_exec);
	signal(SIGQUIT, &sig_exec);
	ft_display_ctrlx_set(DISPLAY);
	g_var.status = execute_btree_node(info, info->r_node);
	delete_node(info->r_node);
	info->r_node = NULL;
}

int	execute_btree_node(t_info *info, t_tree_node *root)
{
	int status;

	// subshell
	if (root->type == TN_PARENS)
		status = exec_paren(info, root);
	else if (root->type == TN_AND || root->type == TN_OR)
		status = exec_and_or(info, root);
	else if (root->type == TN_PIPE)
		status = exec_pipe(info, root);
	else
	{
		if (!root->right)
			status = exec_single_word(info, root);
		else
			status = exec_word(info, root);
	}
}