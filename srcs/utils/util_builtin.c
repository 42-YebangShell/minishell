#include "../../includes/minishell.h"

int	run_builtin(t_info *info, t_tree_node *root)
{
	char	*cmd;

	cmd = root->command;
	if (!ft_strncmp(cmd, "echo", -1) || \
		!ft_strncmp(cmd, "ECHO", -1))
		return (ft_echo(root->command));
	if (!ft_strncmp(cmd, "cd", -1) || \
		!ft_strncmp(cmd, "CD", -1))
		return (ft_cd(root->command));
	if (!ft_strncmp(cmd, "pwd", -1) || \
		!ft_strncmp(cmd, "PWD", -1))
		return (ft_pwd(root->command));
	if (!ft_strncmp(cmd, "export", -1) || \
		!ft_strncmp(cmd, "EXPORT", -1))
		return (ft_export(root->command));
	if (!ft_strncmp(cmd, "unset", -1) || \
		!ft_strncmp(cmd, "UNSET", -1))
		return (ft_unset(root->command));
	if (!ft_strncmp(cmd, "env", -1) || \
		!ft_strncmp(cmd, "ENV", -1))
		return (ft_env(root->command));
	if (!ft_strncmp(cmd, "exit", -1) || \
		!ft_strncmp(cmd, "EXIT", -1))
		return (ft_exit(root->command));
	return (EXIT_FAILURE);
}