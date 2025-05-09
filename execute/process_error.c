/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:53:32 by busseven          #+#    #+#             */
/*   Updated: 2025/05/09 17:41:23 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_error(t_cmd *cmd, char *file, int redir_num)
{
	(void) cmd;
	errno = 1;
	cmd->err_type = 1;
	cmd->exit_code = 1;
	if (access(file, F_OK) < 0)
		cmd->err_msg = ft_strjoin(file, ": No such file or directory");
	if (redir_num == 1 || redir_num == 2)
	{
		if (access(file, W_OK) < 0)
			cmd->err_msg = ft_strjoin(file, ": Permission Denied");
	}
	if (redir_num == 3 || redir_num == 4)
	{
		if (access(file, R_OK) < 0)
			cmd->err_msg = ft_strjoin(file, ": Permission Denied");
	}
	return (1);
}

void	execve_error(void)
{
	write(2, "minishell: ", 11);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	exit(errno);
}
