#include "../../includes/minishell.h"

static t_token	*check_root_node(t_token *tokens);
static void	cut_btree_node(t_token	*token, t_token *root);
static void set_btree_word(t_tree_node **node);

void	set_btree_node(t_tree_node **node)
{
	t_token	*root;
	
	if (*node && !((*node)->type))
	{
		root = check_root_node((*node)->tokens);
		if (root)
		{
			(*node)->type = tree_node_type(root->type);
			cut_btree_node((*node)->tokens, root);
			(*node)->left = create_btree_node((*node)->tokens);
			(*node)->tokens = NULL;
			(*node)->right = create_btree_node(root->next);
			free(root->content);
			free(root);
			set_btree_node(&((*node)->left));
			set_btree_node(&((*node)->right));
		}
		else
			set_btree_word(node);
	}
	
}

static t_token	*check_root_node(t_token *tokens)
{
	t_token	*root_and_or;
	t_token *root_pipe;

	root_and_or = tokens;
	root_pipe = NULL;
	while(root_and_or)
	{
		if (root_and_or->type == AND || root_and_or->type == OR)
			return (root_and_or);
		if (!root_pipe && root_and_or->type == PIPE)
			root_pipe = root_and_or;
		root_and_or = root_and_or->next;
	}
	return (root_pipe);
}

static void	cut_btree_node(t_token	*token, t_token *root)
{
	if (!token || !root)
		return ;
	while (token->next)
	{
		if (token->next == root)
			break ;
		token = token->next;
	}
	token->next = NULL;
}

static void set_btree_word(t_tree_node **node)
{
	t_token	*token;
	
	// (*node)->type = tree_node_type(root->type);
	// token = (*node)->tokens;
	// if (token->type == NONE)
	// 	// error 
	// // redir
	// if (token->type >= 8 11 )
	// // 
	// if (token->type == HERE_DOC )
}
