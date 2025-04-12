/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:24:35 by busseven          #+#    #+#             */
/*   Updated: 2025/04/12 10:24:11 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	copy_redir_tokens(t_cmd *cmd, t_shelldata *shell)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while(cmd->tokens[i])
	{
		if(is_redir(cmd->tokens[i]))
		{
			if(!cmd->tokens[i + 1])
				cmd->redirs[n] = ft_strdup(cmd->tokens[i]);
			else if(!ft_strncmp(cmd->tokens[i], "<<", ft_strlen(cmd->tokens[i])))
				cmd->redirs[n] = ft_strjoin(cmd->tokens[i], cmd->tokens[i + 1]);
			else
				cmd->redirs[n] = ft_strjoin(cmd->tokens[i], expand_string(cmd->tokens[i + 1], shell));
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