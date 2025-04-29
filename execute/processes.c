/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:43:40 by busseven          #+#    #+#             */
/*   Updated: 2025/04/29 17:50:35 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

static int is_simple_cd_command(t_cmd *cmd, t_shelldata *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return 0;
	if (shell->cmd_count != 1)
		return 0;
	if (ft_strcmp(cmd->args[0], "cd") != 0)
		return 0;
	if (cmd->redir_count != 0 || cmd->output_type != 0 || cmd->input_type != 0)
		return 0;
	return 1;
}

static void handle_simple_cd(t_cmd *cmd, t_shelldata *shell)
{
	shell->exit_status = cd_command(cmd->args[1]);
	free_command(cmd);
}

static void run_child_process(t_cmd *cmd, t_shelldata *shell, int i, int pid)
{
	if (pid == 0)
	{
		pick_pipes(cmd);
		open_files(cmd);
		pick_file_descriptors(cmd);
		check_command_existence(cmd, shell);
		execute_command(cmd, shell, i);
	}
	close_pipes(&cmd, shell, i);
}

void start_processes(t_shelldata *shell, t_cmd **cmds)
{
	int	pid;
	int	i;
	t_cmd	*temp;

	temp = *cmds;
	i = 0;
	pid = 1;
	if (is_simple_cd_command(*cmds, shell))
	{
		handle_simple_cd(*cmds, shell);
		*cmds = temp;
		return;
	}
	while (*cmds)
	{
		if (pid != 0)
			pid = fork();
		run_child_process(*cmds, shell, i, pid);
		i++;
		*cmds = (*cmds)->next;
	}
	wait_for_children(pid, shell);
	*cmds = temp;
}
