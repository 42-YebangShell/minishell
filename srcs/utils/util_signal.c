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
	return;
}
