#include "../../includes/minishell.h"

int	str_len(char *str, char c, int i, int type)
{
	while (str[i])
	{
		if (type && ft_strchr("\'\"()|&<>", str[i]))
			return (i);
		if (str[i] == c)
			return (i);
		i++;
	}
	if (!type)
		return (0);
	return (i);
}

int	str_parens(char *str, int i)
{
	int	cnt;

	if (str[i] == (char)')')
		return (-1);
	i += 1;
	cnt = 1;
	while (cnt && str[i])
	{
		if (str[i] == (char)'(')
			cnt += 1;
		else if (str[i] == (char)')')
			cnt -= 1;
		i++;
	}
	if (cnt > 0)
		return (0);
	else if (cnt < 0)
		return (-1);
	return (i);
}