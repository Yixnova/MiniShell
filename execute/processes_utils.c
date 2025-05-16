/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:40:12 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/16 10:30:36 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_permissions(t_cmd *cmd)
{
	if (access(cmd->path, X_OK) == 0)
		return (0);
	else
	{
		return(access_permission_denied(cmd, cmd->args[0]));
	}
	return (0);
}
int	find_command_path(t_cmd *cmd, t_shelldata *shell)
{
	if (check_builtin_and_path(cmd, shell))
	{
		if (search_in_paths(cmd, shell))
		{
			if(is_file_dir_name(cmd->args[0]))
			{
				cmd->path = cmd->args[0];
				return (0);
			}
			return (1);
		}	
		return (1);
	}
	return(0);
}

int	check_command_existence(t_cmd *cmd, t_shelldata *shell)
{
	int	valid;

	valid = find_command_path(cmd, shell);
	(void) valid;
	if (cmd->built_in)
		return (0);
	if (is_file_dir_name(cmd->args[0]))
	{
		if (is_directory(cmd->args[0]))
			return (directory_error(cmd, cmd->args[0]));
		else
		{
			if (!valid)
				return (no_such_file(cmd, cmd->args[0]));
			else if (access(cmd->path, F_OK) == 0)
				return(access_permission_denied(cmd, cmd->args[0]));
		}
	}
	else if (valid)
	{
		return(check_permissions(cmd));
	}
	return (0);
}

void	close_files(t_cmd **cmds)
{
	int i;

	i = 0;
	while((*cmds)->file_descs[i])
	{
		close((*cmds)->file_descs[i]);
		i++;
	}
}
