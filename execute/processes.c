/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:43:40 by busseven          #+#    #+#             */
/*   Updated: 2025/04/23 11:01:50 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_pipes(t_cmd **cmds, t_shelldata *shell, int i)
{
	if((*cmds)->input_type == 3)
		close((*cmds)->hd_arr[(*cmds)->hd_index][0]);
	if(i != 0)
		close(shell->pipes[i - 1][0]);
	if(i != shell->cmd_count - 1 && (*cmds)->output_type == 1)
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
		if(pid != 0)
			close_pipes(cmds, shell, i);
		i++;
		*cmds = (*cmds)->next;
	}
	wait_for_children(pid, shell);
	*cmds = temp;
}
