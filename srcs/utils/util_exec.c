#include "../../includes/minishell.h"

int	check_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WCOREFLAG | WTERMSIG(status));
}

int	check_builtin(t_token *token)
{
	char	*cmd;

	cmd = token->content;
	if (!ft_strcmpi(cmd, "echo") || \
		!ft_strcmpi(cmd, "cd") || \
		!ft_strcmpi(cmd, "pwd") || \
		!ft_strcmpi(cmd, "export") || \
		!ft_strcmpi(cmd, "unset") || \
		!ft_strcmpi(cmd, "env") || \
		!ft_strcmpi(cmd, "exit"))
	return (EXIT_FAILURE);
}
