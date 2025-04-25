/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:43:40 by busseven          #+#    #+#             */
/*   Updated: 2025/04/25 11:23:52 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_2d_int(int **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
void	free_command(t_cmd *cmd)
{
	free_2d_char(cmd->tokens);
	free_2d_char(cmd->args);
	free_2d_char(cmd->redirs);
	free_2d_char(cmd->limiter_arr);
	free_2d_int(cmd->hd_arr);
	if(cmd->path)
		free(cmd->path);
}
void	close_pipes(t_cmd **cmds, t_shelldata *shell, int i)
{
	if((*cmds)->input_type == 3)
		close((*cmds)->hd_arr[(*cmds)->hd_index][0]);
	if(i != 0)
		close(shell->pipes[i - 1][0]);
	if(i != shell->cmd_count - 1)
		close(shell->pipes[i][1]);
}
void	wait_for_children(int pid, t_shelldata *shell)
{
	int	status;
	int	n;
	(void)pid;
	n = 0;
	while (n < shell->cmd_count)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			shell->exit_status = WEXITSTATUS(status);
		}
		n++;
	}
}


void	start_processes(t_shelldata *shell, t_cmd **cmds)
{
	int		pid;
	int		i;
	t_cmd	*temp;
	t_cmd	*to_free;

	temp = *cmds;
	i = 0;
	pid = 1;
	while (*cmds)
	{
		if(pid != 0)
			pid = fork();
		if (pid == 0)
		{
			pick_pipes(*cmds);
			open_files(*cmds);
			pick_file_descriptors(*cmds);
			if(!find_command_path(*cmds, shell))
				(*cmds)->invalid = 1;
			execute_command(*cmds, shell, i);
		}
		close_pipes(cmds, shell, i);
		i++;
		to_free = *cmds;
		free_command(to_free);
		*cmds = (*cmds)->next;
	}
	wait_for_children(pid, shell);
	*cmds = temp;
}
