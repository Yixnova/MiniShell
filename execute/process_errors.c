/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:53:32 by busseven          #+#    #+#             */
/*   Updated: 2025/04/30 10:37:56 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	open_error(char *file, int redir_num)
{
	errno = 1;
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	if(access(file, F_OK) < 0)
	{
		write(2, "No such file or directory\n", 27);
		exit(1);	
	}
	if(redir_num == 1 || redir_num == 2)
	{
		if(access(file, W_OK) < 0)
			write(2, "Permission Denied\n", 19);
		exit(1);
	}
	if(redir_num == 3 || redir_num == 4)
	{
		if(access(file, R_OK) < 0)
			write(2, "Permission Denied\n", 19);
		exit(1);
	}
}

void	execve_error(void)
{
	write(2, "minishell: ", 11);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	exit(errno);
}
void	command_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Command not found\n", 21);
	exit(127);
}
void	directory_error(char *dir)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putendl_fd(": Is a directory", 2);
	exit(126);
}

void	access_permission_denied(char *file)
{
	errno = 126;
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, "Permission denied", 18);
	write(2, "\n", 1);
	exit(errno);
}
void	access_error(char *file)
{
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(126)));
	write(2, "\n", 1);
	exit(errno);
}

void	no_such_file(char *file)
{
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, "No such file or directory", 26);
	write(2, "\n", 1);
	exit(127);
}