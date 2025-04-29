/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:43:40 by busseven          #+#    #+#             */
/*   Updated: 2025/04/29 15:46:33 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		is_file_dir_name(char *file)
{
	int i;

	i = 0;
	while(file[i] == '.')
		i++;
	if(file[i] == '/')
		return (1);
	return (0);
}
void	check_command_existence(t_cmd *cmd, t_shelldata *shell)
{
	int	valid;

	valid = find_command_path(cmd, shell);
	if(cmd->built_in)
		return ;
	if(!valid)
	{
		if(is_file_dir_name(cmd->args[0]))
		{
			if(is_directory(cmd->args[0]))
				directory_error(cmd->args[0]);
			else
				no_such_file(cmd->args[0]);
		}
	}
	else
	{
		if(access(cmd->path, X_OK) == 0)
			return ;
		else
		{
			access_permission_denied(cmd->args[0]);			
		}
	}
}
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
	while (*cmds)
	{
		if(pid != 0)
			pid = fork();
		if (pid == 0)
		{
			pick_pipes(*cmds);
			open_files(*cmds);
			pick_file_descriptors(*cmds);
			check_command_existence(*cmds, shell);
			execute_command(*cmds, shell, i);
		}
		close_pipes(cmds, shell, i);
		i++;
		*cmds = (*cmds)->next;
	}
	wait_for_children(pid, shell);
	*cmds = temp;
}
