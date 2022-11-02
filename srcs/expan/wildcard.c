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
		printf("tmp content :: :: %s\n", tmp->content);
		if (is_aster_token(*tmp))
		{
			get_expans_list(tmp, &expan_tokens);
			// show_token_list(expan_tokens);
			token_replace(tokens_list, tmp, expan_tokens);
		}
		tmp = tmp->next;
	}

}




static void	get_expans_list(t_token *token, t_token **expan_token)
{
	struct dirent	*dirent;
	DIR				*dir;
	// t_token			*replace_tokens;
	t_token			*new;
	t_token			input;
	char			*prefix;
	char			*suffix;
	int				pos;


	printf("before pre/suffix ::::: %s\n", token->content);
	prefix = get_prefix(token->content);
	suffix = get_suffix(token->content);
	printf("   prefix :: %s \n   suffix :: %s \n", prefix, suffix);///
	dir = opendir(".");
	while (1)
	{
		dirent = readdir(dir);
		if (!dirent)
			break ;
		else
		{
			if (!prefix && !suffix)
				continue ;
			else if (prefix && !suffix)
			{
				if (ft_strncmp(dirent->d_name, prefix, ft_strlen(prefix)) == 0)
				{
					input.content = ft_strdup(dirent->d_name);
					input.type = token->type;
					printf("1.input :: %s\n", input.content); ////
					new = new_token(input);
					printf("new :: %s\n", new->content); ///
					if (new->content)
						add_token(expan_token, new);
					// show_token_list(*expan_token);
				}
			}
			else if (!prefix && suffix)
			{
				pos = ft_strlen(dirent->d_name) - ft_strlen(suffix);
				if (pos < 0)
					continue ;
				if (strncmp(dirent->d_name + pos, suffix, ft_strlen(suffix)) == 0)
				{
					input.content = ft_strdup(dirent->d_name);
					input.type = token->type;
					printf("2. input :: %s\n", input.content); ////
					new = new_token(input);
					printf("new :: %s\n", new->content); ///
					if (new->content)
						add_token(expan_token, new);
					// show_token_list(*expan_token);
				}
			}
			else if (prefix && suffix)
			{
				if (ft_strncmp(dirent->d_name, prefix, ft_strlen(prefix)) == 0)
				{
					pos = ft_strlen(dirent->d_name) - ft_strlen(suffix);
					if (pos < 0)
						continue;
					if (strncmp(dirent->d_name + pos, suffix, ft_strlen(suffix)) == 0)
					{
						input.content = ft_strdup(dirent->d_name);
						input.type = token->type;
						printf("3. input :: %s\n", input.content);////
						new = new_token(input);
						printf("new :: %s\n", new->content); ///
						if (new->content)
							add_token(expan_token, new);
						// show_token_list(*expan_token);
					}
				}
			}
		}
	}
	printf("\n\n");
	// show_token_list(*expan_token);
	closedir(dir);
	// show_token_list(*expan_token); //왜 클로즈한다음에는 에러나지..? 이유는 dirent->d_name을 dup 안하고 그대로 썼기 때문
}
