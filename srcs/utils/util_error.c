#include "../../includes/minishell.h"

void	ft_perror(char *str)
{
	printf("%s %s\n", str, strerror(errno));
}

int	check_syntax_error(t_token *token)
{
	if (token->type == AND || token->type == OR || token->type == PIPE)
	{
		printf("syntax error near unexpected token `%s`\n", token->content);
		return (0);
	}
	return (1);
}