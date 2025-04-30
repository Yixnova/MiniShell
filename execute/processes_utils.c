/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:40:12 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/30 18:22:39 by busseven         ###   ########.fr       */
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
void	close_pipes(t_shelldata *shell, int i)
{
	if(i != 0)
	{
		close(shell->pipes[i - 1][0]);
		close(shell->pipes[i - 1][1]);	
	}
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
