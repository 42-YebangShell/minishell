#include "../../includes/minishell.h"

//for expansion dir

// static int	ft_dollar_len(char *cmd_line, int i);

// char	*replace_dollar(char *cmd_line)
// {
// 	int		i;
// 	int		tot_doll_num;
// 	char	*dollar_wd;
// 	int		dollar_len;

// 	tot_doll_num = cnt_dollar(cmd_line);

// 	i = 0;
// 	while (cmd_line[i])
// 	{./
// 		if (cmd_line[i] == '$' && cmd_line[i + 1] != ' ')
// 		{
// 			dollar_len = ft_dollar_len(cmd_line, i);

// 			ft_strlcpy();
// 		}
// 		i++;
// 	}
// }

// static int	ft_dollar_len(char *cmd_line, int i)
// {
// 	int		len;

// 	len = 0;
// 	while (cmd_line[i] != ' ')
// 	{
// 		len++;
// 		i++;
// 	}
// 	return (len);
// }

// static char	*rm_brace(t_token *token)
// {
// 	char	*result;
// 	char	*content;

// 	content = token->content;
// 	if (content[0] != (char)'{' )
// 		return (content);
// 	result = malloc(sizeof(char) * (ft_strlen(content) + 2));
// 	if (!result)
// 		return (NULL);
// 	ft_strlcpy(result, content + 1, ft_strlen(content) - 1);
// 	return (result);
// }

//////////////////////////////////////////////////

static void	show_token_list(t_token *list)
{
	t_token *tmp;

	if (!list)
		return ;
	tmp = list;
	while (tmp)
	{
		printf(":: NOW :: %s\n", tmp->content);
		// ft_putstr_fd(tmp->content, STDOUT_FILENO);
		// ft_putstr_fd("\n", STDOUT_FILENO);
		tmp = tmp->next;
	}
}
///////////////////////////////////////////////////////

//end
// static void get_expans_list(t_token *token, t_token **expan_token);
// static void	aster_replace(t_token **tokens);
// static int	is_aster_token(t_token token);
// static char	*get_prefix(char *str);
// static char	*get_suffix(char *str);
// static void	token_replace(t_token **tokens_list, t_token *target, t_token *expan_tokens);
// static t_token	*ft_tokenlast(t_token *lst);

int	exec_set(char *cmd_line)
{
	t_info	info;

	info.h_token = NULL;
	tokenizer(&(info.h_token), cmd_line);
	aster_replace(&(info.h_token));/// added
	show_token_list(info.h_token);
	if (check_syntax_error(info.h_token) == SUCCESS && \
		redir_here_doc_check(&info) == SUCCESS)
	{
		info.r_node = create_btree_node(info.h_token);
		set_btree_node(&(info.r_node));
		ft_display_ctrlx_set(DISPLAY);
		execution(&info);
		ft_display_ctrlx_set(NODISPLAY);
		free(cmd_line);
		return (EXIT_SUCCESS);
	}
	else
	{
		delete_token(info.h_token);
		return (EXIT_FAILURE);
	}
}

void	execution(t_info *info)
{
	signal(SIGINT, &sig_exec);
	signal(SIGQUIT, &sig_exec);
	execute_btree_node(info, info->r_node);
	delete_node(info->r_node);
}

void	execute_btree_node(t_info *info, t_tree_node *root)
{
	if (!root)
		return ;
	if (root->type == TN_WORD && root->right == NULL)
		g_var.status = exec_single_word(info, root);
	else if (root->type == TN_PARENS)
		g_var.status = exec_parens(root);
	else if (root->type == TN_AND || root->type == TN_OR)
		exec_and_or(info, root);
	else if (root->type == TN_PIPE)
		g_var.status = exec_pipe(info, root);
}


////////////////////////////////////////////////////
// static void	aster_replace(t_token **tokens_list)
// {
// 	t_token	*tmp;
// 	t_token *itr;
// 	t_token			*expan_tokens;

// 	tmp = *tokens_list;
// 	expan_tokens = NULL;
// 	while (tmp)
// 	{
// 		printf("tmp content :: :: %s\n", tmp->content);
// 		if (is_aster_token(*tmp))
// 		{
// 			get_expans_list(tmp, &expan_tokens);
// 			// show_token_list(expan_tokens);
// 			token_replace(tokens_list, tmp, expan_tokens);
// 		}
// 		tmp = tmp->next;
// 	}

// }


// static int	is_aster_token(t_token token)
// {
// 	int		result;

// 	result = 0;
// 	if (ft_strncmp(token.content, "*", 2) != 0)
// 	{
// 		if (ft_strchr(token.content, '*'))
// 		{
// 			result = 1;
// 		}
// 	}
// 	return (result);
// }

// static void	get_expans_list(t_token *token, t_token **expan_token)
// {
// 	struct dirent	*dirent;
// 	DIR				*dir;
// 	// t_token			*replace_tokens;
// 	t_token			*new;
// 	t_token			input;
// 	char			*prefix;
// 	char			*suffix;
// 	int				pos;


