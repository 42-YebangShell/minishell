#include "../../includes/minishell.h"

int	tree_node_type(int type)
{
	if (type == OR)
		return (TK_OR);
	else if (type == AND)
		return (TK_AND);
	else if (type == PIPE)
		return (TK_PIPE);
	else if (type == PARENS)
		return (TK_PARENS);
	else
		return (TK_WORD);
}

t_tree_node	*create_tree_node(t_token *tokens)
{
	int			type;
	t_tree_node	*node;

	node = ft_calloc(1, sizeof(t_tree_node));
	node->tokens = ft_calloc(1, sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = tree_node_type(tokens->type);
	node->tokens = tokens;
	return (node);
}

void	insert_node(t_token *token, t_token *root)
{
	if (!token || root)
		return ;
	while (token->next)
	{
		if (token->next == root)
			break;
		token = token->next;
	}
	token->next = NULL;
}

void	del_node(t_tree_node *node)
{
	if (node)
	{
		del_node(node->left);
		del_node(node->right);
		del_token(node->tokens);
		del_token(node->redir);
		del_token(node->words);
		free(node);
		node = NULL;
	}
}