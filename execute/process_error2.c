/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_error2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:25:31 by busseven          #+#    #+#             */
/*   Updated: 2025/05/26 13:35:23 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/minishell.h"

void	single_dot_error(void)
{
	ft_putstr_fd("minishell: .: filename argument required\n", 2);
	ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
	exit (2);
}

int	is_all_dots(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '.')
			return (0);
		i++;
	}
	return (1);
}