// 	printf("before pre/suffix ::::: %s\n", token->content);
// 	prefix = get_prefix(token->content);
// 	suffix = get_suffix(token->content);
// 	printf("   prefix :: %s \n   suffix :: %s \n", prefix, suffix);///
// 	dir = opendir(".");
// 	while (1)
// 	{
// 		dirent = readdir(dir);
// 		if (!dirent)
// 			break ;
// 		else
// 		{
// 			if (!prefix && !suffix)
// 				continue ;
// 			else if (prefix && !suffix)
// 			{
// 				if (ft_strncmp(dirent->d_name, prefix, ft_strlen(prefix)) == 0)
// 				{
// 					input.content = ft_strdup(dirent->d_name);
// 					input.type = token->type;
// 					printf("1.input :: %s\n", input.content); ////
// 					new = new_token(input);
// 					printf("new :: %s\n", new->content); ///
// 					if (new->content)
// 						add_token(expan_token, new);
// 					// show_token_list(*expan_token);
// 				}
// 			}
// 			else if (!prefix && suffix)
// 			{
// 				pos = ft_strlen(dirent->d_name) - ft_strlen(suffix);
// 				if (pos < 0)
// 					continue ;
// 				if (strncmp(dirent->d_name + pos, suffix, ft_strlen(suffix)) == 0)
// 				{
// 					input.content = ft_strdup(dirent->d_name);
// 					input.type = token->type;
// 					printf("2. input :: %s\n", input.content); ////
// 					new = new_token(input);
// 					printf("new :: %s\n", new->content); ///
// 					if (new->content)
// 						add_token(expan_token, new);
// 					// show_token_list(*expan_token);
// 				}
// 			}
// 			else if (prefix && suffix)
// 			{
// 				if (ft_strncmp(dirent->d_name, prefix, ft_strlen(prefix)) == 0)
// 				{
// 					pos = ft_strlen(dirent->d_name) - ft_strlen(suffix);
// 					if (pos < 0)
// 						continue;
// 					if (strncmp(dirent->d_name + pos, suffix, ft_strlen(suffix)) == 0)
// 					{
// 						input.content = ft_strdup(dirent->d_name);
// 						input.type = token->type;
// 						printf("3. input :: %s\n", input.content);////
// 						new = new_token(input);
// 						printf("new :: %s\n", new->content); ///
// 						if (new->content)
// 							add_token(expan_token, new);
// 						// show_token_list(*expan_token);
// 					}
// 				}
// 			}
// 		}
// 	}
// 	printf("\n\n");
// 	// show_token_list(*expan_token);
// 	closedir(dir);
// 	// show_token_list(*expan_token); //왜 클로즈한다음에는 에러나지..? 이유는 dirent->d_name을 dup 안하고 그대로 썼기 때문
// }

// static char	*get_prefix(char *str)
// {
// 	char	*prefix;
// 	int		len;

// 	if (!str)
// 		return (NULL);
// 	// printf("str[0] == %c\n", str[0]);
// 	len = 0;
// 	while (str[len] && str[len] != '*')
// 		len++;
// 	if (len == 0)
// 		return (NULL);
// 	printf("prefix len :: %d\n", len);//
// 	prefix = (char *)malloc(sizeof(char) * (len + 1 + 1));
// 	if (!prefix)
// 		return (NULL);
// 	ft_strlcpy(prefix, str, len + 1);
// 	return (prefix);
// }

// static char	*get_suffix(char *str)
// {
// 	char	*suffix;
// 	int		pre_len;
// 	int		suf_len;

// 	if (!str)
// 		return (NULL);
// 	pre_len = 0;
// 	while (str[pre_len] && str[pre_len] != '*')
// 		pre_len++;
// 	suf_len = ft_strlen(str) - pre_len - 1;
// 	if (suf_len == 0)
// 		return (NULL);
// 	printf("suffix len :: %d\n", suf_len);//
// 	suffix = (char *)malloc(sizeof(char) * (suf_len + 1 + 1));
// 	if (!suffix)
// 		return (NULL);
// 	ft_strlcpy(suffix, str + pre_len + 1, suf_len + 1);
// 	return (suffix);
// }


// static void	token_replace(t_token **tokens_list, t_token *target, t_token *expan_tokens)
// {
// 	t_token	*tmp;
// 	t_token *tmp2;
// 	t_token *tmp3;

// 	if (expan_tokens == NULL)
// 		return ;
// 	tmp = *tokens_list;
// 	if (tmp == target && tmp->next == NULL)
// 	{
// 		*tokens_list = expan_tokens;
// 	}
// 	while (tmp)
// 	{

// 		if (tmp->next == target)
// 		{
// 			tmp2 = tmp->next->next;
// 			tmp->next = expan_tokens;
// 			tmp3 = ft_tokenlast(expan_tokens);
// 			tmp3->next = tmp2;
// 		}
// 		tmp = tmp->next;
// 	}
// }

// static t_token	*ft_tokenlast(t_token *lst)
// {
// 	if (lst == NULL)
// 		return (NULL);
// 	while (lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
// }
