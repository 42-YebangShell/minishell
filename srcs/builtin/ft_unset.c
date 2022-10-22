#include "../../includes/minishell.h"

// static void	set_env_var(t_token *key_val);
static void			add_env_node(char *key, char *value, t_environ **env_list);
static t_environ	*new_env_node(char *key, char *value);
static void			lstaibangdd_env_node(t_environ **env_list, t_environ *new);
static t_environ	*last_env_node(t_environ *env_list);
static void	lstadd_env_node(t_environ **env_list, t_environ *new);
static int	already_exist(char *key);
static void	update_env_var(char *key, char *val);

int	ft_unset(t_token *command)
{
	t_token	*tmp;
	char	*key;
	char	*val;
	int		flag;
	int		i;

	if (command == NULL || command->next == NULL)
		return (0);
	tmp = command->next;
	while (tmp)
	{

		if (already_exist(key))
			update_env_var(key, val);
		else
			add_env_node(key, val, &g_var.env_list);
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

static void	update_env_var(char *key, char *val)
{
	t_environ	*tmp;

	tmp = g_var.env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
		{
			free(tmp->value);
			tmp->value = val;
		}
		tmp = tmp->next;
	}
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

