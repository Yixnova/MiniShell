/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:01:01 by busseven          #+#    #+#             */
/*   Updated: 2025/05/12 14:26:23 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_all_pipes(t_shelldata *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count - 1)
	{
		free(shell->pipes[i]);
		i++;
	}
}

void	close_pipes(t_shelldata *shell, int i)
{
	if (i != 0)
	{
		close(shell->pipes[i - 1][0]);
		close(shell->pipes[i - 1][1]);
	}
}
