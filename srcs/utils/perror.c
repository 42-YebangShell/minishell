#include "../../includes/minishell.h"

void	ft_perror(char *str)
{
	printf("%s %s\n", str, strerror(errno));
}
