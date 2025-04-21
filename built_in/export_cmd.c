/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:37:53 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/21 18:26:02 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/built_in.h"

static void	sort_and_print_env(t_env **env)
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

static int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || !(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void	print_invalid_identifier(const char *arg)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static void	set_env_from_equal(t_env **env, char *arg, char *equal)
{
	size_t	key_len;
	char	*key;
	char	*value;

	key_len = equal - arg;
	key = ft_strndup(arg, key_len);
	value = ft_strdup(equal + 1);
	if (key && value)
		set_env(env, key, value);
	free(key);
	free(value);
}

static void	handle_export_arg(t_env **env, char *arg, int *error)
{
	char	*equal;
	char	*key;

	equal = ft_strchr(arg, '=');
	if (equal)
		key = ft_strndup(arg, equal - arg);
	else
		key = ft_strdup(arg);
	if (!is_valid_identifier(key))
	{
		print_invalid_identifier(arg);
		*error = 1;
		free(key);
		return ;
	}
	free(key);
	if (equal)
		set_env_from_equal(env, arg, equal);
	else
		set_env(env, arg, "");
}

void	export_command(t_env **env, char **args)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	if (!args[1])
	{
		sort_and_print_env(env);
		return ;
	}
	while (args[i])
	{
		handle_export_arg(env, args[i], &error);
		i++;
	}
	if (error)
		((t_env *)(*env))->envp = (char **)1;
}
