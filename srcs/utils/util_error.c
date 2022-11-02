#include "../../includes/minishell.h"

void	error_exit(char *str)
{
	ft_putstr_fd("minish: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	// exit(g_var.status);
}

void	ft_perror(char *err_msg1, char *err_msg2)
{
	ft_putstr_fd("minish: ", STDERR_FILENO);
	ft_putstr_fd(err_msg1, STDERR_FILENO);
	ft_putendl_fd(err_msg2, STDERR_FILENO);
	// exit(g_var.status);
}

int	check_syntax_error(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == AND || token->type == OR || token->type == PIPE)
	{
		ft_perror("syntax error near unexpected token ", token->content);
		return (FALSE);
	}
	return (SUCCESS);
}
