/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:43:40 by busseven          #+#    #+#             */
/*   Updated: 2025/04/25 14:11:44 by busseven         ###   ########.fr       */
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
	if(cmd->tokens)
		free_2d_char(cmd->tokens);
	if(cmd->args)
		free_2d_char(cmd->args);
	if(cmd->redirs)
		free_2d_char(cmd->redirs);
	if(cmd->limiter_arr)
		free_2d_char(cmd->limiter_arr);
	if(cmd->hd_arr)
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

void	update_pwd_env(t_env **env)
{
	char cwd[BUFFER_SIZE];
	t_env *pwd;
	t_env *oldpwd;
	char *old;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return;
	pwd = find_env(*env, "PWD");
	oldpwd = find_env(*env, "OLDPWD");
	if (pwd && pwd->value)
		old = ft_strdup(pwd->value);
	else
		old = ft_strdup("");
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = old;
	}
	else
		set_env(env, "OLDPWD", old);
	if (pwd)
	{
		free(pwd->value);
		pwd->value = ft_strdup(cwd);
	}
	else
		set_env(env, "PWD", cwd);
}

void start_processes(t_shelldata *shell, t_cmd **cmds)
{
	int	pid;
	int	i;
	t_cmd	*temp;

	temp = *cmds;
	i = 0;
	pid = 1;
	if (shell->cmd_count == 1 && *cmds && (*cmds)->args && (*cmds)->args[0] && !ft_strcmp((*cmds)->args[0], "cd"))
	{
		int cd_status = cd_command((*cmds)->args[1]);
		if (cd_status == 0)
			update_pwd_env(&shell->env);
		shell->exit_status = cd_status;
		free_command(*cmds);
		*cmds = temp;
		return ;
	}
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
		*cmds = (*cmds)->next;
	}
	wait_for_children(pid, shell);
	*cmds = temp;
}
