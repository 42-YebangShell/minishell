#include "../../includes/minishell.h"


#define INFILE 0
#define OUTFILE 1
#define APPD_OUT 2
#define SUCCESS 0

void	ft_handle_error(const char *str)
{
	printf("%s\n", str);
	perror("following error occurs");
	exit(1);
}

int	ft_fileopen(char *filename, int mode)
{
	int		fd;
	int		flag;

	if (mode == INFILE)
	{
		if (access(filename, F_OK) == SUCCESS)
		{
			fd = open(filename, O_RDONLY);
			return (fd);
		}
		else if (access(filename, F_OK) == -1)
			ft_handle_error("infile does not exist");
	}
	flag = O_CREAT | O_WRONLY | O_TRUNC;
	if (mode == APPD_OUT)
		flag = O_CREAT | O_WRONLY | O_APPEND;
	fd = open(filename, flag, 0744);
	if (fd == -1)
		ft_handle_error("outfile open failed");
	return (fd);
}


int	set_redir(t_token *redirs)
{
	t_token	*tmp;
	int		fdin;
	int		fdout;
	int		fd_doc;
	char	*line;

	tmp = redirs;
	if (tmp == NULL)
		return (0);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "<", 2) == 0)
		{
			fdin = ft_fileopen(tmp->next->content, INFILE);
		}
		else if (ft_strncmp(tmp->content, ">", 2) == 0)
		{
			fdout = ft_fileopen(tmp->next->content, OUTFILE);
		}
		else if (ft_strncmp(tmp->content, ">>", 3) == 0)
		{
			fdout = ft_fileopen(tmp->next->content, APPD_OUT);
		}
		else if (ft_strncmp(tmp->content, "<<", 3) == 0)
		{
			fd_doc = ft_fileopen("/tmp/.here_doc", OUTFILE);
			while (1)
			{
				ft_putstr_fd("heredoc> ", 2);
				line = get_next_line(0);
				if (!line)
					ft_handle_error("\nUnexpected EOF");
				if (ft_strncmp(line, tmp->next->content, ft_strlen(tmp->next->content)) == 0)
					break;
				ft_putstr_fd(line, fd_doc);
			}
		}
		tmp = tmp->next;
	}
}