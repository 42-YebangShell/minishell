#include "../../includes/minishell.h"
//printf하면 출력되는데 ft_putstr_fd하면 출력 안됨...
static int	check_option(char *content);
static void	put_quote(char *str, int fd);

int	ft_echo(t_token *command)
{
	int		option;
	t_token	*tmp;

	if (command == NULL)
		return (0);
	if (command->next)
		option = check_option(command->next->content);
	if (option)
		tmp = command->next->next;
	else
		tmp = command->next;
	while (tmp)
	{
		if (tmp->type != D_QUOTE || tmp->type != S_QUOTE)
			ft_putstr_fd(tmp->content, STDOUT_FILENO);
			// printf("%s", tmp->content);
		if (tmp->type == D_QUOTE || tmp->type == S_QUOTE)
			put_quote(tmp->content, STDOUT_FILENO);
		tmp = tmp->next;
	}
	if (!option)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

static int	check_option(char *content)
{
	if (ft_strncmp(content, "-n", 2) == 0)
		return (1);
	return (0);
}

static void	put_quote(char *str, int fd)
{
	if (str == NULL || fd < 0)
		return ;
	str++;
	while (*str)
	{
		write(fd, str, 1);
		str++;
	}
}
