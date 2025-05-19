/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:30:23 by busseven          #+#    #+#             */
/*   Updated: 2025/05/19 19:11:22 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_cmds(t_shelldata *shell)
{
	int	i;
	t_cmd	*temp;

	while(shell->cmd_count > 0)
	{
		i = 0;
		while((*(shell->cmds))->has_hd && (*(shell->cmds))->hd_count > 0)
		{
			free((*(shell->cmds))->hd_arr[i]);
			free((*(shell->cmds))->limiter_arr[i]);
			(*(shell->cmds))->hd_count--;
			i++;
		}
		free_2d_char((*(shell->cmds))->tokens);
		free_2d_char((*(shell->cmds))->args);
		free_2d_char((*(shell->cmds))->redirs);
		free((*(shell->cmds))->hd_parsedollar);
		free((*(shell->cmds))->file_descs);
		if((*(shell->cmds))->err_msg)
			free((*(shell->cmds))->err_msg);
		if((*(shell->cmds))->has_hd)
		{
			free((*(shell->cmds))->limiter_arr);
			free((*(shell->cmds))->hd_arr);
		}
		if((*(shell->cmds))->invalid != 1)
			free((*(shell->cmds))->path);
		temp = (*(shell->cmds))->next;
		if(shell->cmds && *(shell->cmds))
			free(*(shell->cmds));
		*(shell->cmds) = temp;
		shell->cmd_count--;
	}
}
