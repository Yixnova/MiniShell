/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:53:32 by busseven          #+#    #+#             */
/*   Updated: 2025/04/25 13:06:47 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	open_error(char *file)
{
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	exit(errno);
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