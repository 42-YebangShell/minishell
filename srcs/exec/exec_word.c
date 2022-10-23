#include "../../includes/minishell.h"

int	exec_single_word(t_info *info, t_tree_node *root)
{
	int	fd[2];
	int r_status;

	r_status = 0;
	if (root->redir)
	{
		fd[READ_END] = dup(STDIN_FILENO);
		fd[WRITE_END] = dup(STDOUT_FILENO);
		if (fd[READ_END] == -1 || fd[WRITE_END] == -1)
			exit(EXIT_FAILURE); 
		r_status = apply_redirection(info, root);
	}
	if (r_status)
	{
		rd_fd[0] = dup(STDIN_FILENO);
		rd_fd[1] = dup(STDOUT_FILENO);
		close(rd_fd[0]);
		close(rd_fd[1]);
		dup2(io_fd[0], STDIN_FILENO);
		close(io_fd[0]);
		dup2(io_fd[1], STDOUT_FILENO);
		close(io_fd[1]);
	}
}
void	execute_single_cmdline(void)
{
	t_process	*process;

	process = g_minishell_info.ps_list;
	if (apply_redirections(process->cmd_line) == FAILURE)
		return (set_last_status(EXIT_FAILURE));
	if (is_argv_null(process->argv))
		return ;
	if (is_built_in(process))
		return (set_last_status(execute_built_in(process)));
	g_minishell_info.ps_list->pid = fork();
	if (g_minishell_info.ps_list->pid == -1)
		error_exit("fork error");
	else if (g_minishell_info.ps_list->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execute_command(process);
	}
	else
		return (set_last_status(wait_childs()));
}
int exec_word(t_info *info, t_tree_node *root)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, &sig_exec);
	signal(SIGQUIT, &sig_exec);
	if (check_builtin(root))
		return (builtin(info, root));
	else
	{
		pid = fork();
		if (pid == -1)
			exit(0);
		else
		{
			status = exec_cmd_child(info, root);
			exit(status);
		}
		waitpid(pid, &g_var.status, 0);
		return (check_status(g_var.status));
	}
}

int	exec_cmd_child(t_info *info, t_tree_node *root)
{
	char	*cmd;
	char	**path;
	int		r_status;

	r_status = apply_redirections(info, root);
	if (r_status)
		return (r_status);
	if (!root)
		return (EXIT_SUCCESS);
	cmd = root->command->content;
	path = exec_find_path(g_var.env_list, "PATH");
	if (path)
		exec_env_path()
}

char	**exec_find_path(t_environ *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->key, key, -1) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}
char	**exec_env_path(t_token *token)
{
	int		i;
	char	*cmd;
	char	**env;

	cmd = token->content;
	env = exec_env_str();
	while ()
	{

	}
}

char **exec_env_str(void)
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