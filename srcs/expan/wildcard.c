#include "../../includes/minishell.h"

static void	get_expans_list(t_token *token, t_token **expan_token);
static int case_zero(char *d_name, t_token *token, t_token **expan_token);
static int case_one(char *d_name, char *prefix, t_token *token, t_token **expan_token);
static int	case_two(char *d_name, char *suffix, t_token *token, t_token **expan_token);
static int case_three(char *d_name, char *prefix, char *suffix, t_token *token, t_token **expan_token);

void	aster_replace(t_token **tokens_list)
{
	t_token	*tmp;
	t_token *itr;
	t_token			*expan_tokens;

	tmp = *tokens_list;
	expan_tokens = NULL;
	while (tmp)
	{
		// printf("tmp content :: :: %s\n", tmp->content);
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
	t_token			*new;
	t_token			input;
	char			*prefix;
	char			*suffix;
	int				pos;
	int				res;

	res = 0;
	prefix = get_prefix(token->content);
	suffix = get_suffix(token->content);
	dir = opendir(".");
	while (1)
	{
		dirent = readdir(dir);
		if (!dirent)
			break ;
		else
		{
			if (!prefix && !suffix)
				case_zero(dirent->d_name, token, expan_token);
				// continue ;
			else if (prefix && !suffix)
			{
				case_one(dirent->d_name, prefix, token, expan_token);
				// if (ft_strncmp(dirent->d_name, prefix, ft_strlen(prefix)) == 0)
				// {
				// 	input.content = ft_strdup(dirent->d_name);
				// 	input.type = token->type;
				// 	new = new_token(input);
				// 	if (new->content)
				// 		add_token(expan_token, new);
				// }
			}
			else if (!prefix && suffix)
			{
				res = case_two(dirent->d_name, suffix, token, expan_token);
				if (res == -1)
					continue ;

				// pos = ft_strlen(dirent->d_name) - ft_strlen(suffix);
				// if (pos < 0)
				// 	continue ;
				// if (strncmp(dirent->d_name + pos, suffix, ft_strlen(suffix)) == 0)
				// {
				// 	input.content = ft_strdup(dirent->d_name);
				// 	input.type = token->type;
				// 	new = new_token(input);
				// 	if (new->content)
				// 		add_token(expan_token, new);
				// }
			}
			else if (prefix && suffix)
			{
				res = case_three(dirent->d_name, prefix, suffix, token, expan_token);
				if (res == -1)
					continue;
				// if (ft_strncmp(dirent->d_name, prefix, ft_strlen(prefix)) == 0)
				// {
				// 	pos = ft_strlen(dirent->d_name) - ft_strlen(suffix);
				// 	if (pos < 0)
				// 		continue;
				// 	if (strncmp(dirent->d_name + pos, suffix, ft_strlen(suffix)) == 0)
				// 	{
				// 		input.content = ft_strdup(dirent->d_name);
				// 		input.type = token->type;
				// 		new = new_token(input);
				// 		if (new->content)
				// 			add_token(expan_token, new);
				// 	}
				// }
			}
		}
	}
	// printf("\n\n");
	closedir(dir);
}

static int case_zero(char *d_name, t_token *token, t_token **expan_token)
{
		int		pos;
		t_token *new;
		t_token input;
		int res;

		input.content = ft_strdup(d_name);
		input.type = token->type;
		new = new_token(input);
		if (new->content)
			add_token(expan_token, new);
		return (res);

}

static int case_one(char *d_name, char *prefix, t_token *token, t_token **expan_token)
{
	int		pos;
	t_token *new;
	t_token	input;
	int		res;

	res = 0;
	if (ft_strncmp(d_name, prefix, ft_strlen(prefix)) == 0)
	{
		input.content = ft_strdup(d_name);
		input.type = token->type;
		new = new_token(input);
		if (new->content)
			add_token(expan_token, new);
	}
	return (res);
}

static int	case_two(char *d_name, char *suffix, t_token *token, t_token **expan_token)
{
	int		pos;
	t_token *new;
	t_token	input;
	int		res;

	res = 0;
	pos = ft_strlen(d_name) - ft_strlen(suffix);
	if (pos < 0)
		res = -1;
	if (strncmp(d_name + pos, suffix, ft_strlen(suffix)) == 0)
	{
		input.content = ft_strdup(d_name);
		input.type = token->type;
		new = new_token(input);
		if (new->content)
			add_token(expan_token, new);
	}
	return (res);
}

static int case_three(char *d_name, char *prefix, char *suffix, t_token *token, t_token **expan_token)
{
	int		pos;
	t_token *new;
	t_token	input;
	int		res;

	res = 0;
	if (ft_strncmp(d_name, prefix, ft_strlen(prefix)) == 0)
	{
		pos = ft_strlen(d_name) - ft_strlen(suffix);
		if (pos < 0)
			res = -1;
		if (strncmp(d_name + pos, suffix, ft_strlen(suffix)) == 0)
		{
			input.content = ft_strdup(d_name);
			input.type = token->type;
			new = new_token(input);
			if (new->content)
				add_token(expan_token, new);
		}
	}
	return (res);
}
