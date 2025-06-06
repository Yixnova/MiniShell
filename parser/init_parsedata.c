/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsedata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:31:23 by busseven          #+#    #+#             */
/*   Updated: 2025/06/05 19:12:58 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	make_pipes(int pipe_count, t_shelldata *shell)
{
	int			n;
	struct stat	statbuf;

	n = 0;
	while (pipe_count > 0)
	{
		shell->pipes[n] = ft_calloc(2, sizeof(int));
		pipe(shell->pipes[n]);
		fstat(shell->pipes[n][1], &statbuf);
		pipe_count--;
		n++;
	}
}

void	init_parsedata(t_shelldata *shell)
{
	int		i;
	int		count;
	int		pipe_count;

	i = 0;
	count = 0;
	while (shell->tokens[i])
	{
		if (ft_strlen(shell->tokens[i]) == 1 && shell->tokens[i][0] == '|')
			count++;
		i++;
	}
	shell->cmds = ft_calloc(count + 1, sizeof(t_cmd *));
	shell->cmd_count = count + 1;
	pipe_count = count;
	while (count + 1 > 0)
	{
		add_cmd(shell, ft_cmdnew());
		count--;
	}
	if (pipe_count > 0)
		shell->pipes = ft_calloc(pipe_count, sizeof(int *));
	shell->pids = ft_calloc(shell->cmd_count, sizeof(int));
	make_pipes(pipe_count, shell);
}
