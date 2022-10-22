#include "../../includes/minishell.h"

void	show_tokens_data(t_token *tokens, char *str)
{
	t_token *tmp;

	if (!tokens)
		return;
	tmp = tokens;
	ft_putstr_fd("\033[0;33m", 1);
	ft_putstr_fd("token", 1);
	ft_putstr_fd("(", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(") : ", 1);
	ft_putstr_fd("\n", 1);
	while (tmp)
	{
		ft_putstr_fd("\033[0;33m", 1);
		ft_putstr_fd(tmp->content, 1);
		ft_putstr_fd("(", 1);
		ft_putnbr_fd(tmp->type, 1);
		ft_putstr_fd(")", 1);
		tmp = tmp->next;
	}
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\n\033[0;0m\x1b[1A\x1b[M", 1);
}

void	show_tree_data(t_tree_node *node, char *str)
{
	if (node)
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\nnode type : ", 1);
		ft_putnbr_fd(node->type, 1);
		ft_putstr_fd("\n", 1);
		show_tokens_data(node->tokens, "tokens");
		show_tokens_data(node->command, "command");
		//for echo cmd
		if (node->command && ft_strncmp(node->command->content, "echo", 5) == 0)
			ft_echo(node->command);
		show_tokens_data(node->redir, "redirection");
		show_tree_data(node->left, "left");
		show_tree_data(node->right, "right");
	}
}
/*-------------------------------------------------------------------------------------------------*/
void	set_excute(char *cmd_line)
{
	t_info	info;

	info.h_token = NULL;
	tokenizer(&(info.h_token), cmd_line);
	if (check_syntax_error(info.h_token))
	{
		info.r_node = create_btree_node(info.h_token);
		set_btree_node(&(info.r_node));
		execution(&info);
		free(cmd_line);
		// show_tree_data(info.r_node, "root");
	}
	else
		delete_token(info.h_token);
}

void execution(t_info *info)
{
	signal(SIGINT, &sig_exec);
	signal(SIGQUIT, &sig_exec);
	ft_display_ctrlx_set(DISPLAY);
	execute_btree_node(info, info->r_node);
	delete_node(info->r_node);
	info->r_node = NULL;
}

void	execute_btree_node(t_info *info, t_tree_node *root)
{
	if (root->type == TN_PARENS)
		exec_paren(info, root);
	else if (root->type == TN_AND || root->type == TN_OR)
		g_var.status = exec_and_or(info, root);
	else if (root->type == TN_PIPE)
		g_var.status = exec_pipe(info, root);
	else
	{
		if (!root->right)
			g_var.status = exec_single_word(info, root);
		else
			g_var.status = exec_word(info, root);
	}
}
