/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:43:40 by busseven          #+#    #+#             */
/*   Updated: 2025/04/15 19:48:33 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pick_pipes(t_cmd *cmd)
{
	cmd->input = 0;
	cmd->output = 1;
	if (cmd->prev)
		cmd->input = cmd->prev->pipe[0];
	if(cmd->next)
		cmd->output = cmd->next->pipe[1];
}
void	pick_file_descriptors(t_cmd *cmd)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	while (cmd->redirs[i])
	{
		if (redir_num(cmd->redirs[i]) != 3)
		{
			if(redir_num(cmd->redirs[i]) == 2 || redir_num(cmd->redirs[i]) == 1)
			{
				cmd->output = cmd->file_descs[f];
				cmd->append = redir_num(cmd->redirs[i]);
			}
			else if (redir_num(cmd->redirs[i]) == 4)
				cmd->input = cmd->file_descs[f];
			f++;
		}
		else
		{
			cmd->input = cmd->hd_arr[cmd->hd_index][0];
			cmd->hd_index++;
		}
		i++;
	}
}

void	open_files(t_cmd *cmd)
{
	int		i;
	int		n;
	char	*file_name;

	i = 0;
	n = 0;
	cmd->fd_count = cmd->redir_count - cmd->hd_count;
	cmd->file_descs = ft_calloc(cmd->fd_count, sizeof(int));
	while (cmd->redirs[i])
	{
		file_name = cmd->redirs[i] + is_in_str(cmd->redirs[i], ' ') + 1;
		if(redir_num(cmd->redirs[i]))
		{
			if (redir_num(cmd->redirs[i]) == 1)
				cmd->file_descs[n] = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 777);
			else if (redir_num(cmd->redirs[i]) == 2)
				cmd->file_descs[n] = open(file_name, O_RDWR | O_CREAT | O_APPEND, 777);
			else if (redir_num(cmd->redirs[i]) == 4)
				cmd->file_descs[n] = open(file_name, O_RDONLY);
			if (cmd->file_descs[n] < 0)
				//error:no such file, exit from the process entirely.
			n++;
		}
		i++;
	}
}

void	start_processes(t_shelldata *shell, t_cmd **cmds)
{
	int		pid;
	int		status;
	t_cmd	*temp;
	
	temp = *cmds;
	while (*cmds)
	{
		pid = fork();
		if (pid == 0)
		{
			pick_pipes(*cmds);
			open_files(*cmds);
			pick_file_descriptors(*cmds);
			execute_command(*cmds, shell);
			close_pipes(*cmds);
		}
		*cmds = (*cmds)->next;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		shell->exit_status = WEXITSTATUS(status);
		printf("%d\n", WEXITSTATUS(status));
	}
	*cmds = temp;
}
