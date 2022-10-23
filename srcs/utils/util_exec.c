#include "../../includes/minishell.h"

char	*exec_rm_paren(t_token *tk_parens)
{
	char	*result;
	char	*str_parens;

	str_parens = tk_parens->content;
	result = malloc(sizeof(char *) * (ft_strlen(str_parens)));
	if (!result)
		reutnr (NULL);
	ft_strlcpy(result, str_parens + 1, ft_strlen(str_parens) - 1);
}