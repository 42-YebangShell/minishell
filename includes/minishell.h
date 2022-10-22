#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/get_next_line/get_next_line.h"

# include "struct.h"
# include "utils.h"
# include "parser.h"
# include "exec.h"
# include "env.h"
# include "builtin.h"

t_global	g_var;
void		rl_replace_line (const char *text, int clear_undo);

#endif
