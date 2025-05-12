/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:08:21 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/12 14:25:26 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execute.h"

void	redir_cmd(t_cmd *cmd, t_shelldata *shell, int i)
{
	if (cmd->input_type == 1)
	{
		close(shell->pipes[i - 1][1]);
		dup2(shell->pipes[i - 1][0], 0);
		close(shell->pipes[i - 1][0]);
		close(shell->pipes[i - 1][1]);
	}
	else if (cmd->input_type == 2)
		dup2(cmd->input, 0);
	else if (cmd->hd_arr && cmd->input_type == 3)
	{
		close(cmd->hd_arr[cmd->hd_index][1]);
		dup2(cmd->hd_arr[cmd->hd_index][0], 0);
	}
	if (cmd->output_type == 1)
	{
		close(shell->pipes[i][0]);
		dup2(shell->pipes[i][1], 1);
		close(shell->pipes[i][1]);
		close(shell->pipes[i][0]);
	}
	else if (cmd->output_type == 2)
		dup2(cmd->output, 1);
}

void	execute_command(t_cmd *cmd, t_shelldata *shell, int i)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		exit(0);
	redir_cmd(cmd, shell, i);
	if (is_builtin_command(cmd->args[0]))
	{
		if (handle_builtin_command(shell, cmd->args))
		{
			if (cmd->path)
				free(cmd->path);
			exit(0);
		}
	}
	else if (execve(cmd->path, cmd->args, shell->env->envp) == -1)
		execve_error();
	if (cmd->path)
		free(cmd->path);
	exit(0);
}
