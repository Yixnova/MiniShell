/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:24:35 by busseven          #+#    #+#             */
/*   Updated: 2025/04/12 10:35:48 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
				cmd->redirs[n] = ft_strjoin(str, str_next);
			else
				cmd->redirs[n] = ft_strjoin(str, expand_str(str_next, shell));
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