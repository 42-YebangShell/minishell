#include "../../includes/minishell.h"

void	sig_readline(int signo)
{
	if (signo == SIGINT)
	{
		g_var.status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	return ;
}

void	sig_exec(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGQUIT)
		printf("Quit: 3\n");
}

void	sig_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		exit(sig + 128);
	}
}
