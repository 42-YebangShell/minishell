#include "../../includes/minishell.h"

static int	exec_count_pipe(t_tree_node *root);
static void	exec_pipe_child(t_info *info, t_tree_node *root, t_pipe p);
static int	exec_last_pipe(t_info *info, t_tree_node *root, t_pipe p);
static void	exit_wait(int cnt);

int	exec_pipe(t_info *info, t_tree_node *root)
{
	t_pipe	p;
	int		i;
	int		**fd;
	int		*pid;
	int		status;

	p.cnt = exec_count_pipe(root);
	fd = (int **)malloc(sizeof(int *) * (p.cnt));
	i = 0;
	while (i < p.cnt)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	//PIPE fd 2DIM array created
	pid = (int *)malloc(sizeof(int) * (p.cnt + 1)); //pid 할당 생성
	
	i = 0;
	while (i < p.cnt)
	{
		if (pipe(fd[i]) == -1)
			exit(1);
		pid[i] = fork();
		if (pid[i] == -1)
			exit(i - 1);
		if (pid[i] == 0)
		{
			if (root->type == TN_PARENS)
				exec_parens(root);
			close(fd[i][READ_END]);
			dup2(fd[i][WRITE_END], STDOUT_FILENO);
			close(fd[i][WRITE_END]);
			if (root->type != TN_PARENS)
			{
				if (check_builtin(root->command) == EXIT_SUCCESS)
					p.status = run_builtin(info, root);
				else
					p.status = exec_word_child(info, root);
			}
			g_var.status = p.status;
		}
		else
		{
			close(fd[i][WRITE_END]);
			root = root->right;
			
		}
		i++;

	}

	pid[i] = fork();
	if (pid[i] == -1)
		exit(1);
	else if (pid[i] == 0)
	{
		status = exec_last_word_child(info, root, p);
		exit(status);
	}
	close(fd[i - 1][READ_END]);
	close(fd[i - 1][WRITE_END]);
	i = 0;
	while (i <= p.cnt)
	{
		if (waitpid(pid[i], &p.status, 0) == p.pid)
			status = p.status;
		i++;
	}
	return (check_status(status));
}


static int	exec_count_pipe(t_tree_node *root)
{
	int	cnt;

	cnt = 0;
	while (root->type == TN_PIPE)
	{
		cnt++;
		root = root->right;
	}
	return (cnt);
}