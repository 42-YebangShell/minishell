#include "../../includes/minishell.h"

void execution(t_info *info)
{
	signal(SIGINT, &sig_exec);
	signal(SIGQUIT, &sig_exec);
	execute_btree_node(info, info->r_node);
	delete_node(info->r_node);
}

void	execute_btree_node(t_info *info, t_tree_node *root)
{
	if (root->type == TN_PARENS)
		exec_paren(root);
	else if (root->type == TN_AND || root->type == TN_OR)
		exec_and_or(info, root);
	else if (root->type == TN_PIPE)
		g_var.status = exec_pipe(info, root);
	else
	{
		if (!root->right)
			g_var.status = exec_single_word(info, root);
		else
			g_var.status = exec_word(info, root);
	}
	// if (check_builtin(root->command) == EXIT_SUCCESS)
	// 	g_var.status = run_builtin(info, root);
}