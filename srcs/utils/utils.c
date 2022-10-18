#include "../../includes/minishell.h"

int	str_len(char *str, char c, int i, int type)
{
	while (str[i])
	{
		i++;
		if (type && ft_strchr("\'\"()|&<>", str[i]))
			return (i - 1);
		
		if (str[i] == c)
			return (i);
	}
	return (0);
}

int	str_parens(char *str, int i)
{
	int	cnt;

	cnt = 1;
	if (str[i] == (char)')')
		return (0);
	while (cnt && str[i])
	{
		i++;
		if (str[i] == (char)'(')
			cnt += 1;
		else if (str[i] == (char)')')
			cnt -= 1;
	}
	if (cnt)
		return (0);
	return (i);
}