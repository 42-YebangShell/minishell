#include "../includes/minishell.h"

static void	shell_loop();
static void	sig_handler(int signo);
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
	ft_display_ctrlx_set(DISPLAY);
}

static void	shell_loop()
{
	char	*cmd_line;

	while(1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		cmd_line = readline("minish$ ");
		if (cmd_line)
		{	
			// excution(cmd_line);
			tokenizer(cmd_line);
			// printf("%s\n", cmd_line);
		}
		else
		{
			printf("\033[1A");
			printf("\033[7C");
			printf(" exit\n");
			free(cmd_line);
			// ft_display_ctrlx_set();
			exit(1);
		}
	}
}

static void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	return;
}

static void	ft_display_ctrlx_set(int flag)
{
	if (tcgetattr(STDIN_FILENO, &g_var.settings) == ERROR)
		ft_perror("minsh: tcgetattr");
	if (flag)
		g_var.settings.c_lflag &= ECHOCTL;
	else
		g_var.settings.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_var.settings) == ERROR)
		ft_perror("minsh: tcsetattr");
}