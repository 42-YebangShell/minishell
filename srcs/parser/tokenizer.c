#include "../../includes/minishell.h"

void	print_token(t_token *token)
{
	while(token)
	{
		printf("%s\t", token->contents);
		token = token->next;
	}
}
void tokenizer(char *cmd_line)
{
	int		i;
	int		q_flag;
	char	*line;
	t_token	*tokens;

	i = 0;
	q_flag = 0;
	line = ft_strtrim(cmd_line, " ");
	while (line[i])
	{
		if (ft_strchr("\'\"", line[i]))
			add_token(tokens, check_quote(&i, line));
		// PARENS
		else if (ft_strchr("()", line[i]))
			add_token(tokens, check_parens(&i, line));
		// OR, AND, PIPE,
		else if (ft_strchr("|&", line[i]))
			add_token(tokens, check_and_or_pipe(&i, line));
		// INP_RDIR, OUT_RDIR, APP_RDIR, HERE_DOC,
		else if (ft_strchr("<>", line[i]))
			add_token(tokens, check_redir(&i, line)); 
		// CMD, OPTION
		else
			add_token(tokens, check_cmd_or_option(&i, line));
		i++;
		printf("%c", line[i]);
	}
	print_token(tokens);
	// return (tokens);
}

