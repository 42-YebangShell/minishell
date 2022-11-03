#include "../../includes/minishell.h"

static char	*check_expand(char *str);
static void	expand_replace(char **buff, char *str, int *idx);
static char	*get_str_env(char *str, int *idx);
static	int	expand_key_len(char *str);

void	expand(t_token **h_token)
{
	t_token	*token;

	token = *h_token;
	while (token)
	{
		if (token->type >= CMD && token->type <= D_QUOTE)
			token->content = check_expand(token->content);
		token = token->next;
	}
}

static char	*check_expand(char *str)
{
	int		i;
	int		len;
	char	*buff;
	char	*env_value;

	i = 0;
	buff = NULL;
	while (str[i])
	{
		if (str[i] == '$')
			expand_replace(&buff, &str[i], &i);
		else
			add_char_buff(&buff, str[i]);
		i++;
	}
	return (buff);
}

static void	expand_replace(char **buff, char *str, int *idx)
{
	char	*value;

	if (str[1] && str[1] == '?')
	{
		*idx += 1;
		add_str_buff(buff, ft_itoa(g_var.status));
		return ;
	}
	if ((str[1] && str[1] == '$') || !str[1])
	{
		add_char_buff(buff, '$');
		return ;
	}
	value = get_str_env(str, idx);
	if (value)
		add_str_buff(buff, value);
}

static char	*get_str_env(char *str, int *idx)
{
	int			len;
	char		*env_key;
	t_environ	*env_list;
	t_environ	*env_node;

	len = expand_key_len(&str[1]);
	*idx += len;
	env_key = ft_substr(str, 1, len);
	env_node = get_env_node(env_key);
	if (!env_node)
		return (ft_strdup(""));
	return (ft_strdup(env_node->value));
}

static int	expand_key_len(char *str)
{
	int	i;

	// int		len;
	// char	*new_str;
	// int		j;
	// int		k;

	// len = 0;
	// len = ft_strlen(str);
	// // if (*str == '{')
	// // 	flag = 1;
	// // if (flag)
	// if (str[1] && str[1] == '{')
	// {
	// 	new_str = malloc(sizeof(char) * (len));
	// 	j = 0;
	// 	k = 1;
	// 	while (str[j])
	// 	{
	// 		new_str[j] = str[k];
	// 		i++;
	// 		j++;
	// 		if (str[j] == '}')
	// 			break ;
	// 	}
	// 	new_str[i] = '\0';
	// 	printf("what: %s\n", new_str);
	// 	*buff = ft_strjoin(*buff, new_str);
	// }
	// else

	i = 0;
	while (str[i] && str[i] != '$')
	{

		i++;
	}
	return (i);
}
