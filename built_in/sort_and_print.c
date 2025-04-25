/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:13:19 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/22 10:13:21 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/built_in.h"

void	sort_and_print_env(t_env **env)
{
	int		count;
	t_env	*tmp;
	t_env	**arr;
	int		i;

	count = 0;
	tmp = *env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(t_env *) * count);
	if (!arr)
		return ;
	tmp = *env;
	i = 0;
	while (tmp)
	{
		arr[i++] = tmp;
		tmp = tmp->next;
	}
	bubble_sort_env(arr, count);
	print_sorted_env(arr, count);
	free(arr);
}
