#include "../../includes/minishell.h"

static void	pass_space(int *idx, char *line);

void	tokenizer(t_token **tokens, char *cmd_line)
{
	int		i;
	char	*line;

	i = 0;
	line = ft_strtrim(cmd_line, " 	");
	while (line[i])
	{
		if (ft_strchr("\'\"", line[i]))
			add_token(tokens, check_quote(&i, line));
		else if (ft_strchr("()", line[i]))
			add_token(tokens, check_parens(&i, line));
		else if (ft_strchr("|&", line[i]))
			add_token(tokens, check_and_or_pipe(&i, line));
		else if (ft_strchr("<>", line[i]))
			add_token(tokens, check_redir(&i, line));
		else
			add_token(tokens, check_cmd_or_option(&i, line));
		pass_space(&i, line);
		if (!*tokens)
			break ;
		if (i > (int)ft_strlen(line))
			break ;
	}
}

static void	pass_space(int *idx, char *line)
{
	int		i;

	i = *idx;
	while (line[i])
	{
		if (line[i] != ' ' || line[i] != '	')
			break ;
		i++;
	}
	*idx = i;
}
