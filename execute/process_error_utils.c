/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_error_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:58:28 by busseven          #+#    #+#             */
/*   Updated: 2025/05/16 16:42:44 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
