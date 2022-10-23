#include "../../includes/minishell.h"

void	exec_make_env_str(char *env[])
{
	int			i;
	char		*env;
	t_environ	*env_list;

	i = 0;
	env_list = g_var.env_list;
	while (env_list)
	{
		env = NULL;
		if (env_list->value)
		{
			add_str(env, env_list->key);
			add_str(env, "=");
			add_str(env, env_list->value);
			env[i++] = env;
		}
		env_list = env_list->next;
	}
}

char	**exec_env_str_list(void)
{
	int			i;
	t_environ	*env_list;
	char		**env;

	i = 0;
	env_list = g_var.env_list;
	while (env_list)
	{
		if (env_list->value)
			i++;
		env_list = env_list->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	if (env == NULL)
		exit(EXIT_FAILURE);
	exec_make_env_str(env);
	return (env);
}

char	**exec_token_str_list(t_token *token)
{
	int		len;
	t_token	*tmp;
	char **cmd_list;

	len = get_token_length(token);
	cmd_list = malloc(sizeof(char *) * (len + 1));
	cmd_list[len] = '\0';
	if (!cmd_list)
		exit(EXIT_FAILURE);
	tmp = token;
	while (tmp)
	{
		add_str(cmd_list, tmp->content);
		tmp = tmp->next;
	}
	return (cmd_list)
}

char	*exec_find_path(char *cmd, char *envp[])
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
