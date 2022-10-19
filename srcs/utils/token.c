#include "../../includes/minishell.h"

t_token	*new_token(t_token token)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = token.type;
	new->content = token.content;
	return (new);
}

void	add_token(t_token **token_list, t_token *new)
{
	t_token	*last;

	if (!token_list || !new)
		return ;
	if (!*token_list)
	{
		*token_list = new;
		return ;
	}
	last = get_last_token(*token_list);
	last->next = new;
}

t_token	*get_last_token(t_token *tokens)
{
	while (tokens)
	{
		if (!tokens->next)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

void	*delete_token(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = next;
	}
	return (NULL);
}
