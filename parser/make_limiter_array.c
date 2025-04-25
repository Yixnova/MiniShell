/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_limiter_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:10:31 by busseven          #+#    #+#             */
/*   Updated: 2025/04/25 10:58:44 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	redir_num(char	*str)
{
	if (!strncmp(str, "> ", 2))
		return (1);
	if (!strncmp(str, ">> ", 3))
		return (2);
	if (!strncmp(str, "<< ", 3))
		return (3);
	if (!strncmp(str, "< ", 2))
		return (4);
	return (0);
}

void	make_limiter_arr(t_cmd	*cmd)
{
	int	i;
	int	n;
	int	len;

	i = 0;
	n = 0;
	if(!cmd || !cmd->redirs || !ft_strcmp(cmd->redirs[0], "\0"))
		return ;
	while (cmd->redirs[i])
	{
		if(redir_num(cmd->redirs[i]) == 3)
			cmd->hd_count++;
		i++;
	}
	if(cmd->hd_count < 0)
		return ;
	cmd->limiter_arr = ft_calloc(cmd->hd_count, sizeof(char *));
	i = 0;
	while (cmd->redirs[i])
	{
		if(redir_num(cmd->redirs[i]) == 3)
		{
			len = ft_strlen(cmd->redirs[i] + 3);
			cmd->limiter_arr[n] = ft_substr(cmd->redirs[i], 3, len);
			n++;
		}
		i++;
	}
}
