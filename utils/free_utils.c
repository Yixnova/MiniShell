/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:30:23 by busseven          #+#    #+#             */
/*   Updated: 2025/05/19 19:38:14 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_shell(t_shelldata *shell)
{
	free_env_list(shell->env);
	free_input_data(shell);
	free_2d_char(shell->input_arr);
	free(shell->read_line);
	free(shell);
}
void	free_here_document_vars(t_shelldata *shell)
{
	int	i;

	i = 0;
	while((*(shell->cmds))->has_hd && (*(shell->cmds))->hd_count > 0)
	{
		free((*(shell->cmds))->hd_arr[i]);
		free((*(shell->cmds))->limiter_arr[i]);
		(*(shell->cmds))->hd_count--;
		i++;
	}
	if((*(shell->cmds))->has_hd)
	{
		free((*(shell->cmds))->limiter_arr);
		free((*(shell->cmds))->hd_arr);
	}
}

void	free_cmds(t_shelldata *shell)
{
	t_cmd	*temp;

	while(shell->cmd_count > 0)
	{
		free_here_document_vars(shell);
		free_2d_char((*(shell->cmds))->tokens);
		free_2d_char((*(shell->cmds))->args);
		free_2d_char((*(shell->cmds))->redirs);
		free((*(shell->cmds))->hd_parsedollar);
		free((*(shell->cmds))->file_descs);
		if((*(shell->cmds))->err_msg)
			free((*(shell->cmds))->err_msg);
		if((*(shell->cmds))->invalid != 1)
			free((*(shell->cmds))->path);
		temp = (*(shell->cmds))->next;
		if(shell->cmds && *(shell->cmds))
			free(*(shell->cmds));
		*(shell->cmds) = temp;
		shell->cmd_count--;
	}
}
