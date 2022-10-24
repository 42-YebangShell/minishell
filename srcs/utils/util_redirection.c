#include "../../includes/minishell.h"

int	redir_check_here_doc(t_info *info)
{
	t_token	*token;

	signal(SIGINT, &sig_here_doc);
	token = info->h_token;
	while (token)
	{
		if (token->type == HERE_DOC)
			if (!redir_here_doc(token->next->content))
				return (FALSE);
		token = token->next;
	}
	return (TRUE);
}
