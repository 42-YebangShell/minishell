#include "../../includes/minishell.h"

static void			add_env_node(char *key, char *value, t_environ **env_list);
static t_environ	*new_env_node(char *key, char *value);
static void			lstadd_env_node(t_environ **env_list, t_environ *new);
static t_environ	*last_env_node(t_environ *env_list);

t_environ	*get_envp_list(char **env)
{
	int			i;
	char		*key;
	char		*value;
	char		**tmp;
	t_environ	*env_list;

	i = 0;
	tmp = NULL;
	env_list = NULL;
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		key = tmp[0];
		value = tmp[1];
		add_env_node(key, value, &env_list);
		tmp = NULL;
		i++;
	}
	return (env_list);
}

static void	add_env_node(char *key, char *value, t_environ **env_list)
{
	t_environ	*new;

	new = new_env_node(key, value);
	if (!new)
	{
		printf("Error\n");
		exit(1);
	}
	lstadd_env_node(env_list, new);
}

static t_environ	*new_env_node(char *key, char *value)
{
	t_environ	*new_lst;

	new_lst = (t_environ *)malloc(sizeof(t_environ));
	if (!new_lst)
		return (NULL);
	new_lst->key = key;
	new_lst->value = value;
	new_lst->next = NULL;
	return (new_lst);
}

static void	lstadd_env_node(t_environ **env_list, t_environ *new)
{
	t_environ	*tmp;
	t_environ	*tmp2;

	tmp = NULL;
	if (env_list == NULL || new == NULL)
		return ;
	if (*env_list == NULL)
	{
		*env_list = new;
		return ;
	}
	tmp2 = *env_list;
	tmp = last_env_node(tmp2);
	tmp->next = new;
}

static t_environ	*last_env_node(t_environ *env_list)
{
	t_environ	*tmp;

	tmp = env_list;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
