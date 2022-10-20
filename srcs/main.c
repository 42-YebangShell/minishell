#include "../includes/minishell.h"

static void	shell_init(t_info *info, char **envp);
static void	shell_loop();
static char *set_read_line();
static void	ft_display_ctrlx_set(int flag);

int	main(int ac, char **av, char **envp)
{
	t_info	info;

	(void)ac;
	(void)av;
	shell_init(&info, envp);
	shell_loop();
}

static void	shell_init(t_info *info, char **envp)
{
	g_var.status = 0;
	// g_var.settings
	g_var.env_list = get_envp_list(envp);
	welcome_screen();
}

static void	shell_loop()
{
	t_info	info;
	char	*cmd_line;

	while("yebang")
	{
		cmd_line = set_read_line();
		add_history(cmd_line);
		tokenizer(&(info.h_token), cmd_line);
		if (check_syntax_error(info.h_token))
		{
			info.r_node = create_btree_node(info.h_token);
			set_btree_node(&(info.r_node));
			show_tree_data(info.r_node, "root");
			//set redir and exec
			// execution(info.r_node);
		}
		delete_token(info.h_token);
	}
}

static char *set_read_line()
{
	char *cmd_line;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_display_ctrlx_set(NODISPLAY);
	cmd_line = readline("minish$ ");
	if (!cmd_line)
	{
		printf("\033[1A");
		printf("\033[7C");
		printf(" exit\n");
		free(cmd_line);
		ft_display_ctrlx_set(DISPLAY);
		exit(1);
	}
	return (cmd_line);
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