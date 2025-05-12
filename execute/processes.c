/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:43:40 by busseven          #+#    #+#             */
/*   Updated: 2025/05/12 11:08:55 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	wait_for_children(t_shelldata *shell)
{
	int	status;
	int	pid;
	int	n;

	n = 0;
	while (n < shell->cmd_count)
	{
		pid = wait(&status);
		if(pid == shell->pids[shell->cmd_count - 1])
		{
			if (WIFEXITED(status))
			{
				display_error_messages(*(shell->cmds));
				shell->exit_status = WEXITSTATUS(status);
			}
		}
		n++;
	}
}

static void	handle_simple_cd(t_cmd *cmd, t_shelldata *shell)
{
	if (cmd->args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		shell->exit_status = 1;
	}
	else
	{
		shell->exit_status = cd_command(cmd->args[1]);
	}
}

static void	run_child_process(t_cmd *cmd, t_shelldata *shell, int i, int pid)
{
	if (pid == 0)
	{
		if(cmd->exit_code != 0)
			exit(cmd->exit_code);
		pick_pipes(cmd);
		pick_file_descriptors(cmd);
		if(ft_strcmp(cmd->args[0], "export") && ft_strcmp(cmd->args[0], "unset"))
			execute_command(cmd, shell, i);
		exit (0);
	}
	shell->pids[i] = pid;
}

int	handle_cd_unset_export(t_cmd *cmds, t_cmd *temp, t_shelldata *shell)
{
	if (is_simple_cd_command(cmds, shell))
	{
		handle_simple_cd(cmds, shell);
		cmds = temp;
		return (1);
	}
	if(is_simple_export_command(cmds, shell))
	{
		shell->exit_status = export_command(&shell->env, cmds->args, shell);
		if(shell->exit_status == 0)
			set_envp(shell, shell->env);
		return (1);
	}
	else if(is_simple_unset_command(cmds, shell))
	{
		shell->exit_status = unset_command(&shell->env, cmds->args);
		return (1);
	}
	return (0);
}

void start_processes(t_shelldata *shell, t_cmd **cmds)
{
	int		pid;
	int		i;
	t_cmd	*temp;

	temp = *cmds;
	i = 0;
	pid = 1;
	assign_error_messages(*cmds, shell);
	if(handle_cd_unset_export(*cmds, temp, shell))
		return ;
	while (*cmds)
	{
		if (pid != 0)
			pid = fork();
		run_child_process(*cmds, shell, i, pid);
		if((*cmds)->input_type == 3)
			close((*cmds)->hd_arr[(*cmds)->hd_index][0]);
		close_pipes(shell, i);
		i++;
		*cmds = (*cmds)->next;
	}
	*cmds = temp;
	wait_for_children(shell);
}
