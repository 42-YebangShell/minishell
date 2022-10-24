#include "../../includes/minishell.h"

int	redir_check_here_doc(t_info *info)
{
	int		status;
	t_token	*here_doc;

	status = SUCCESS;
	here_doc = info->h_token;
	while (here_doc)
	{
		if (here_doc->type == AND || here_doc->type == OR || here_doc->type == PIPE)
			g_var.hd_cnt++;
		if (here_doc->type == HERE_DOC)
		{
			status = redir_here_doc(here_doc);
		}
		here_doc = here_doc->next;
	}
	return (status);
}