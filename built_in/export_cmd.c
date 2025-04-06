/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:37:53 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/06 16:30:59 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/built_in.h"

static int	count_env_variables(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static t_env	**create_env_array(t_env *env, int count)
{
	t_env	**arr;
	int		i;

	arr = malloc(sizeof(t_env *) * count);
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	return (arr);
}

static void	sort_and_print_env(t_env **env)
{
	int		count;
	t_env	**arr;

	count = count_env_variables(*env);
	arr = create_env_array(*env, count);
	if (!arr)
		return ;
	bubble_sort_env(arr, count);
	print_sorted_env(arr, count);
	free(arr);
}

static void	handle_key_value_pair(t_env **env, char *arg)
{
	char	*equal;
	char	*key;
	char	*value;
	size_t	key_len;

	equal = ft_strchr(arg, '=');
	if (equal)
	{
		key_len = equal - arg;
		key = ft_strndup(arg, key_len);
		value = ft_strdup(equal + 1);
		if (key && value)
			set_env(env, key, value);
		free(key);
		free(value);
	}
	else
		set_env(env, arg, "");
}

void	export_command(t_env **env, char **args)
{
	int	i;

	if (!args[1])
	{
		sort_and_print_env(env);
		return ;
	}
	i = 1;
	while (args[i])
	{
		handle_key_value_pair(env, args[i]);
		i++;
	}
}
