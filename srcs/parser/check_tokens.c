#include "../../includes/minishell.h"

t_token	*check_quote(int *i, char *line)
{
	int		len;
	int		type;
	t_token	*new;

	if (line[*i] == '\"')
		type = D_QUOTE;
	else if (line[*i] == '\'')
		type = S_QUOTE;
	len = str_len(line, line[*i], *i, NONE);
	if (!len)
	{
		type = NONE;
		len = ft_strlen(line);
	}
	new = new_token(ft_substr(line, *i, len - *i), type);
	*i = len;
	return (new);
}

t_token	*check_parens(int *i, char *line)
{
	int		len;
	int		type;
	t_token	*new;

	type = PARENS;
	len = str_parens(line, *i);
	if (!len)
	{
		type = NONE;
		len = ft_strlen(line);
	}
	new = new_token(ft_substr(line, *i, len - *i), type);
	*i = len;
	return (new);
}

t_token	*check_and_or_pipe(int *i, char *line)
{
	int		len;
	int		type;
	char	*tmp;
	t_token	*new;

	len = 2;
	if (line[*i + 1] && line[*i] == '|' && line[*i + 1] == '|')
		type = OR;
	else if (line[*i] == '|')
	{
		len = 1;
		type = PIPE;
	}
	else if (line[*i + 1] && line[*i] == '&' && line[*i+1] == '&')
		type = AND;	
	new = new_token(ft_substr(line, *i, len), type);
	*i += len;
	return (new);
}

t_token	*check_redir(int *i, char *line)
{
	int		len;
	int		type;
	t_token	*new;

	len = 2;
	if (line[*i + 1] && line[*i] == '<' && line[*i + 1] == '<')
		type = HERE_DOC;
	else if (line[*i + 1] && line[*i] == '>' && line[*i + 1] == '>')
		type = APP_RDIR;
	len = 1;
	if (line[*i] == '<')
		type = INP_RDIR;
	else if (line[*i] == '>')
		type = OUT_RDIR;
	new = new_token(ft_substr(line, *i, len), type);
	*i += len;
	return (new);
}

t_token	*check_cmd_or_option(int *i, char *line)
{
	int		idx;
	int		len;
	int		type;
	t_token	*new;

	idx = 0;
	type = CMD;
	// 특수문자 체크 함수 호출

	if (line[idx] == '-')
		type = OPTION;
	len = str_len(line, (char)' ', *i, CMD);
	new = new_token(ft_substr(line, *i, len - *i), type);
	*i = len;
	return (new);
}