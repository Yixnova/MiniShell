/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:24:35 by busseven          #+#    #+#             */
/*   Updated: 2025/04/12 13:10:13 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*join_space(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	ptrlen;
	int		i;

	i = 0;
	ptrlen = ft_strlen(s1) + ft_strlen(s2) + 2;
	ptr = (char *) malloc (sizeof(char) * ptrlen);
	if (!ptr)
		return (NULL);
	while (*s1)
	{
		ptr[i] = *s1;
		s1++;
		i++;
	}
	ptr[i] = ' ';
	i++;
	while (*s2)
	{
		ptr[i] = *s2;
		s2++;
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

void	copy_redir_tokens(t_cmd *cmd, t_shelldata *shell)
{
	int		i;
	int		n;
	char	*str;
	char	*str_next;

	i = 0;
	n = 0;
	while(cmd->tokens[i])
	{
		str = cmd->tokens[i];
		str_next = cmd->tokens[i + 1];
		if(is_redir(str))
		{
			if(!str_next)
				cmd->redirs[n] = ft_strdup(str);
			else if(!ft_strncmp(str, "<<", ft_strlen(str)))
				cmd->redirs[n] = join_space(str, str_next);
			else
				cmd->redirs[n] = join_space(str, expand_str(str_next, shell));
			n++;
			i += 2;
		}
		else
			i++;
	}
}
void	make_redir_array(t_cmd *cmd, t_shelldata *shell)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(cmd->tokens[i])
	{
		if(is_redir(cmd->tokens[i]))
		{
			count++;
			i++;
		}
		i++;
	}
	cmd->redirs = ft_calloc(count + 1, sizeof(char *));
	copy_redir_tokens(cmd, shell);
}