#include "../../includes/minishell.h"

static int	tree_node_type(int type);

void	set_b_tree(t_tree_node	*node)
{
	t_token	*parent;
	t_token	*left_child;
	t_token	*right_child;

	if (!node)
		return ;
	parent = NULL;
	left_child = NULL;
	right_child = NULL;
	parent = is_and_or_pipe(node->tokens);
	if (!parent)
		return ;
	if (parent && (parent->type == AND || parent->type == OR || parent->type == PIPE))
	{
		node->type = node_type(parent->type);
		insert_node(&node->tokens, parent);
		left_child = node->tokens;
		node->left = create_tree_node(left_child);
		right_child = parent->next;
		node->right = create_tree_node(right_child);

		parent->next = NULL;
		node->tokens = parent;

		parsing(node->left);
		parsing(node->right);
	}
}

void	*create_tree_node(t_token *tokens)
{
	int			type;
	t_tree_node	*node;

	node = (t_tree_node *)ft_calloc(1, sizeof(t_tree_node));
	node->tokens = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = tree_node_type(tokens->type);
	node->tokens = tokens;
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

void	delete_node(t_tree_node *node)
{
	if (node)
	{
		delete_node(node->left);
		delete_node(node->right);
		delete_token(node->tokens);
		delete_token(node->redir);
		delete_token(node->command);
		free(node);
		node = NULL;
	}
}

static int	tree_node_type(int type)
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