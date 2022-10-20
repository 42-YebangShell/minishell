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

void	show_tokens_data(t_token *tokens, char *str)
{
	t_token *tmp;

	if (!tokens)
		return;
	tmp = tokens;
	printf("\033[0;33m");
	printf("token(%s) : \n", str);
	printf("token type = %d\n", tmp->type);
	while (tmp)
	{
		printf("\033[0;33m");
		printf("[%s]", tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
	printf("\n\033[0;0m\x1b[1A\x1b[M");
}

void	show_tree_data(t_tree_node *node, char *str)
{
	if (node)
	{
		printf("%s\n", str);
		printf("node type : %d\n", node->type);
		// show_tokens_data(node->tokens);
		show_tokens_data(node->command, "command");
		show_tokens_data(node->redir, "redirection");
		show_tree_data(node->left, "left");
		show_tree_data(node->right, "right");
	}
}
int	check_syntax_error(t_token *token)
{
	if (token->type == AND || token->type == OR || token->type == PIPE)
	{
		printf("syntax error near unexpected token `%s`\n", token->content);
		return (0);
	}
	return (1);
}
static void	shell_loop()
{
	t_info	info;
	char	*cmd_line;

	while(1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		cmd_line = readline("minish$ ");
		add_history(cmd_line);
		if (cmd_line)
		{
			info.h_token = NULL;
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