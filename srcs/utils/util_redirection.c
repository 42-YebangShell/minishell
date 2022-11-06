#include "../../includes/minishell.h"

int	redir_here_doc_check(t_info *info)
{
	int		status;
	t_token	*here_doc;

	status = SUCCESS;
	here_doc = info->h_token;
	g_var.hd_cnt = 0;
	while (here_doc)
	{
		if (here_doc->type == AND || here_doc->type == OR \
			|| here_doc->type == PIPE)
			g_var.hd_cnt++;
		if (here_doc->type == HERE_DOC)
			status = redir_here_doc_file(here_doc);
		here_doc = here_doc->next;
	}
	return (status);
}

int	redir_here_doc_file_number(t_info *info, t_token *token)
{
	int		cnt;
	t_token	*here_doc;

	cnt = 0;
	here_doc = info->h_token;
	while (here_doc)
	{
		if (here_doc->type == AND || here_doc->type == OR \
			|| here_doc->type == PIPE)
			cnt++;
		if (here_doc == token)
			return (cnt);
		here_doc = here_doc->next;
	}
	return (0);
}
