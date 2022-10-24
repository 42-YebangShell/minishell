#include "../includes/minishell.h"

static void	shell_loop(void);
static char	*set_read_line(t_info *info);

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	g_var.hd_cnt = 0;
	g_var.status = 0;
	g_var.env_list = get_envp_list(envp);
	welcome_screen();
	ft_display_ctrlx_set(NODISPLAY);
	shell_loop();
}

static void	shell_loop(void)
{
	t_info	info;
	char	*cmd_line;

	while (1)
	{
		cmd_line = set_read_line(&info);
		add_history(cmd_line);
		g_var.status = exec_set(cmd_line);
	}
}

static char	*set_read_line(t_info *info)
{
	char	*line;

	signal(SIGINT, sig_readline);
	signal(SIGQUIT, SIG_IGN);
	info->h_token = NULL;
	line = readline("minish$ ");
	if (!line)
	{
		ft_putstr_fd("\033[1A", STDOUT_FILENO);
		ft_putstr_fd("\033[7C", STDOUT_FILENO);
		ft_putstr_fd(" exit\n", STDOUT_FILENO);
		ft_display_ctrlx_set(DISPLAY);
		exit(g_var.status);
	}
	return (line);
}
