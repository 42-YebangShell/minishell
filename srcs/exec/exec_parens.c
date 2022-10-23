#include "../../includes/minishell.h"

static char	*exec_rm_paren(t_token *tk_parens);

void	exec_paren(t_tree_node *root)
{
	char	*cmd_line;

	cmd_line = rm_paren(root->tokens);
	if (cmd_line)
		set_excute(cmd_line);
}

static char	*exec_rm_paren(t_token *tk_parens)
{
	char	*result;
	char	*str_parens;

	str_parens = tk_parens->content;
	result = malloc(sizeof(char) * (ft_strlen(str_parens) + 2));
	if (!result)
		reutnr (NULL);
	ft_strlcpy(result, str_parens + 1, ft_strlen(str_parens) - 1);
}