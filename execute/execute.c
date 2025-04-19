/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:08:21 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/19 16:34:19 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execute.h"

void	redir_cmd(t_cmd *cmd, t_shelldata *shell, int i)
{
	if(cmd->input_type == 1)
	{
		dup2(shell->pipes[i - 1][0], 0);
		close(shell->pipes[i - 1][1]);
	}
	else if(cmd->input_type == 2)
		dup2(cmd->input, 0);
	else if(cmd->input_type == 3)
	{
		dup2(cmd->hd_arr[cmd->hd_index][0], 0);
	}
	if(cmd->output_type == 1 && !cmd->next->invalid)
	{
		dup2(shell->pipes[i][1], 1);
		close(shell->pipes[i][0]);
	}
	else if(cmd->output_type == 2)
		dup2(cmd->output, 1);
}

int	is_directory(const char *path)
{
	struct stat	file;

	if (lstat(path, &file) == 0 && S_ISDIR(file.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": is a directory", 2);
		return (1);
	}
	return (0);
}

void	execute_command(t_cmd *cmd, t_shelldata *shell, int i)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		exit(1);
	redir_cmd(cmd, shell, i);
	if (handle_builtin_command(shell, cmd->args))
	{
		if (cmd->path)
			free(cmd->path);
		exit(0);
	}
	if(execve(cmd->path, cmd->args, shell->env->envp) == -1)
		exit(1);
	if (cmd->path)
		free(cmd->path);
	exit(1);
}
