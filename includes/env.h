#ifndef ENV_H
# define ENV_H

t_environ	*get_envp_list(char **env);
t_environ	*get_env_node(char *key);

#endif