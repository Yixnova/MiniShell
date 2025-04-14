/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_limiter_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:10:31 by busseven          #+#    #+#             */
/*   Updated: 2025/04/14 09:47:25 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	has_valid_redir(char	*str)
{
	if(!strncmp(str, "> ", 2))
		return (1);
	if(!strncmp(str, ">> ", 3))
		return (2);
	if(!strncmp(str, "<< ", 3))
		return (3);
	if(!strncmp(str, "< ", 2))
		return (4);
	return (0);
}

void	make_limiter_arr(t_cmd	*cmd)
{
	int	i;
	int	n;
	int	count;
	int	len;

	i = 0;
	count = 0;
	n = 0;
	while(cmd->redirs[i])
	{
		if(has_valid_redir(cmd->redirs[i]) == 3)
			count++;
		i++;
	}
	cmd->limiter_arr = ft_calloc(count + 1, sizeof(char *));
	i = 0;
	while(cmd->redirs[i])
	{
		if(has_valid_redir(cmd->redirs[i]) == 3)
		{
			len = ft_strlen(cmd->redirs[i] + 3);
			cmd->limiter_arr[n] = ft_substr(cmd->redirs[i], 3, len);
			n++;
		}
		i++;
	}
}
