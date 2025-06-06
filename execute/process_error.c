/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:53:32 by busseven          #+#    #+#             */
/*   Updated: 2025/06/05 19:11:02 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_error(t_cmd *cmd, char *file, int redir_num)
{
	(void) cmd;
	(void) redir_num;
	cmd->err_type = 1;
	cmd->exit_code = 1;
	if (is_directory(file))
		return (directory_error(cmd, file));
	cmd->err_msg = ft_threejoin(file, ": ", strerror(errno));
	ft_putstr_fd(cmd->err_msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	execve_error(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	exit(errno);
}

int	command_not_found(t_cmd *tcmd, char *cmd)
{
	tcmd->err_msg = ft_strjoin(cmd, ": command not found");
	tcmd->err_type = 2;
	tcmd->invalid = 1;
	tcmd->exit_code = 127;
	return (1);
}

int	directory_error(t_cmd *cmd, char *dir)
{
	(void) cmd;
	cmd->err_msg = ft_strjoin(dir, ": Is a directory");
	cmd->err_type = 1;
	ft_putstr_fd(cmd->err_msg, 2);
	ft_putstr_fd("\n", 2);
	exit(126);
	return (1);
}

int	no_such_file(t_cmd *cmd, char *file)
{
	cmd->err_msg = ft_strjoin(file, ": No such file or directory");
	cmd->err_type = 1;
	ft_putstr_fd(cmd->err_msg, 2);
	ft_putstr_fd("\n", 2);
	exit(127);
	return (1);
}
