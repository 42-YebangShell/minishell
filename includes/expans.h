#ifndef EXPANS_H
# define EXPANS_H

//wildcard.c
void	aster_replace(t_token **tokens_list);

//wildcard_utils.c
int		is_aster_token(t_token token);
char	*get_prefix(char *str);
char	*get_suffix(char *str);
void	token_replace(t_token **tokens_list, t_token *target, t_token *expan_tokens);
t_token	*ft_tokenlast(t_token *lst);


#endif
