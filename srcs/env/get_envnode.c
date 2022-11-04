#include "../../includes/minishell.h"

static int	is_inside_bad(char *key);

t_environ	*get_env_node(char *key)
{
	t_environ	*tmp;
	char		*new_key;
	int			len;

	len = 0;
	len = ft_strlen(key);
	if (key[0] == '}')
	{
		ft_putstr_fd("bad substitution", STDERR_FILENO);
		return (NULL);
	}
	if (key[0] == '{')
	{
		if (key[len - 1] == '}')
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
		else
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

static int	is_inside_bad(char *key)
{
	if (ft_strchr(key, '{') || ft_strchr(key, '}'))
		return (1);
	return (0);
}
