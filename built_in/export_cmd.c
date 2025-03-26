/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:37:53 by yigsahin          #+#    #+#             */
/*   Updated: 2025/03/26 19:12:47 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/built_in.h"

static void	bubble_sort_env(t_env **arr, int count)
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
			if (ft_strncmp(arr[j]->key, arr[j + 1]->key,
					ft_strlen(arr[j]->key) + 1) > 0)
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

void	export_command(t_env **env, char **args)
{
	int		i;
	int		count;
	t_env	**arr;
	t_env	*curr;

	if (!args[1])
	{
		count = 0;
		curr = *env;
		while (curr)
		{
			count++;
			curr = curr->next;
		}
		arr = malloc(sizeof(t_env *) * count);
		if (!arr)
			return ;
		curr = *env;
		i = 0;
		while (curr)
		{
			arr[i] = curr;
			curr = curr->next;
			i++;
		}
		bubble_sort_env(arr, count);
		i = 0;
		while (i < count)
		{
			printf("declare -x %s", arr[i]->key);
			if (arr[i]->value && arr[i]->value[0])
				printf("=\"%s\"", arr[i]->value);
			printf("\n");
			i++;
		}
		free(arr);
	}
	else
	{
		i = 1;
		while (args[i])
		{
			char *equal = ft_strchr(args[i], '=');
			if (equal)
			{
				size_t key_len = equal - args[i];
				char *key = ft_strndup(args[i], key_len);
				char *value = ft_strdup(equal + 1);
				if (key && value)
					set_env(env, key, value);
				free(key);
				free(value);
			}
			else
				set_env(env, args[i], "");
			i++;
		}
	}
}
