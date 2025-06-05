/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:40:12 by yigsahin          #+#    #+#             */
/*   Updated: 2025/06/05 19:11:05 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_files(t_cmd **cmds)
{
	int	i;

	i = 0;
	while ((*cmds)->file_descs[i])
	{
		close((*cmds)->file_descs[i]);
		i++;
	}
}

void	display_error_messages(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->err_type == 2)
		{
			ft_putstr_fd(cmds->err_msg, 2);
			ft_putstr_fd("\n", 2);
		}
		cmds = cmds->next;
	}
}

void	close_all_pipes(t_shelldata *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count - 1)
	{
		free(shell->pipes[i]);
		i++;
	}
}

void	close_pipes(t_shelldata *shell, int i)
{
	if (i != 0)
	{
		close(shell->pipes[i - 1][0]);
		close(shell->pipes[i - 1][1]);
	}
}

int	redir_len(char *str)
{
	if (redir_num(str) == 1 || redir_num(str) == 4)
		return (1);
	if (redir_num(str) == 2 || redir_num(str) == 3)
		return (2);
	return (0);
}
