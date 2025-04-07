/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:24:57 by busseven          #+#    #+#             */
/*   Updated: 2025/04/07 17:34:14 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		*ft_intjoin(int	*arr, int n)
{
	int	i;
	int	*new;

	i = 0;
	while(arr[i])
		i++;
	new = ft_calloc(i + 1, sizeof(int));
	i = 0;
	while(arr[i])
	{
		new[i] = arr[i];
		i++;
	}
	new[i] = n;
	free(arr);
	return(new);
}
