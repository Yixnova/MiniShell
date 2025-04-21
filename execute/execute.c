/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:08:21 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/21 17:35:01 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execute.h"

int	is_directory(const char *path)
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

void	execute_command(t_cmd *cmd, t_shelldata *shell, int i)
{
	(void)i;
	if (!cmd || !cmd->args || !cmd->args[0])
		exit(1);
	if(cmd->invalid)
	{
		exit(127);
	}
	if (handle_builtin_command(shell, cmd->args))
	{
		if (cmd->path)
			free(cmd->path);
		exit(0);
	}
	if(execve(cmd->path, cmd->args, shell->env->envp) == -1)
		exit(1);
	if (cmd->path)
		free(cmd->path);
	exit(1);
}
