/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:24:57 by busseven          #+#    #+#             */
/*   Updated: 2025/04/09 16:11:18 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_cmd(t_shelldata *shell, t_cmd *cmd, int *i, int *n)
{
	int	k;

	k = 0;
	cmd->tokens = ft_calloc(*n + 1, sizeof(char *));
	while(shell->token_arr[*i] && *i < *n)
	{
		cmd->tokens[k] = shell->token_arr[*i];
		k++;
		(*i)++;
	}
	make_arg_array(cmd);
}

void	parser(t_shelldata *shell, t_cmd *cmds, int i, int n)
{
	int	pid;
	int	status;

	if(!cmds || !shell->token_arr[i])
		return ;
	pid = fork();
	while(shell->token_arr[n] && !is_pipe(shell->token_arr[n]))
		(n)++;
	if(pid == 0)
	{
		init_cmd(shell, cmds, &i, &n);
		exit(1);
	}
	else
	{
		parser(shell, cmds->next, n + 1, n + 1);
	}
	waitpid(pid, &status, 0);
	if(WIFEXITED(status))
	{
		//child'ın exit statusunu çeker
		shell->exit_status = WEXITSTATUS(status);
	}
}
