/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_error_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:53:32 by busseven          #+#    #+#             */
/*   Updated: 2025/05/15 13:57:15 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	command_not_found(t_cmd *tcmd, char *cmd)
{
	tcmd->err_msg = ft_strjoin(cmd, ": command not found");
	tcmd->err_type = 2;
	tcmd->exit_code = 127;
	return (1);
}

int	directory_error(t_cmd *cmd, char *dir)
{
	(void) cmd;
	cmd->err_msg = ft_strjoin(dir, ": Is a directory");
	cmd->exit_code = 126;
	cmd->err_type = 1;
	return (1);
}

int	access_permission_denied(t_cmd *cmd, char *file)
{
	cmd->err_msg = ft_strjoin(file, ": Permission denied");
	cmd->err_type = 1;
	cmd->exit_code = 126;
	return (1);
}

int	access_error(t_cmd *cmd, char *file)
{
	cmd->err_msg = ft_myjoin(file, ": ", strerror(errno));
	cmd->err_type = 1;
	cmd->exit_code = 126;
	return (1);
}

int	no_such_file(t_cmd *cmd, char *file)
{
	cmd->err_msg = ft_strjoin(file, ": No such file or directory");
	cmd->err_type = 1;
	cmd->exit_code = 127;
	return (1);
}
