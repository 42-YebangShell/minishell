#include "../../includes/minishell.h"

static int	already_exist(char *key);
static void	delete_env_node(t_environ **env_list, char *key);

int	ft_unset(t_token *command)
{
	t_token	*tmp;
	char	*key;
	int		flag;
	int		i;

	if (command == NULL || command->next == NULL)
		return (0);
	tmp = command->next;
	while (tmp)
	{
		key = tmp->content;
		if (already_exist(key))
		{
			delete_env_node(&g_var.env_list, key);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	already_exist(char *key)
{
	t_environ	*tmp;
	int			res;

	tmp = g_var.env_list;
	res = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
			res = 1;
		tmp = tmp->next;
	}
	return (res);
}

static void	delete_env_node(t_environ **env_list, char *key)
{
	t_environ	*tmp;
	t_environ	*tmp2;
	t_environ	*target;

	tmp = *env_list;
	if (env_list == NULL || target == NULL)
		return ;
	target = get_env_node(key);
	while (tmp->next != target)
	{
		tmp = tmp->next;
	}
	target = tmp->next;
	tmp->next = tmp->next->next;
	free(target->key);
	free(target->value);
	free(target);
}

static int	is_inside_bad(char *key)
{
	if (ft_strchr(key, '{') || ft_strchr(key, '}'))
		return (1);
	return (0);
}

t_environ	*get_env_node(char *key)
{
	t_environ	*tmp;
	char		*new_key;
	int			i;
	int			len;

	len = 0;
	len = ft_strlen(key);
	if (key[0] == '{' && key[len - 1] == '}')
	{

		new_key = malloc(sizeof(char) * len - 2 + 1);
		ft_strlcpy(new_key, key + 1, len - 1);
		key = new_key;
		if (is_inside_bad(key))
		{
			ft_putstr_fd("bad substitution", STDERR_FILENO);
			return (NULL);
		}
	}

	tmp = g_var.env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
