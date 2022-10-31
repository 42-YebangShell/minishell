#include "../../includes/minishell.h"

int	ft_cd(t_token *command)
{
	char	*path;
	int		res;
	static char	*cwd;
	char		*tmp;

	cwd = getcwd(NULL, 0);
	if (command == NULL)
		return (0);
	if (command->next == NULL)
	{
		g_var.prev_path = cwd;
		chdir(getenv("HOME"));
		cwd = getcwd(NULL, 0);
		return (0);
	}
	path = command->next->content;
	if (ft_strncmp(path, "-", 2) == 0)
	{
		tmp = cwd;
		res = chdir(g_var.prev_path);
		g_var.prev_path = tmp;
		if (res == -1)
		{
			ft_putstr_fd("minsh: cd: OLDPWD not set\n", STDERR_FILENO);
			return (-1);
		}
	}
	else
	{
		g_var.prev_path = cwd;
		res = chdir(path);
		if (res == -1)
		{
			ft_putstr_fd("minsh: cd:", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
			return (-1);
		}
	}
	return (0);
}
