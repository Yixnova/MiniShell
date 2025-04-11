/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:24:57 by busseven          #+#    #+#             */
/*   Updated: 2025/04/11 15:12:06 by busseven         ###   ########.fr       */
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
	int z = 0;
	while(cmd->tokens[z])
	{
		printf("%s\n", cmd->tokens[z]);
		z++;
	}
	pipe(cmd->pipe);
	make_arg_array(cmd);
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