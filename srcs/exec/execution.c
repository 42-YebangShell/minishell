#include "../../includes/minishell.h"

int	exec_set(char *cmd_line)
{
	t_info	info;

	info.h_token = NULL;
	// replace_dollar
	tokenizer(&(info.h_token), cmd_line);
	if (check_syntax_error(info.h_token) == SUCCESS && \
		redir_here_doc_check(&info) == SUCCESS)
	{
		info.r_node = create_btree_node(info.h_token);
		set_btree_node(&(info.r_node));
		execution(&info);
		free(cmd_line);
		return (EXIT_SUCCESS);
	}
	else
	{
		delete_token(info.h_token);
		return (EXIT_FAILURE);
	}
}

void	execution(t_info *info)
{
	signal(SIGINT, &sig_exec);
	signal(SIGQUIT, &sig_exec);
	execute_btree_node(info, info->r_node);
	delete_node(info->r_node);
}

void	execute_btree_node(t_info *info, t_tree_node *root)
{
	if (!root)
		return ;
	if (root->type == TN_WORD && root->right == NULL)
		g_var.status = exec_single_word(info, root);
	else if (root->type == TN_PARENS)
		g_var.status = exec_parens(root);
	else if (root->type == TN_AND || root->type == TN_OR)
		exec_and_or(info, root);
	else if (root->type == TN_PIPE)
		g_var.status = exec_pipe(info, root);
	else
		g_var.status = exec_word(info, root);
}
