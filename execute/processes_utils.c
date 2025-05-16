/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:40:12 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/16 17:57:43 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_files(t_cmd **cmds)
{
	int i;

	i = 0;
	while((*cmds)->file_descs[i])
	{
		close((*cmds)->file_descs[i]);
		i++;
	}
}
