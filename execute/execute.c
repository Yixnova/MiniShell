/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:38:29 by yigsahin          #+#                #+#             */
/*   Updated: 2025/03/26 13:54:43 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_directory(const char *path)
{
	struct stat	f;

	if (lstat(path, &f) == 0 && S_ISDIR(f.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": is a directory", 2);
		return (1);
	}
	return (0);
}

static int	command_not_found(const char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}

static int	execute_external_command(char **args, t_shelldata *shell)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	if (access(args[0], F_OK | X_OK) == 0 && !is_directory(args[0]))
		execve(args[0], args, shell->env->envp);
	paths = ft_split(find_env(shell->env, "PATH")->value, ':');
	if (!paths)
		return (command_not_found(args[0]));
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
	ft_arrfree(paths);
	return (command_not_found(args[0]));
}

void	execute_command(t_shelldata *shell)
{
	char	**args = ft_split(shell->input, ' ');
	pid_t	pid;
	int		status;

	if (!args || !args[0])
	{
		ft_arrfree(args);
		return ;
	}
	if (handle_builtin_command(shell, args))
	{
		ft_arrfree(args);
		return ;
	}
	pid = fork();
	if (pid == 0)
		exit(execute_external_command(args, shell));
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork");
	ft_arrfree(args);
}
