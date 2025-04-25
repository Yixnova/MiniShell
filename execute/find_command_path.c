/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:34:02 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/23 11:16:30 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execute.h"

int	check_builtin_and_path(t_cmd *cmd)
{
	if(!cmd->args || !cmd->args[0])
		return (-1);
	cmd->built_in = is_builtin_command(cmd->args[0]);
	if (cmd->built_in)
	{
		cmd->invalid = 0;
		cmd->path = NULL;
		return (1);
	}
	if ((cmd->args[0][0] == '/' || cmd->args[0][0] == '.') &&
		access(cmd->args[0], F_OK | X_OK) == 0)
	{
		cmd->path = ft_strdup(cmd->args[0]);
		cmd->invalid = 0;
		return (1);
	}
	return (0);
}

int	search_in_paths(t_cmd *cmd, t_shelldata *shell)
{
	t_env	*env_path = find_env(shell->env, "PATH");
	char	**paths;
	char	*test;
	int		i = 0;

	if (!env_path || !env_path->value)
		return (0);
	paths = ft_split(env_path->value, ':');
	if (!paths)
		return (0);
	while (paths[i])
	{
		test = ft_myjoin(paths[i], "/", cmd->args[0]);
		if (access(test, F_OK | X_OK) == 0)
		{
			cmd->path = test;
			cmd->invalid = 0;
			array_free(paths);
			return (1);
		}
		free(test);
		i++;
	}
	array_free(paths);
	return (0);
}
