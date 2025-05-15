/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:53:32 by busseven          #+#    #+#             */
/*   Updated: 2025/05/15 10:51:23 by busseven         ###   ########.fr       */
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
		return(directory_error(cmd, file));
	cmd->err_msg = ft_myjoin(file, ": ", strerror(errno));
	return (1);
}

void	execve_error(void)
{
	write(2, "minishell: ", 11);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	exit(errno);
}
