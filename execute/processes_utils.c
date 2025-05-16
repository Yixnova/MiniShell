/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:40:12 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/16 16:42:58 by busseven         ###   ########.fr       */
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
