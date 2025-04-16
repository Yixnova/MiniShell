/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:08:21 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/16 10:24:25 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execute.h"

void	close_pipes(t_cmd	*cmd)
{
	if(cmd->input == cmd->prev->pipe[0])
		close(cmd->prev->pipe[0]);
	else if(cmd->input == cmd->hd_arr[cmd->hd_index][0])
		close(cmd->hd_arr[cmd->hd_index][0]);
	else if(cmd->input != 0)
		close(cmd->input);
	if(cmd->output == cmd->pipe[1])
	{
		close(cmd->pipe[1]);
	}
	else if(cmd->output != 1)
		close(cmd->output);
}

void	redirect_cmd(t_cmd	*cmd)
{
	if(cmd->prev && cmd->input == cmd->prev->pipe[0])
		dup2(cmd->prev->pipe[0], 0);
	else if(cmd->hd_arr[cmd->hd_index] && cmd->input == cmd->hd_arr[cmd->hd_index][0])
		dup2(cmd->hd_arr[cmd->hd_index][0], 0);
	else if(cmd->input != 0)
		dup2(cmd->input, 0);
	if(cmd && cmd->output == cmd->pipe[1])
		dup2(cmd->pipe[1], 1);
	else if(cmd->output != 1)
		dup2(cmd->output, 1);
}
static int	is_directory(const char *path)
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

static int	not_found(const char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}

static int	external_command(char **args, t_shelldata *shell)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	if (access(args[0], F_OK | X_OK) == 0 && !is_directory(args[0]))
		execve(args[0], args, shell->env->envp);
	paths = ft_split(find_env(shell->env, "PATH")->value, ':');
	if (!paths)
		return (not_found(args[0]));
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_myjoin(paths[i], "/", args[0]);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			execve(cmd_path, args, shell->env->envp);
			free(cmd_path);
			break ;
		}
		free(cmd_path);
		i++;
	}
	array_free(paths);
	return (not_found(args[0]));
}

void	execute_command(t_cmd *cmd, t_shelldata *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		exit(1) ;
	redirect_cmd(cmd);
	if (handle_builtin_command(shell, cmd->args))
		exit(0) ;
	external_command(cmd->args, shell);
}
