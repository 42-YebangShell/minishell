#include "../../includes/minishell.h"

int	ft_cd(t_token *command)
{
	char	*path;

	if (command == NULL)
		return (0);
	if (command->next == NULL)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	path = command->next->content;
	if (ft_strncmp(path, "-", 2) == 0)
	{
		if (chdir(g_var.prev_path) == -1)
		{
			ft_putstr_fd("minsh: cd: OLDPWD not set\n", STDERR_FILENO);
			return (-1);
		}
	}
	else
	{
		g_var.prev_path = getcwd(NULL, 0);
		if (chdir(path) == -1)
		{
			ft_putstr_fd("minsh: cd:", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
			return (-1);
		}
	}
	return (0);
}
