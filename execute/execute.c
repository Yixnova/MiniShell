/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:08:21 by yigsahin          #+#    #+#             */
/*   Updated: 2025/06/05 19:10:58 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execute.h"

void	execve_fail(t_cmd *cmd)
{
	write(2, "minishell: ", 11);
	if (errno == EACCES)
	{
		if (is_directory(cmd->args[0]))
			directory_error(cmd, cmd->args[0]);
		else
		{
			write(2, cmd->args[0], ft_strlen(cmd->args[0]));
			write(2, ": ", 2);
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, "\n", 1);
			if (!ft_strncmp("Permission", strerror(errno), 10))
				exit(126);
			else if (!ft_strncmp("No such", strerror(errno), 7))
				exit(127);
		}
	}
	else if (errno == ENOENT)
		no_such_file(cmd, cmd->args[0]);
	else
		execve_error(cmd->args[0]);
}

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
	if (!ft_strcmp(cmd->args[0], "export")
		|| !ft_strcmp(cmd->args[0], "unset"))
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
	else if (execve(cmd->path, cmd->args, shell->envp) == -1)
		execve_fail(cmd);
	if (cmd->path)
		free(cmd->path);
	exit(0);
}
