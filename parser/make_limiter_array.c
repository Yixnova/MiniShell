/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_limiter_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:10:31 by busseven          #+#    #+#             */
/*   Updated: 2025/05/16 14:55:43 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	has_no_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (0);
		i++;
	}
	return (1);
}

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

void	add_limiters(t_cmd *cmd)
{
	int	i;
	int	n;
	int	len;
	char *temp;

	i = 0;
	n = 0;
	while (cmd->redirs[i])
	{
		if (redir_num(cmd->redirs[i]) == 3)
		{
			len = ft_strlen(cmd->redirs[i] + 3);
			if (len > 0)
				cmd->has_hd = 1;
			cmd->hd_parsedollar[n] = has_no_quotes(cmd->redirs[i] + 3);
			temp = rm_quotes(cmd->redirs[i], 0);
			cmd->limiter_arr[n] = ft_substr(temp, 3, len);
			free(temp);
			n++;
		}
		i++;
	}
}

void	make_limiter_arr(t_cmd	*cmd)
{
	int	i;

	i = 0;
	cmd->hd_count = 0;
	if (!cmd || !cmd->redirs || !ft_strcmp(cmd->redirs[0], "\0"))
		return ;
	while (cmd->redirs[i])
	{
		if (redir_num(cmd->redirs[i]) == 3)
			cmd->hd_count++;
		i++;
	}
	if (cmd->hd_count <= 0)
		return ;
	cmd->limiter_arr = ft_calloc(cmd->hd_count, sizeof(char *));
	cmd->hd_parsedollar = ft_calloc(cmd->hd_count, sizeof(int));
	add_limiters(cmd);
}
