#include "../../includes/minishell.h"

t_token	check_quote(int *i, char *line)
{
	int		len;
	t_token	new;

	if (line[*i] == '\"')
		new.type = D_QUOTE;
	else if (line[*i] == '\'')
		new.type = S_QUOTE;
	len = str_len(line, line[*i], *i+1, NONE);
	if (!len)
	{
		new.type = NONE;
		len = ft_strlen(line);
	}
	new.content = ft_substr(line, *i, len - *i + 1);
	*i = len + 1;
	return (new);
}

t_token	check_parens(int *i, char *line)
{
	int		len;
	t_token	new;

	new.type = PARENS;
	len = str_parens(line, *i);
	if (!len)
	{
		new.type = NONE;
		len = ft_strlen(line);
	}
	new.content = ft_substr(line, *i, len - *i);
	*i = len;
	return (new);
}

t_token	check_and_or_pipe(int *i, char *line)
{
	int		len;
	t_token	new;

	len = 2;
	if (line[*i + 1] && line[*i] == '|' && line[*i + 1] == '|')
		new.type = OR;
	else if (line[*i] == '|')
	{
		len = 1;
		new.type = PIPE;
	}
	else if (line[*i + 1] && line[*i] == '&' && line[*i+1] == '&')
		new.type = AND;	
	new.content = ft_substr(line, *i, len);
	*i += len;
	return (new);
}

t_token	check_redir(int *i, char *line)
{
	int		len;
	t_token	new;

	len = 2;
	if (line[*i + 1] && line[*i] == '<' && line[*i + 1] == '<')
		new.type = HERE_DOC;
	else if (line[*i + 1] && line[*i] == '>' && line[*i + 1] == '>')
		new.type = APP_RDIR;
	else
	{
		len = 1;
		if (line[*i] == '<')
			new.type = INP_RDIR;
		else if (line[*i] == '>')
			new.type = OUT_RDIR;
	}
	new.content = ft_substr(line, *i, len);
	*i += len;
	return (new);
}

t_token	check_cmd_or_option(int *i, char *line)
{
	int		idx;
	int		len;
	int		type;
	t_token	new;

	idx = 0;
	new.type = CMD;
	if (line[idx] == '-')
		new.type = OPTION;
	len = str_len(line, (char)' ', *i, CMD);
	new.content = ft_substr(line, *i, len - *i);
	*i = len;
	return (new);
}