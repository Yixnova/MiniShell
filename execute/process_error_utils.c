/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_error_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:58:28 by busseven          #+#    #+#             */
/*   Updated: 2025/05/16 16:00:01 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	assign_error_messages(t_cmd *cmds, t_shelldata *shell)
{
	int	open_err = 0;
	while (cmds)
	{
		(cmds)->exit_code = 0;
		if(!cmds->args || !cmds->args[0] || cmds->args[0][0] == '\0')
			return ;
		else if(check_command_existence(cmds, shell))
		{
			;
		}
		if((cmds)->invalid && !is_file_dir_name(cmds->args[0]) && !open_err)
			command_not_found(cmds, cmds->args[0]);
		cmds = cmds->next;
	}
}
void	display_error_messages(t_cmd *cmds)
{
	while (cmds)
	{
		if(cmds->err_type == 2)
		{
			ft_putstr_fd(cmds->err_msg, 2);
			ft_putstr_fd("\n", 2);
		}
		cmds = cmds->next;
	}
}
