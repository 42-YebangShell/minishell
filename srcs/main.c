#include "../includes/minishell.h"

static void	shell_loop();
static char *set_read_line(t_info *info);
static void	ft_display_ctrlx_set(int flag);

void	show_tokens_data(t_token *tokens, char *str)
{
	t_token *tmp;

	if (!tokens)
		return;
	tmp = tokens;
	// printf("\033[0;33m");
	// printf("token(%s) : \n", str);
	ft_putstr_fd("\033[0;33m", 1);
	ft_putstr_fd("token", 1);
	ft_putstr_fd("(", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(") : ", 1);
	ft_putstr_fd("\n", 1);
	while (tmp)
	{
		// printf("\033[0;33m");
		// printf("[%s(%d)]", tmp->content, tmp->type);
		ft_putstr_fd("\033[0;33m", 1);
		ft_putstr_fd(tmp->content, 1);
		ft_putstr_fd("(", 1);
		ft_putnbr_fd(tmp->type, 1);
		ft_putstr_fd(")", 1);
		tmp = tmp->next;
	}
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\n\033[0;0m\x1b[1A\x1b[M", 1);
	// printf("\n");
	// printf("\n\033[0;0m\x1b[1A\x1b[M");
}

void	show_tree_data(t_tree_node *node, char *str)
{
	if (node)
	{
		// printf("%s\n", str);
		// printf("node type : %d\n", node->type);
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\nnode type : ", 1);
		ft_putnbr_fd(node->type, 1);
		ft_putstr_fd("\n", 1);
		show_tokens_data(node->tokens, "tokens");
		show_tokens_data(node->command, "command");
		//for echo cmd
		if (node->command && ft_strncmp(node->command->content, "echo", 5) == 0)
		{
			ft_echo(node->command);
		}
		//for export cmd
		if (node->command && ft_strncmp(node->command->content, "export", 7) == 0)
		{
			ft_export(node->command);
		}
		// if (node->command && ft_strncmp(node->command->content, "echo", 5) == 0)
		// {
		// 	if (node->command->next)
		// 		ft_echo(node->command->next->content);
		// 	else
		// 		ft_echo("");
		// }
		show_tokens_data(node->redir, "redirection");
		show_tree_data(node->left, "left");
		show_tree_data(node->right, "right");
	}
}

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
	t_info	info;
	char	*cmd_line;

	while(1)
	{
		cmd_line = set_read_line(&info);
		add_history(cmd_line);
		info.h_token = NULL;
		tokenizer(&(info.h_token), cmd_line);
		if (check_syntax_error(info.h_token))
		{
			info.r_node = create_btree_node(info.h_token);
			set_btree_node(&(info.r_node));
			show_tree_data(info.r_node, "root");
		}
		delete_token(info.h_token);
	}
}

static char *set_read_line(t_info *info)
{
	char *line;

	signal(SIGINT, sig_readline);
	signal(SIGQUIT, SIG_IGN);
	info->h_token = NULL;
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
