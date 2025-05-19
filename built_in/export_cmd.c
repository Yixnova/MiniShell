/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:37:53 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/19 19:55:31 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/built_in.h"

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

static void	set_env_from_equal(t_env **env, char *key, char *value)
{
	if (key && value)
		set_env(env, key, value);
	free(key);
}

static int	handle_export_arg(t_env **env, char *arg, int *error)
{
	char	*equal;
	char	*key;

	equal = ft_strchr(arg, '=');
	if (equal)
		key = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(equal));
	else
		key = ft_strdup(arg);
	if (!is_valid_identifier(key))
	{
		print_invalid_identifier(arg);
		*error = 1;
		free(key);
		return (1);
	}
	if (equal)
		set_env_from_equal(env, key, equal + 1);
	else
		set_env(env, arg, "");
	return (0);
}

int	export_command(t_env **env, char **args, t_shelldata *shell)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	if (!args[1])
	{
		sort_and_print_env(env);
		(void)shell;
		return (0);
	}
	while (args[i])
	{
		if (handle_export_arg(env, args[i], &error))
			return (1);
		i++;
	}
	if (error)
		return (1);
	else
		return (0);
}
