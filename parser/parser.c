/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:24:57 by busseven          #+#    #+#             */
/*   Updated: 2025/04/09 13:27:46 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_cmd(t_shelldata *shell, t_cmd *cmd, int *i, int *n)
{
	int	k;

	k = 0;
	while(shell->tokens[*n] && shell->tokens[*n] != "|")
		(*n)++;
	cmd->tokens = ft_calloc(*n, sizeof(char *));
	while(shell->tokens[*i] && *i < *n)
	{
		cmd->tokens[k] = shell->tokens[*i];
		k++;
		(*i)++;
	}
	make_arg_array(cmd);
	make_redir_array(cmd);
	make_limiter_arr(cmd);
	make_here_documents(cmd);
}

void	parser(t_shelldata *shell, int i, int n)
{
	int	pid;
	int	status;

	pid = fork();
	find_pipe(shell->token_arr, *n);
	if(pid == 0)
	{
		init_cmd(shell, *(shell->cmd), *i, *n);
	}
	else
	{
		parser(shell, *(shell->cmd)->next n + 1, n + 1);
	}
	waitpid(pid, &status, 0);
	if(WIFEXITED(status))
	{
		//child'ın exit statusunu çeker
		shell->exit = WEXITSTATUS(status);
	}
}
