#include "../../includes/minishell.h"

void	exec_and_or(t_info *info, t_tree_node *root)
{
	int status;
	
	if (root->left->type == TN_WORD)
		status = exec_word(info, root->left);
	else
		status = exec_pipe(info, root->left);
	if ((root->type == TN_AND && status) || (root->type == TN_OR && !status))
		execute_btree_node(info, root->right);
}