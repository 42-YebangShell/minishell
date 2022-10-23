#include "../../includes/minishell.h"

char	*exec_rm_char(t_token *token)
{
	char	*result;
	char	*content;

	content = token->content;
	result = malloc(sizeof(char) * (ft_strlen(content) + 2));
	if (!result)
		return (NULL);
	ft_strlcpy(result, content + 1, ft_strlen(content) - 1);
	return (result);
}