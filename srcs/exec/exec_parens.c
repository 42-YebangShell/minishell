#include "../../includes/minishell.h"

int	exec_paren(t_tree_node *root)
{
	char	*cmd_line;

	cmd_line = rm_paren(root);
	set_excute(cmd_line);
}

char	*rm_paren(t_token *tk_parens)
{
	char	*result;
	char	*str_parens;

	str_parens = tk_parens->content;
	result = malloc(sizeof(char *) * (ft_strlen(str_parens)));
	if (!result)
		reutnr (NULL);
	ft_strlcpy(result, str_parens + 1, ft_strlen(str_parens) - 1);
	printf(result);
}