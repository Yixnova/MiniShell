/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:24:57 by busseven          #+#    #+#             */
/*   Updated: 2025/04/12 09:55:31 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_cmd(t_shelldata *shell, t_cmd *cmd, int *i, int *n)
{
	int	k;

	k = 0;
	cmd->tokens = ft_calloc(*n - *i + 2, sizeof(char *));
	while(shell->token_arr && shell->token_arr[*i] && *i < *n)
	{
		cmd->tokens[k] = ft_strdup(shell->token_arr[*i]);
		k++;
		(*i)++;
	}
	int z = 0;
	printf("tokens:\n");
	while(cmd->tokens[z])
	{
		printf("%s\n", cmd->tokens[z]);
		z++;
	}
	make_arg_array(cmd, shell);
	printf("args:\n");
	z = 0;
	while(cmd->args[z])
	{
		printf("%s\n", cmd->args[z]);
		z++;
	}
	pipe(cmd->pipe);
	printf("next cmd:\n");
}

void	edit_cmds_arr(t_shelldata *shell, t_cmd *cmds, int i, int n)
{
	if(!cmds)
	{
		printf("no cmd\n");
		return ;
	}
	while(shell->token_arr && shell->token_arr[n] && !is_pipe(shell->token_arr[n]))
		n++;
	init_cmd(shell, cmds, &i, &n);
	edit_cmds_arr(shell, cmds->next, i + 1, n + 1);
}