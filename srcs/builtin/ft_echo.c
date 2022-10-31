#include "../../includes/minishell.h"

static int	check_option(char *content);
static void	put_quote(char *str, int fd);

int	ft_echo(t_token *command)
{
	int		option;
	t_token	*tmp;

	if (command == NULL || command->next == NULL)
		return (0);
	if (command->next)
		option = check_option(command->next->content);
	if (option)
		tmp = command->next->next;
	else
		tmp = command->next;
	while (tmp)
	{
		if (tmp->type == D_QUOTE || tmp->type == S_QUOTE)
		{
			put_quote(tmp->content, STDOUT_FILENO);
			ft_putstr_fd(" ", STDOUT_FILENO);
		}
		else
		{
			if (ft_strncmp(tmp->content, " ", 2) != 0)
			{
				ft_putstr_fd(tmp->content, STDOUT_FILENO);
				ft_putstr_fd(" ", STDOUT_FILENO);
			}
		}
		tmp = tmp->next;
	}
	if (!option)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
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
		if (*(str + 1) == '\0')
			break;
		write(fd, str, 1);
		str++;
	}
}
