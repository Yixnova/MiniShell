/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:43:40 by busseven          #+#    #+#             */
/*   Updated: 2025/05/10 09:53:00 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	set_envp(t_shelldata *shell, t_env *env)
{
	t_env	*temp;
	int		count;
	int		i;

	temp = env;
	count = 0;
	i = 0;
	while(temp)
	{
		count++;
		temp = temp->next;
	}
	temp = env;
	shell->env->envp = ft_calloc(count + 1, sizeof(char *));
	while(temp)
	{
		shell->env->envp[i] = ft_myjoin(temp->name, "=", temp->value);
		temp = temp->next;
		i++;
	}
}
void	wait_for_children(t_shelldata *shell)
{
	int	status;
	int	pid;
	int	old_pid;
	int	n;

	n = 0;
	pid = -1;
	while (n < shell->cmd_count)
	{
		old_pid = pid;
		pid = wait(&status);
		if(pid > old_pid)
		{
			if (WIFEXITED(status))
			{
				shell->exit_status = WEXITSTATUS(status);
			}
		}
		n++;
	}
}

static int	is_simple_cd_command(t_cmd *cmd, t_shelldata *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (shell->cmd_count != 1)
		return (0);
	if (ft_strcmp(cmd->args[0], "cd") != 0)
		return (0);
	if (cmd->redir_count != 0 || cmd->output_type != 0 || cmd->input_type != 0)
		return (0);
	return (1);
}
static int	is_simple_export_command(t_cmd *cmd, t_shelldata *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (shell->cmd_count != 1)
		return (0);
	if (ft_strcmp(cmd->args[0], "export") != 0)
		return (0);
	if (cmd->redir_count != 0 || cmd->output_type != 0 || cmd->input_type != 0)
		return (0);
	return (1);
}
static int	is_simple_unset_command(t_cmd *cmd, t_shelldata *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (shell->cmd_count != 1)
		return (0);
	if (ft_strcmp(cmd->args[0], "unset") != 0)
		return (0);
	if (cmd->redir_count != 0 || cmd->output_type != 0 || cmd->input_type != 0)
		return (0);
	return (1);
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
void	close_all_pipes(t_shelldata *shell)
{
	int i;

	i = 0;
	while(i < shell->cmd_count - 1)
	{
		free(shell->pipes[i]);
		i++;
	}
}
void start_processes(t_shelldata *shell, t_cmd **cmds)
{
	int		pid;
	int		i;
	t_cmd	*temp;

	temp = *cmds;
	i = 0;
	pid = 1;
	while (*cmds)
	{
		(*cmds)->exit_code = 0;
		if(open_files(*cmds, shell))
		{
			;
		}
		else if(check_command_existence(*cmds, shell))
		{
			;
		}
		if((*cmds)->invalid)
			command_not_found(*cmds, (*cmds)->args[0]);
		*cmds = (*cmds)->next;
	}
	*cmds = temp;
	if (is_simple_cd_command(*cmds, shell))
	{
		handle_simple_cd(*cmds, shell);
		*cmds = temp;
		return ;
	}
	if(is_simple_export_command(*cmds, shell))
	{
		shell->exit_status = export_command(&shell->env, (*cmds)->args, shell);
		if(shell->exit_status == 0)
			set_envp(shell, shell->env);
		return ;
	}
	else if(is_simple_unset_command(*cmds, shell))
	{
		shell->exit_status = unset_command(&shell->env, (*cmds)->args);
		return ;
	}
	*cmds = temp;
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
	while (*cmds)
	{
		if((*cmds)->err_type == 1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd((*cmds)->err_msg, 2);
			ft_putstr_fd("\n", 2);	
		}
		*cmds = (*cmds)->next;
	}
	*cmds = temp;
	while (*cmds)
	{
		if((*cmds)->err_type == 2)
		{
			ft_putstr_fd((*cmds)->err_msg, 2);
			ft_putstr_fd("\n", 2);
		}
		*cmds = (*cmds)->next;
	}
}
