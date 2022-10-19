#include "../../includes/minishell.h"

void	print_token(t_token *token)
{
	while(token)
	{
		printf("[%s]\t", token->content);
		token = token->next;
	}
	printf("\n");
}
void tokenizer(char *cmd_line)
{
	int		i;
	int		q_flag;
	char	*line;
	t_info	info;

	i = 0;
	q_flag = 0;
	line = ft_strtrim(cmd_line, " ");
	info.h_token = NULL;
	while (line[i])
	{
		if (ft_strchr("\'\"", line[i]))
			add_token(&info.h_token, new_token(check_quote(&i, line)));
		// PARENS
		else if (ft_strchr("()", line[i]))
			add_token(&info.h_token, new_token(check_parens(&i, line)));
		else if (ft_strchr("|&", line[i]))
			add_token(&info.h_token, new_token(check_and_or_pipe(&i, line)));
		else if (ft_strchr("<>", line[i]))
			add_token(&info.h_token, new_token(check_redir(&i, line))); 
		else
			add_token(&info.h_token, new_token(check_cmd_or_option(&i, line)));
		if (i >= ft_strlen(line))
			break;
		if (line[i] == (char)' ')
			i++;
	}
	print_token(info.h_token);
	// return (tokens);
}

