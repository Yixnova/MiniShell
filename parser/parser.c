/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:24:57 by busseven          #+#    #+#             */
/*   Updated: 2025/04/11 12:37:53 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_cmd(t_shelldata *shell, t_cmd *cmd, int *i, int *n)
{
	int	k;

	k = 0;
	cmd->tokens = ft_calloc(*n + 1, sizeof(char *));
	while(shell->token_arr && shell->token_arr[*i] && *i < *n)
	{
		cmd->tokens[k] = shell->token_arr[*i];
		k++;
		(*i)++;
	}
	pipe(cmd->pipe);
	printf("next cmd:\n");
}

void	edit_cmds_arr(t_shelldata *shell, t_cmd *cmds, int i, int n)
{
	if(!cmds)
		return ;
	while(shell->token_arr && shell->token_arr[n] && !is_pipe(shell->token_arr[n]))
		n++;
	init_cmd(shell, cmds, &i, &n);
	if(!shell->token_arr[i])
		return ;
	edit_cmds_arr(shell, cmds->next, i + 1, n + 1);
}