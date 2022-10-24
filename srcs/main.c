#include "../includes/minishell.h"

static void	shell_loop(void);
static char	*set_read_line(t_info *info);

/*
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
		//for unset cmd
		if (node->command && ft_strncmp(node->command->content, "unset", 6) == 0)
		{
			ft_unset(node->command);
		}
		//for env cmd
		if (node->command && ft_strncmp(node->command->content, "env", 4) == 0)
		{
			ft_env(node->command);
		}
		if (node->command && ft_strncmp(node->command->content, "pwd", 4) == 0)
		{
			ft_pwd(node->command);
		}
		if (node->command && ft_strncmp(node->command->content, "cd", 3) == 0)
		{
			ft_cd(node->command);
		}
		//for pwd cmd
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
*/

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
