#include "../../includes/minishell.h"

static int	redir_open_fd(t_info *info, t_token *token);
static int	redir_open_file(char *filename, t_token *token);

int	redirection(t_info *info, t_tree_node *root)
{
	t_token	*token;
	int		r_status;

	r_status = EXIT_FAILURE;
	token = root->redir;
	while (token)
	{
		if (token->type == HERE_DOC)
			redir_here_doc(token);
		else
			r_status = redir_open_fd(info, token);
		token = token->next;
	}
	return (r_status);
}

static int	redir_open_fd(t_info *info, t_token *token)
{
	int		r_status;
	char	*filename;

	filename = NULL;
	if (!token->next)
		return (EXIT_FAILURE);
	filename = token->next->content;
	if (!filename)
		return (EXIT_FAILURE);
	r_status = redir_open_file(filename, token);
	if (r_status == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (r_status);
}

static int	redir_open_file(char *filename, t_token *token)
{
	int	fd;

	fd = -1;
	if (token->type == INP_RDIR && access(filename, F_OK))
	{
		fd = open(filename, O_RDONLY | O_CLOEXEC, 0777);
		dup2(fd, STDIN_FILENO);
	}
	else if (!token->type == INP_RDIR)
	{
		if (token->type == OUT_RDIR)
			fd = open(filename, O_TRUNC | O_CREAT | O_RDWR, 0644);
		else if (token->type == APP_RDIR)
			fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	if (fd == -1)
	{
		ft_perror(filename, ": No such file or directory");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
