/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:53:32 by busseven          #+#    #+#             */
/*   Updated: 2025/05/09 16:58:36 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	open_error(t_cmd *cmd, char *file, int redir_num)
{
	(void) cmd;
	errno = 1;
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	if (access(file, F_OK) < 0)
	{
		write(2, "No such file or directory\n", 27);
		exit(1);
	}
	if (redir_num == 1 || redir_num == 2)
	{
		if (access(file, W_OK) < 0)
			write(2, "Permission Denied\n", 19);
		exit(1);
	}
	if (redir_num == 3 || redir_num == 4)
	{
		if (access(file, R_OK) < 0)
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
