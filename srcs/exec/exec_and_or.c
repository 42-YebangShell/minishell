#include "../../includes/minishell.h"

void	exec_and_or(t_info *info, t_tree_node *root)
{
	int	status;

	if (root->left->type == TN_WORD)
		status = exec_word(info, root->left);
	if (root->left->type == TN_PARENS)
		status = exec_parens(root->left);
	if (root->left->type == TN_PIPE)
		status = exec_pipe(info, root->left);
	if ((root->type == TN_AND && status == EXIT_SUCCESS) || \
		(root->type == TN_OR && status != EXIT_SUCCESS))
		execute_btree_node(info, root->right);
	g_var.status = status;
}
