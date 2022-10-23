#include "../includes/minishell.h"

static void	shell_loop();
static char *set_read_line();
static void	ft_display_ctrlx_set(int flag);

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	g_var.status = 0;
	g_var.env_list = get_envp_list(envp);
	welcome_screen();
	ft_display_ctrlx_set(NODISPLAY);
	shell_loop();
}

static void	shell_loop()
{
	char	*cmd_line;

	while(1)
	{
		cmd_line = set_read_line();
		add_history(cmd_line);
		exec_set(cmd_line);
	}
}

static char *set_read_line()
{
	char *line;

	signal(SIGINT, sig_readline);
	signal(SIGQUIT, SIG_IGN);
	line = readline("minish$ ");
	if (!line)
	{
		printf("\033[1A");
		printf("\033[7C");
		printf(" exit\n");
		ft_display_ctrlx_set(DISPLAY);
		exit(g_var.status);
	}
	return (line);
}
