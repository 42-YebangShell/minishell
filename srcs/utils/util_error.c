#include "../../includes/minishell.h"

void	ft_perror(char *err_msg1, char *err_msg2)
{
	ft_putstr_fd("minish: ", STDOUT_FILENO);
	ft_putstr_fd(err_msg1, STDOUT_FILENO);
	ft_putstr_fd(err_msg2, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	// ft_putstr_fd(strerror(errno), STDOUT_FILENO);
}

int	check_syntax_error(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == AND || token->type == OR || token->type == PIPE)
	{
		ft_perror("syntax error near unexpected token", token->content);
		return (0);
	}
	return (1);
}