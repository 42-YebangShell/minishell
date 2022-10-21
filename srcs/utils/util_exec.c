#include "../../includes/minishell.h"

int	check_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WCOREFLAG | WTERMSIG(status));
}

int	check_builtin(t_token *token)
{
	if (!ft_strncmp(token->content, "echo", -1) || \
		!ft_strncmp(token->content, "ECHO", -1) || \
		!ft_strncmp(token->content, "cd", -1) || \
		!ft_strncmp(token->content, "CD", -1) || \
		!ft_strncmp(token->content, "pwd", -1) || \
		!ft_strncmp(token->content, "PWD", -1) || \
		!ft_strncmp(token->content, "export", -1) || \
		!ft_strncmp(token->content, "EXPORT", -1) || \
		!ft_strncmp(token->content, "unset", -1) ||	 \
		!ft_strncmp(token->content, "UNSET", -1) || \
		!ft_strncmp(token->content, "env", -1) || \
		!ft_strncmp(token->content, "ENV", -1) || \
		!ft_strncmp(token->content, "exit", -1) || \
		!ft_strncmp(token->content, "EXIT", -1))
		return (TRUE);
	return (FALSE);
}