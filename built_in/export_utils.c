/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:30:37 by yigsahin          #+#    #+#             */
/*   Updated: 2025/06/05 19:10:50 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/built_in.h"

void	print_sorted_env(t_env **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("declare -x %s", arr[i]->name);
		if (arr[i]->value && arr[i]->value[0])
			printf("=\"%s\"", arr[i]->value);
		printf("\n");
		i++;
	}
	free(arr);
}

void	bubble_sort_env(t_env **arr, int count)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strncmp(arr[j]->name, arr[j + 1]->name,
					ft_strlen(arr[j]->name) + 1) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
