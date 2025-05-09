/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_error_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:53:32 by busseven          #+#    #+#             */
/*   Updated: 2025/05/09 16:59:55 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	command_not_found(t_cmd *tcmd, char *cmd)
{
	(void) tcmd;
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Command not found\n", 21);
	exit(127);
}

void	directory_error(t_cmd *cmd, char *dir)
{
	(void) cmd;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putendl_fd(": Is a directory", 2);
	exit(126);
}

void	access_permission_denied(t_cmd *cmd, char *file)
{
	(void) cmd;
	errno = 126;
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, "Permission denied", 18);
	write(2, "\n", 1);
	exit(errno);
}

void	access_error(t_cmd *cmd, char *file)
{
	(void) cmd;
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(126)));
	write(2, "\n", 1);
	exit(errno);
}

void	no_such_file(t_cmd *cmd, char *file)
{
	(void) cmd;
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, "No such file or directory", 26);
	write(2, "\n", 1);
	exit(127);
}
