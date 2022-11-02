#include "../../includes/minishell.h"

static void	get_expans_list(t_token *token, t_token **expan_token);

void	aster_replace(t_token **tokens_list)
{
	t_token	*tmp;
	t_token *itr;
	t_token			*expan_tokens;

	tmp = *tokens_list;
	expan_tokens = NULL;
	while (tmp)
	{
		if (is_aster_token(*tmp))
		{
			get_expans_list(tmp, &expan_tokens);
			token_replace(tokens_list, tmp, expan_tokens);
		}
		tmp = tmp->next;
	}

}

static void	get_expans_list(t_token *token, t_token **expan_token)
{
	struct dirent	*dirent;
	DIR				*dir;
	char			*prefix;
	char			*suffix;

	prefix = get_prefix(token->content);
	suffix = get_suffix(token->content);
	dir = opendir(".");
	while (1)
	{
		dirent = readdir(dir);
		if (!dirent)
			break;
		if (!prefix && !suffix)
			case_zero(dirent->d_name, token, expan_token);
		else if (prefix && !suffix)
			case_one(dirent->d_name, prefix, token, expan_token);
		else if (!prefix && suffix)
			case_two(dirent->d_name, suffix, token, expan_token);
		else if (prefix && suffix)
			case_three(dirent->d_name, prefix, suffix, token, expan_token);
	}
	closedir(dir);
}
