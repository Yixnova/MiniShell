/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:08:21 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/15 12:08:24 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execute.h"

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
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (handle_builtin_command(shell, cmd->args))
		return ;
	pid = fork();
	if (pid == 0)
		exit(external_command(cmd->args, shell));
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork");
}
