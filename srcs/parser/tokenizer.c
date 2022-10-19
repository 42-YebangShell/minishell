#include "../../includes/minishell.h"

void tokenizer(t_token **tokens, char *cmd_line)
{
	int		i;
	char	*line;

	i = 0;
	line = ft_strtrim(cmd_line, " ");
	while (line[i])
	{
		if (ft_strchr("\'\"", line[i]))
			add_token(tokens, new_token(check_quote(&i, line)));
		// PARENS
		else if (ft_strchr("()", line[i]))
			add_token(tokens, new_token(check_parens(&i, line)));
		else if (ft_strchr("|&", line[i]))
			add_token(tokens, new_token(check_and_or_pipe(&i, line)));
		else if (ft_strchr("<>", line[i]))
			add_token(tokens, new_token(check_redir(&i, line))); 
		else
			add_token(tokens, new_token(check_cmd_or_option(&i, line)));
		if (i >= ft_strlen(line))
			break;
		if (line[i] == (char)' ')
			i++;
	}
	// print_token(info.h_token);
	// return (tokens);
}
